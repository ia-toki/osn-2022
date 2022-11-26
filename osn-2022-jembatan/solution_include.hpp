#pragma once

#include "common_include.hpp"

struct Kota
{
  int index;
  ULL h;
};

using Kota = struct Kota;
bool operator<(const Kota &a, const Kota &b)
{
  if (a.h == b.h)
    return a.index < b.index;
  return a.h < b.h;
}

bool solve(int N, int Q, const vector<int> &U, const vector<int> &V, const vector<ULL> &H, ULL &total, vector<pair<int, int>> &jembatan)
{
  assert(U.size() == V.size());
  UFDS ufds(N);
  for (int j = 0; j < U.size(); j++)
    ufds.connect(U[j] - 1, V[j] - 1);

  vector<vector<Kota>> componentH;
  map<int, int> parent2component;
  int c = 0;
  for (int i = 0; i < N; i++)
  {
    int parent = ufds.find(i);
    auto it = parent2component.find(parent);
    if (it != parent2component.end())
    {
      int componentIdx = it->second;
      componentH[componentIdx].emplace_back(Kota{i, H[i]});
    }
    else
    {
      vector<Kota> component;
      component.emplace_back(Kota{i, H[i]});
      componentH.push_back(component);
      parent2component.emplace(parent, c++);
    }
  }

  vector<vector<int>> componentPilih(c);

  if (componentH.size() <= 1)
    total = 0;
  else
  {
    for (int i = 0; i < componentH.size(); i++)
    {
      auto it = min_element(componentH[i].begin(), componentH[i].end());
      total += it->h;
      auto parent = ufds.find(it->index);
      auto itComponent = parent2component.find(parent);
      assert(itComponent != parent2component.end());
      componentPilih[itComponent->second].push_back(it->index);
      componentH[i].erase(it);
    }

    vector<Kota> sisa;
    for (int i = 0; i < componentH.size(); i++)
      sisa.insert(sisa.end(), componentH[i].begin(), componentH[i].end());

    if (sisa.size() < c - 2)
      return false;

    sort(sisa.begin(), sisa.end());

    for (int i = 0; i < c - 2; i++)
    {
      total += sisa[i].h;
      auto parent = ufds.find(sisa[i].index);
      auto itComponent = parent2component.find(parent);
      assert(itComponent != parent2component.end());
      componentPilih[itComponent->second].push_back(sisa[i].index);
    }
  }

  if (Q == 1 && total > 0)
  {
    vector<int> kecil;
    vector<vector<int>> besar;

    for (auto c : componentPilih)
    {
      assert(!c.empty());
      if (c.size() == 1)
        kecil.push_back(c[0]);
      else
        besar.push_back(c);
    }

    sort(besar.begin(), besar.end(), [](const auto &a, const auto &b)
         { return a.size() < b.size(); });

    while (!kecil.empty())
    {
      if (!besar.empty())
      {
        auto idxKecil = kecil.back();
        kecil.pop_back();

        auto &bc = besar.back();
        assert(bc.size() >= 2);

        auto idxBesar = bc.back();
        bc.pop_back();
        jembatan.emplace_back(idxKecil, idxBesar);
        if (bc.size() == 1)
        {
          kecil.push_back(bc[0]);
          besar.pop_back();
        }
      }
      else // 2 kecil, masing-masing 1
      {
        assert(kecil.size() == 2);
        jembatan.emplace_back(kecil[0], kecil[1]);
        kecil.clear();
      }
    }
  }

  return true;
}
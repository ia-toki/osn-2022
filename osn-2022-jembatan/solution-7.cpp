#include <bits/stdc++.h>

using namespace std;

class UFDS
{
public:
  UFDS(int n) : _parent(n)
  {
    for (int i = 0; i < n; i++)
      _parent[i] = i;
  }

  ~UFDS() = default;

  int find(int p)
  {
    assert(valid_index(p));

    if (_parent[p] != p)
    {
      _parent[p] = find(_parent[p]);
      return _parent[p];
    }
    else
      return p;
  }

  void connect(int p, int q)
  {
    assert(valid_index(p));
    assert(valid_index(q));
    assert(p != q);
    int pp = find(p);
    int qq = find(q);
    if (pp == qq)
      return;
    _parent[pp] = qq;
  }

  bool same(int p, int q)
  {
    assert(valid_index(p));
    assert(valid_index(q));
    return find(p) == find(q);
  }

private:
  vector<int> _parent;
  bool valid_index(int i) { return 0 <= i && i < _parent.size(); }
};

int numberOfComponents(int n, const vector<int> &u, const vector<int> &v)
{
  assert(u.size() == v.size());

  UFDS g(n);
  for (int i = 0; i < u.size(); i++)
    g.connect(u[i] - 1, v[i] - 1);

  std::vector<int> parent(n);
  for (int i = 0; i < n; i++)
    parent[i] = g.find(i);

  sort(parent.begin(), parent.end());
  auto it = unique(parent.begin(), parent.end());
  return distance(parent.begin(), it);
}

using ULL = unsigned long long;


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

int main()
{
  int N, M, Q;

  cin >> N >> M >> Q;
  vector<ULL> h(N);
  vector<int> u(M), v(M);
  for (int i = 0; i < N; i++)
    cin >> h[i];

  for (int j = 0; j < M; j++)
    cin >> u[j] >> v[j];

  ULL total = 0;
  vector<pair<int, int>> jembatan;
  auto success = solve(N, Q, u, v, h, total, jembatan);

  if (!success)
    cout << -1 << endl;
  else
    cout << total << endl;

  return 0;
}
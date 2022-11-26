#pragma once

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

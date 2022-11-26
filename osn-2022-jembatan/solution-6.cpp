// solution-6

#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
  Graph(int n) : _n(n), visited(vector<bool>(n, false))
  {

    adj.resize(n);
    for (int i = 0; i < n; i++)
      adj[i].assign(n, false);
  }

  void addEdge(int v, int w)
  {
    adj[v][w] = true;
    adj[w][v] = true;
  }

  void DFS(int v, vector<int> &nodesVisited)
  {
    visited[v] = true;

    nodesVisited.push_back(v);
    for (int idx = 0; idx < _n; idx++)
    {
      if (adj[v][idx] && !visited[idx])
        DFS(idx, nodesVisited);
    }
  }

  bool isVisited(int v) const
  {
    return visited[v];
  }

private:
  int _n;
  vector<bool> visited;
  vector<vector<bool>> adj;
};

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
  Graph g(N);
  for (int i = 0; i < U.size(); i++)
    g.addEdge(U[i] - 1, V[i] - 1);

  vector<vector<Kota>> components;

  for (int i = 0; i < N; i++)
  {
    if (!g.isVisited(i))
    {
      vector<int> nodesVisited;
      g.DFS(i, nodesVisited);

      vector<Kota> curComponents;
      for (auto idx : nodesVisited)
        curComponents.emplace_back(Kota{idx, H[idx]});
      components.push_back(curComponents);
    }
  }

  total = 0;
  if (2 * components.size() - 2 > N)
    return false;
  else if (components.size() == 1)
    return true;
  else
  {
    for (auto &comp : components)
    {

      auto it = min_element(comp.begin(), comp.end());
      total += it->h;
      comp.erase(it);
    }

    vector<ULL> sisa;
    for (auto &comp : components)
    {
      for (const auto &kota : comp)
        sisa.push_back(kota.h);
    }

    sort(sisa.begin(), sisa.end());
    assert(sisa.size() >= components.size() - 2);

    for (int i = 0; i < components.size() - 2; i++)
      total += sisa[i];
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
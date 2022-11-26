// solution-5

#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
  Graph(int n) : visited(vector<bool>(n, false)) {}

  void addEdge(int v, int w)
  {
    adj[v].push_back(w);
    adj[w].push_back(v);
  }

  void DFS(int v)
  {
    visited[v] = true;

    list<int>::iterator i;
    for (auto node : adj[v])
      if (!visited[node])
        DFS(node);
  }

  bool isVisited(int v)
  {
    return visited[v];
  }

private:
  vector<bool> visited;
  map<int, list<int>> adj;
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

  g.DFS(0);

  vector<Kota> comp1;
  vector<Kota> comp2;

  for (int i = 0; i < N; i++)
  {
    if (g.isVisited(i))
      comp1.emplace_back(Kota{i, H[i]});
    else
      comp2.emplace_back(Kota{i, H[i]});
  }

  if (comp1.empty() || comp2.empty())
    total = 0;
  else
  {

    auto it1 = min_element(comp1.begin(), comp1.end());
    auto it2 = min_element(comp2.begin(), comp2.end());

    total += it1->h + it2->h;
    if (Q == 1)
      jembatan.emplace_back(it1->index, it2->index);
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
  {
    cout << -1 << endl;
    return 0;
  }
  else
  {
    cout << total << endl;

    if (Q == 1 && total == 0)
      cout << 0 << endl;

    if (Q == 1 && total > 0)
    {

      cout << jembatan.size() << endl;
      for (const auto &[p, q] : jembatan)
        cout << p + 1 << " " << q + 1 << endl;
    }
  }

  return 0;
}
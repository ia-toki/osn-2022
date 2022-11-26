#include "solution_include.hpp"

#include <bits/stdc++.h>

using namespace std;

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

  cout << total << endl;

  if (Q == 1 && total == 0)
    cout << 0 << endl;

  if (Q == 1 && total > 0)
  {

    cout << jembatan.size() << endl;
    for (const auto &[p, q] : jembatan)
      cout << p + 1 << " " << q + 1 << endl;
  }
  return 0;
}
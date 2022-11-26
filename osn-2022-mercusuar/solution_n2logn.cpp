#include <bits/stdc++.h>
using namespace std;

using lint = long long;
const lint INF = 1e18;

lint Solve(vector<int> A) {
  int N = A.size();
  vector<int> V(N), IV(N);
  iota(begin(V), end(V), 0);
  sort(begin(V), end(V),
       [&A](int i, int j) { return pair(A[i], i) < pair(A[j], j); });
  for (int i = 0; i < N; i++) {
    IV[V[i]] = i;
  }
  vector<array<int, 4>> range;
  const auto g = [&](const auto &g, int l, int r) {
    if (l > r) {
      return;
    }
    int id = range.size();
    int mx = -1;
    for (int i = l; i <= r; i++) {
      mx = max(mx, A[i]);
    }
    int s = -1;
    for (int i = l; i <= r; i++) {
      if (A[i] == mx) {
        s = i;
      }
    }
    range.push_back({l, r, id, s});
    g(g, l, s - 1);
    g(g, s + 1, r);
  };
  g(g, 0, N - 1);
  sort(begin(range), end(range));
  vector memo(N, vector(N + 1, vector(2, vector(2, -INF))));
  const auto f = [&](const auto &f, int l, int r, int cl, int cr, int x) {
    if (l > r) {
      return cl == 0 || cr == 0 ? INF : 0;
    }
    if (x < 0) {
      return INF;
    }
    auto it =
        lower_bound(begin(range), end(range), array<int, 4>{l, r, -1, -1});
    int id = (*it)[2];
    int s = (*it)[3];

    if (memo[id][x][cl][cr] != -INF) {
      return memo[id][x][cl][cr];
    }
    lint &ret = memo[id][x][cl][cr];
    ret = INF;

    // Case: do not increase A[s]
    ret = min(ret, f(f, l, s - 1, cl, 0, IV[s]) + f(f, s + 1, r, 1, cr, IV[s]));
    ret = min(ret, f(f, l, s - 1, cl, 1, IV[s]) + f(f, s + 1, r, 0, cr, IV[s]));

    // Case: increase A[s] to A[V[x]]
    if (x < N) {
      ret = min(ret, A[V[x]] - A[s] + f(f, l, s - 1, cl, 1, x) +
                         f(f, s + 1, r, 1, cr, x));
    }

    // Case: increase A[s] to A[l - 1]
    if (cl == 0) {
      assert(l > 0 && IV[s] <= IV[l - 1]);
      ret = min(ret, A[l - 1] - A[s] + f(f, l, s - 1, 1, 1, IV[l - 1]) +
                         f(f, s + 1, r, 1, cr, min(x, IV[l - 1])));
    }

    // Case: increase A[s] to A[r + 1]
    if (cr == 0) {
      assert(r < N - 1);
      assert(r < N - 1 && IV[s] <= IV[r + 1]);
      ret =
          min(ret, A[r + 1] - A[s] + f(f, l, s - 1, cl, 1, min(x, IV[r + 1])) +
                       f(f, s + 1, r, 1, 1, IV[r + 1]));
    }
    return ret;
  };
  return f(f, 0, N - 1, 1, 1, N);
}

int main() {
  int N;
  cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  cout << Solve(A) << '\n';
  return 0;
}

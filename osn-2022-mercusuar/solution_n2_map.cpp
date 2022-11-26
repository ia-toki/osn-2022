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
  map<array<int, 2>, int> mxr;
  map<array<int, 2>, int> idr;
  vector memo(N, vector(N + 1, vector(2, vector(2, -INF))));
  const auto f = [&](const auto &f, int l, int r, int cl, int cr, int x) {
    if (l > r) {
      return cl == 0 || cr == 0 ? INF : 0;
    }
    if (x < 0) {
      return INF;
    }
    if (idr.count({l, r}) == 0) {
      idr[{l, r}] = idr.size();
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
      mxr[{l, r}] = s;
    }

    int id = idr[{l, r}];
    if (memo[id][x][cl][cr] != -INF) {
      return memo[id][x][cl][cr];
    }
    lint &ret = memo[id][x][cl][cr];
    ret = INF;

    int s = mxr[{l, r}];

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

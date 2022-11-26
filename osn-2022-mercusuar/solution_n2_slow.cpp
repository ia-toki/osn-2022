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
  const auto f = [&](const auto &f, int l,
                     int r) -> vector<vector<vector<lint>>> {
    vector dp = vector(N + 1, vector(2, vector(2, -INF)));
    if (l > r) {
      for (int x = 0; x <= N; x++) {
        for (int cl = 0; cl < 2; cl++) {
          for (int cr = 0; cr < 2; cr++) {
            dp[x][cl][cr] = cl == 0 || cr == 0 ? INF : 0;
          }
        }
      }
      return dp;
    }

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

    auto lft = f(f, l, s - 1);
    auto rgt = f(f, s + 1, r);

    for (int x = 0; x <= N; x++) {
      for (int cl = 0; cl < 2; cl++) {
        for (int cr = 0; cr < 2; cr++) {
          lint &ret = dp[x][cl][cr];
          ret = INF;

          // Case: do not increase A[s]
          ret = min(ret, lft[IV[s]][cl][0] + rgt[IV[s]][1][cr]);
          ret = min(ret, lft[IV[s]][cl][1] + rgt[IV[s]][0][cr]);

          // Case: increase A[s] to A[V[x]]
          if (x < N) {
            ret = min(ret, A[V[x]] - A[s] + lft[x][cl][1] + rgt[x][1][cr]);
          }

          // Case: increase A[s] to A[l - 1]
          if (cl == 0 && l > 0) {
            ret = min(ret, A[l - 1] - A[s] + lft[IV[l - 1]][1][1] +
                               rgt[min(x, IV[l - 1])][1][cr]);
          }

          // Case: increase A[s] to A[r + 1]
          if (cr == 0 && r < N - 1) {
            ret = min(ret, A[r + 1] - A[s] + lft[min(x, IV[r + 1])][cl][1] +
                               rgt[IV[r + 1]][1][1]);
          }
        }
      }
    }
    return dp;
  };
  return f(f, 0, N - 1)[N][1][1];
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

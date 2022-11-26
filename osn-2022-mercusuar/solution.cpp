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
  vector<int> seg(2 * N);
  for (int i = 0; i < N; i++) {
    seg[N + i] = IV[i];
  }
  for (int i = N - 1; i > 0; i--) {
    seg[i] = max(seg[i * 2], seg[i * 2 + 1]);
  }
  const auto f = [&](const auto &f, int l,
                     int r) -> array<array<array<lint, 3>, 2>, 2> {
    array<array<array<lint, 3>, 2>, 2> dp;
    for (int cl = 0; cl < 2; cl++) {
      for (int cr = 0; cr < 2; cr++) {
        for (int cx = 0; cx < 3; cx++) {
          dp[cl][cr][cx] = (l > r && cl == 1 && cr == 1) ? 0 : INF;
        }
      }
    }
    if (l > r) {
      return dp;
    }
    int s = -1;
    for (int i = l + N, j = r + N + 1; i < j; i /= 2, j /= 2) {
      if (i & 1) s = max(s, seg[i++]);
      if (j & 1) s = max(s, seg[--j]);
    }
    s = V[s];
    auto lft = f(f, l, s - 1);
    auto rgt = f(f, s + 1, r);
    for (int cl = 0; cl < 2; cl++) {
      for (int cr = 0; cr < 2; cr++) {
        for (int cx = 0; cx < 3; cx++) {
          lint &ret = dp[cl][cr][cx];

          // Case: do not increase A[s]
          for (int cxl = 0; cxl < 3; cxl++) {
            for (int cxr = 0; cxr < 3; cxr++) {
              ret = min(ret, 1ll * (cxl + cxr) * A[s] + lft[cl][0][cxl] +
                                 rgt[1][cr][cxr]);
              ret = min(ret, 1ll * (cxl + cxr) * A[s] + lft[cl][1][cxl] +
                                 rgt[0][cr][cxr]);
            }
          }

          // Case: increase A[s] to A[V[x]]
          for (int cxl = 0; cxl < cx; cxl++) {
            int cxr = cx - 1 - cxl;
            ret = min(ret, -A[s] + lft[cl][1][cxl] + rgt[1][cr][cxr]);
            ret = min(ret, -A[s] + lft[cl][1][cxl] + rgt[1][cr][cxr]);
          }

          // Case: increase A[s] to A[l - 1]
          if (cl == 0 && l > 0) {
            for (int cxl = 0; cxl < 3; cxl++) {
              for (int cxr = 0; cxr < 3; cxr++) {
                ret = min(
                    ret,
                    (A[l - 1] - A[s]) + (cxl * A[l - 1] + lft[1][1][cxl]) +
                        min(cxr * A[l - 1] + rgt[1][cr][cxr], rgt[1][cr][cx]));
              }
            }
          }

          // Case: increase A[s] to A[r + 1]
          if (cr == 0 && r < N - 1) {
            for (int cxl = 0; cxl < 3; cxl++) {
              for (int cxr = 0; cxr < 3; cxr++) {
                ret = min(
                    ret,
                    (A[r + 1] - A[s]) + (cxr * A[r + 1] + rgt[1][1][cxr]) +
                        min(cxl * A[r + 1] + lft[cl][1][cxl], lft[cl][1][cx]));
              }
            }
          }
        }
      }
    }
    return dp;
  };
  return f(f, 0, N - 1)[1][1][0];
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

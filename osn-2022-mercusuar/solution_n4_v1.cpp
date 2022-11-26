#include <bits/stdc++.h>
using namespace std;

using lint = long long;
const lint INF = 1e18;

lint Solve(vector<int> A) {
  int N = A.size();
  auto V = A;
  sort(begin(V), end(V));
  V.resize(unique(begin(V), end(V)) - begin(V));
  vector memo(N, vector(N, vector(3, vector(V.size() + 1, -INF))));
  const auto f = [&](const auto &f, int l, int r, int c, int x) {
    if (l > r) {
      return c == 0 ? 0 : INF;
    }
    if (x < 0 || c < 0) {
      return INF;
    }
    if (memo[l][r][c][x] != -INF) {
      return memo[l][r][c][x];
    }
    lint &ret = memo[l][r][c][x];
    ret = INF;
    if (c == 0) {
      ret = min(ret, f(f, l, r, 0, x - 1));
      ret = min(ret, f(f, l, r, 2, x - 1));
    } else {
      for (int i = l; i <= r; i++) {
        if (V[x] < A[i]) {
          return INF;
        }
      }
      for (int i = l; i <= r; i++) {
        ret = min(
            ret, f(f, l, i - 1, 0, x) + f(f, i + 1, r, c - 1, x) + V[x] - A[i]);
        ret = min(
            ret, f(f, l, i - 1, 0, x) + f(f, i + 1, r, c - 0, x) + V[x] - A[i]);
      }
    }
    return ret;
  };
  return f(f, 0, N - 1, 0, V.size());
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

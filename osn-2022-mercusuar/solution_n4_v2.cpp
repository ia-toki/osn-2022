#include <bits/stdc++.h>
using namespace std;

using lint = long long;
const lint INF = 1e18;

lint Solve(vector<int> A) {
  int N = A.size();
  auto V = A;
  sort(begin(V), end(V));
  V.resize(unique(begin(V), end(V)) - begin(V));
  vector memo(N, vector(N, vector(V.size() + 1, -INF)));
  const auto f = [&](const auto &f, int l, int r, int x) {
    if (l > r) {
      return 0ll;
    }
    if (x < 0) {
      return INF;
    }
    if (memo[l][r][x] != -INF) {
      return memo[l][r][x];
    }
    lint &ret = memo[l][r][x];
    ret = INF;
    int mx = -1;
    for (int i = l; i <= r; i++) {
      mx = max(mx, A[i]);
    }
    vector<int> S;
    for (int i = l; i <= r; i++) {
      if (A[i] == mx) {
        S.emplace_back(i);
      }
    }
    if (S.size() >= 2) {
      lint sum = 0;
      S.insert(begin(S), l - 1);
      S.emplace_back(r + 1);
      int nxt = lower_bound(begin(V), end(V), mx) - begin(V);
      for (int i = 1; i < int(S.size()); i++) {
        sum += f(f, S[i - 1] + 1, S[i] - 1, nxt);
      }
      ret = min(ret, sum);
    } else {
      int s = S[0];
      if (x < int(V.size())) {
        ret = min(ret, V[x] - A[s] + f(f, l, s - 1, x) + f(f, s + 1, r, x));
      }
      int nxt = lower_bound(begin(V), end(V), mx) - begin(V);
      for (int i = l; i <= s - 1; i++) {
        ret = min(ret, A[s] - A[i] + f(f, l, i - 1, nxt) +
                           f(f, i + 1, s - 1, nxt) + f(f, s + 1, r, nxt));
      }
      for (int i = s + 1; i <= r; i++) {
        ret = min(ret, A[s] - A[i] + f(f, l, s - 1, nxt) +
                           f(f, s + 1, i - 1, nxt) + f(f, i + 1, r, nxt));
      }
    }
    return ret;
  };
  return f(f, 0, N - 1, V.size());
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

#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int N;
  cin >> N;
  vector<int> A(N), W(N), V(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    A[i]--;
  }
  for (int i = 0; i < N; i++) {
    cin >> W[i];
  }
  for (int i = 0; i < N; i++) {
    cin >> V[i];
  }

  vector<vector<vector<int>>> ls(2, vector<vector<int>>(N));
  for (int i = 0; i < N; i++) {
    ls[0][A[i]].emplace_back(i);
  }
  for (int i = N - 1; i >= 0; i--) {
    ls[1][A[i]].emplace_back(i);
  }

  const long long INF = 2e18;
  vector<long long> dp(N, INF);
  int last = N;
  for (int v = N - 1; v >= 0; v--) {
    if (last == N) {
      for (auto i : ls[0][v]) {
        dp[i] = V[i];
      }
    } else {
      for (int r = 0; r < 2; r++) {
        int ptr = 0;
        long long mn = INF;
        for (auto i : ls[r][v]) {
          while (ptr < int(ls[r][last].size()) &&
                 ((r == 0 && ls[r][last][ptr] < i) ||
                  (r == 1 && ls[r][last][ptr] > i))) {
            mn = min(mn, dp[ls[r][last][ptr]] +
                             (r == 0 ? -ls[r][last][ptr] : ls[r][last][ptr]));
            ptr += 1;
          }
          if (2 * INF / W[i] >= mn) {
            dp[i] = min(
                dp[i], V[i] + 1ll * W[i] * (r == 0 ? i : -i) + 1ll * W[i] * mn);
          }
        }
      }
    }
    if (!ls[0][v].empty()) {
      last = v;
    }
  }

  long long ans = INF;
  for (auto i : ls[0][last]) {
    ans = min(ans, dp[i]);
  }

  cout << ans << '\n';
  return 0;
}

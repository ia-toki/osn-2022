#include <bits/stdc++.h>
using namespace std;

using lint = long long;
const lint INF = 1e18;

lint Solve(vector<int> A) {
  int N = A.size();
  vector<vector<lint>> dp(N, vector<lint>(N));
  for (int l = N - 1; l >= 0; l--) {
    for (int r = l; r < N; r++) {
      dp[l][r] = INF;
      for (int cl = 0; cl <= N; cl++) {
        for (int cr = 0; cr <= N; cr++) {
          int nl = l + cl;
          int nr = r - cr;
          if (cl + cr >= 2 && nl <= nr + 1) {
            int w = 0;
            lint cost = 0;
            for (int i = 0; i < cl; i++) {
              cost -= A[l + i];
              w = max(w, A[l + i]);
            }
            for (int i = 0; i < cr; i++) {
              cost -= A[r - i];
              w = max(w, A[r - i]);
            }
            cost += 1ll * (cl + cr) * w;
            dp[l][r] = min(dp[l][r], (nl > nr ? 0 : dp[nl][nr]) + cost);
          }
        }
      }
    }
  }
  return dp[0][N - 1];
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

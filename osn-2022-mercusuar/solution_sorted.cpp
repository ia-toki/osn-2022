#include <bits/stdc++.h>
using namespace std;

using lint = long long;
const lint INF = 1e18;

lint Solve(vector<int> A) {
  int N = A.size();
  vector<lint> dp(N + 1);
  dp[0] = 0;
  for (int i = 1; i <= N; i++) {
    dp[i] = INF;
    int w = 0;
    lint s = 0;
    for (int j = 0; j <= 3 && j <= i; j++) {
      if (2 <= j) {
        dp[i] = min(dp[i], dp[i - j] + 1ll * w * j - s);
      }
      if (j < i) {
        w = max(w, A[i - 1 - j]);
        s += A[i - 1 - j];
      }
    }
  }
  return dp[N];
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

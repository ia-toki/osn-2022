#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5;
const long long MAX_ANS = 1e18;

long long multiply(long long a, long long b) {
  if (a == 0 || b == 0) return 0;
  if (a > MAX_ANS || b > MAX_ANS) return MAX_ANS+1;
  if (a > MAX_ANS / b) return MAX_ANS+1;
  return a * b > MAX_ANS ? MAX_ANS + 1 : a * b;
}

int N, M;
int A[MAX_N + 5], W[MAX_N + 5], V[MAX_N + 5];
long long dp[MAX_N + 5];
vector<int> colorGroup[MAX_N + 5];

void compress() {
  set<int> tmp;
  for (int i = 1; i <= N; i++) {
    tmp.emplace(A[i]);
  }

  map<int, int> newId;
  int p_newId = 1;
  for (int num : tmp) {
    newId[num] = p_newId++;
  }

  M = tmp.size();
  for (int i = 1; i <= N; i++) {
    A[i] = newId[A[i]];
  }
}

void prepare() {
  ios_base::sync_with_stdio(0);
  cin >> N;
  for (int i = 1; i <= N; i++) cin >> A[i];
  for (int i = 1; i <= N; i++) cin >> W[i];
  for (int i = 1; i <= N; i++) cin >> V[i];
  compress();

  for (int i = 1; i <= N; i++) {
    colorGroup[A[i]].emplace_back(i);
  }
  memset(dp, 0x3f3f3f3fLL, sizeof(dp));
}

void solve(int color) {
  if (color == M) {
    for (int idx : colorGroup[color]) {
      dp[idx] = V[idx];
    }
    return;
  }

  for (int i : colorGroup[color]) {
    for (int j : colorGroup[color+1]) {
      dp[i] = min(dp[i], multiply(abs(i - j) + dp[j], W[i]) + V[i]);
    }
  }
}

int main() {
  prepare();
  for (int i = M; i >= 1; i--) {
    solve(i);
  }

  long long ans = 2e18;
  for (int i = 1; i <= N; i++) {
    if (A[i] == 1) ans = min(ans, dp[i]);
  }

  cout << ans << "\n";
  // assert(ans <= MAX_ANS);
}

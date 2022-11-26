#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 5e5;
const long long MAX_ANS = 1e18;

long long multiply(long long a, long long b) {
  if (a == 0 || b == 0) return 0;
  if (a > MAX_ANS || b > MAX_ANS) return MAX_ANS+1;
  if (a > MAX_ANS / b) return MAX_ANS+1;
  return a * b > MAX_ANS ? MAX_ANS + 1 : a * b;
}

int N, M;
int A[MAX_N + 5], W[MAX_N + 5], V[MAX_N + 5];
long long memo[60][MAX_N + 5];
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
  memset(memo, -1, sizeof(memo));
}

void prepare() {
  ios_base::sync_with_stdio(0);
  cin >> N;
  for (int i = 1; i <= N; i++) cin >> A[i];
  for (int i = 1; i <= N; i++) cin >> W[i];
  for (int i = 1; i <= N; i++) cin >> V[i];
  compress();
}

long long dp(int mult, int idx) {
  if (A[idx] == M) return 0;
  if (memo[mult][idx] != -1) return memo[mult][idx];
  long long res = MAX_ANS + 1;
  for (int nxt = 1; nxt <= N; nxt++) {
    if (A[nxt] == A[idx] + 1) {
      long long now = dp(mult + (W[nxt] == 2), nxt) + multiply(abs(nxt - idx), (1LL << mult)) + multiply(1LL << mult, V[nxt]);
      res = min(res, now);
    }
  }
  return memo[mult][idx] = res;
}

int main() {
  prepare();
  long long ans = 2e18;
  for (int i = 1; i <= N; i++) {
    if (A[i] == 1) ans = min(ans, dp(0 + (W[i] == 2), i) + V[i]);
  }

  cout << ans << "\n";
  // assert(ans <= MAX_ANS);
}

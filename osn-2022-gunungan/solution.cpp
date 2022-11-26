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
vector<int> colorGroup[100005];

void compress() {
  vector<int> tmp;
  for (int i = 1; i <= N; i++) {
    tmp.emplace_back(A[i]);
  }

  sort(tmp.begin(), tmp.end());
  tmp.resize(unique(tmp.begin(), tmp.end()) - tmp.begin());

  M = tmp.size();
  for (int i = 1; i <= N; i++) {
    A[i] = upper_bound(tmp.begin(), tmp.end(), A[i]) - tmp.begin();
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

int getNextIdx(int &p_1, int &p_2, vector<int> &vec1, vector<int> &vec2) {
  assert(p_1 < vec1.size() || p_2 < vec2.size());
  if (p_2 >= vec2.size()) return vec1[p_1++];
  if (p_1 >= vec1.size()) return vec2[p_2++];
  if (vec1[p_1] < vec2[p_2]) return vec1[p_1++];
  return vec2[p_2++];
}

void solve(int color) {
  if (color == M) {
    for (int idx : colorGroup[color]) {
      dp[idx] = V[idx];
    }
    return;
  }

  int p_1=0, p_2=0;
  vector<int> vec;
  while (p_1 < colorGroup[color].size() || p_2 < colorGroup[color+1].size()) {
    vec.emplace_back(getNextIdx(p_1, p_2, colorGroup[color], colorGroup[color+1]));
  }

  // iteration from the front for i > j cases;
  long long optimal = 2e18;
  for (int i = 0; i < vec.size(); i++) {
    int idx = vec[i];
    if (A[idx] == color) {
      dp[idx] = min(dp[idx], multiply(optimal - (N - idx), W[idx]) + V[idx]);
    }else {
      optimal = min(optimal, dp[idx] + (N - idx));
    }
  }

  // iterate from behind
  optimal = 2e18;
  for (int i = vec.size()-1; i >= 0; i--) {
    int idx = vec[i];
    if (A[idx] == color) {
      dp[idx] = min(dp[idx], multiply(optimal - idx, W[idx]) + V[idx]);
    }else {
      optimal = min(optimal, dp[idx] + idx);
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
  assert(ans <= MAX_ANS);
}

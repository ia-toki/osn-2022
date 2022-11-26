#include <algorithm>
#include <cstdio>
#include <vector>

const long long kInf = 2e18;

long long mul(long long x, long long y) {
  if (x > kInf / y) return kInf;
  return x * y;
}

long long solve(std::vector<int> A, std::vector<int> W, std::vector<int> V) {
  int N = static_cast<int>(A.size());
  std::vector<long long> dp(N);
  std::vector<std::vector<int>> pos(N);
  for (int i = 0; i < N; ++i) pos[--A[i]].push_back(i);
  for (int i = 0, j = 0; j < N; ++i, ++j) {
    while (j < N && pos[j].empty()) ++j;
    if (j < N) std::swap(pos[i], pos[j]);
  }
  while (pos.back().empty()) pos.pop_back();

  for (int idx : pos.back()) dp[idx] = V[idx];

  for (int i = pos.size() - 2; i >= 0; --i) {
    int j = 0;
    long long miniDp = kInf;
    for (int idx : pos[i]) {
      for (; j < pos[i + 1].size() && pos[i + 1][j] < idx; ++j) {
        miniDp = std::min(miniDp, dp[pos[i + 1][j]] - pos[i + 1][j]);
      }
      dp[idx] = mul(miniDp + idx, W[idx]) + V[idx];
    }

    j = 0;
    miniDp = kInf;
    std::reverse(pos[i].begin(), pos[i].end());
    std::reverse(pos[i + 1].begin(), pos[i + 1].end());
    for (int idx : pos[i]) {
      for (; j < pos[i + 1].size() && pos[i + 1][j] > idx; ++j) {
        miniDp = std::min(miniDp, dp[pos[i + 1][j]] + pos[i + 1][j]);
      }
      dp[idx] = std::min(dp[idx], mul(miniDp - idx, W[idx]) + V[idx]);
    }
    std::reverse(pos[i].begin(), pos[i].end());
    std::reverse(pos[i + 1].begin(), pos[i + 1].end());
  }

  long long ans = kInf;
  for (int idx : pos[0]) ans = std::min(ans, dp[idx]);
  return ans;
}

int main() {
  int N;
  scanf("%d", &N);
  std::vector<int> A(N), W(N), V(N);
  for (int i = 0; i < N; ++i) scanf("%d", &A[i]);
  for (int i = 0; i < N; ++i) scanf("%d", &W[i]);
  for (int i = 0; i < N; ++i) scanf("%d", &V[i]);
  printf("%lld\n", solve(A, W, V));
  return 0;
}

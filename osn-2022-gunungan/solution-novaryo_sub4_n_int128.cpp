#include <bits/stdc++.h>
#define pii pair<int, int>
#define pll pair<long long, long long>
#define L(n) (n << 1)
#define R(n) (n << 1 | 1)
#define print_vector(n) for(auto a0 : n) cout << a0 << ' '; cout << endl;
#define vector_sort(n) sort(n.begin(), n.end())
#define print_array(n, l, r) for(int a0 = l; a0 <= r; a0++) cout << n[a0] << ' '; cout << '\n';
#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)
#define ABS(a) ((a) > 0 ? (a) : -(a))
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
long long dp[60][MAX_N + 5];
vector<int> colorGroup[100005];

long long multiply(long long a, long long b) {
  if (a == 0 || b == 0) return 0;
  if (a > MAX_ANS || b > MAX_ANS) return MAX_ANS+1;
  if (a > MAX_ANS / b) return MAX_ANS+1;
  return a * b > MAX_ANS ? MAX_ANS + 1 : a * b;
}

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

  // cout << M << "\n";
  // print_array(A, 1, N);
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

void solve(int layer, int color) {
  if (color == 1) {
    if (layer != 0) return;
    for (int idx : colorGroup[color]) {
      dp[layer + (W[idx] == 2)][idx] = V[idx];
    }
    return;
  }

  for (int )
  int p_1=0, p_2=0;
  vector<int> vec;
  while (p_1 < colorGroup[color-1].size() || p_2 < colorGroup[color].size()) {
    vec.emplace_back(getNextIdx(p_1, p_2, colorGroup[color-1], colorGroup[color]));
  }

  long long mult = (1LL << layer);
  
  for (int i = 0; i < vec.size(); i++) {
    int idx = vec[i];
    int nxt_layer = layer + (W[idx] == 2);
    if (A[idx] == color) {
      dp[nxt_layer][idx] = min(dp[nxt_layer][idx], normalize(optimal + V[idx] * mult - (N - idx) * mult));
    }else {
      optimal = min(optimal, dp[layer][idx] + (N - idx) * mult);
    }
  }

  optimal = 2e36;
  for (int i = vec.size()-1; i >= 0; i--) {
    int idx = vec[i];
    int nxt_layer = layer + (W[idx] == 2);
    if (A[idx] == color) {
      dp[nxt_layer][idx] = min(dp[nxt_layer][idx], normalize(optimal + V[idx] * mult - idx * mult));
    }else {
      optimal = min(optimal, dp[layer][idx] + idx * mult);
    }
  }
}

int main() {
  prepare();
  for (int j = 0; j < 59; j++) {
    for (int i = 1; i <= M; i++) {
      solve(j, i);
    }
  }

  long long ans = 2e18;
  for (int i = 1; i <= N; i++) {
    if (A[i] == M) {
      for (int j = 0; j < 60; j++) {
        ans = min(ans, dp[j][i]);
      }
    }
  }

  cout << ans << "\n";
}

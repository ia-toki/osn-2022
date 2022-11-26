#include <bits/stdc++.h>
using namespace std;

using lint = long long;
const lint MOD = 1e9 + 7;

int main() {
  int N;
  cin >> N;
  vector<int> A(N), T(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  for (int i = 0; i < N; i++) {
    cin >> T[i];
    if (T[i] == 2) {
      A[i] *= -1;
    }
  }
  vector<lint> P(N + 1);
  vector<lint> PP(N + 1);
  vector<lint> PPP(N + 1);
  for (int i = 0; i < N; i++) {
    P[i + 1] = P[i] + A[i];
    PP[i + 1] = (PP[i] + P[i]) % MOD;
    PPP[i + 1] = (PPP[i] + 1ll * i * P[i]) % MOD;
  }
  lint ans = 0;
  vector<int> st = {0};
  for (int R = 1; R <= N; R++) {
    while (!st.empty() && P[R] >= P[st.back()]) {
      st.pop_back();
    }
    int L = st.empty() ? 0 : st.back() + 1;
    ans += (P[R] % MOD) * (1ll * (R - L + 1) * (R - L) / 2 % MOD) % MOD;
    ans += (PP[R] - PP[L]) * (L - 1) % MOD;
    ans -= (PPP[R] - PPP[L]) % MOD;
    st.emplace_back(R);
  }
  cout << (ans % MOD + MOD) % MOD << '\n';
  return 0;
}

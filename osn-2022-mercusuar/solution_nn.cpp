#include <bits/stdc++.h>
using namespace std;

using lint = long long;
const lint INF = 1e18;

lint Solve(vector<int> A) {
  int N = A.size();
  auto coords = A;
  lint ansOptimal = INF;
  const auto Brute = [&](const auto &self, int u, lint cost) {
    if (u == N) {
      vector<int> st;
      vector<int> isValid(N);
      for (int i = 0; i < N; i++) {
        while (!st.empty() && A[st.back()] < A[i]) {
          st.pop_back();
        }
        if (!st.empty() && A[st.back()] == A[i]) {
          isValid[st.back()] = isValid[i] = 1;
        }
        st.emplace_back(i);
      }
      for (int i = 0; i < N; i++) {
        if (!isValid[i]) {
          return INF;
        }
      }
      ansOptimal = min(ansOptimal, cost);
      return cost;
    }
    lint ret = INF;
    for (auto c : coords) {
      if (A[u] <= c) {
        int old = A[u];
        A[u] = c;
        ret = min(ret, self(self, u + 1, cost + c - old));
        A[u] = old;
      }
    }
    return ret;
  };
  return Brute(Brute, 0, 0);
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

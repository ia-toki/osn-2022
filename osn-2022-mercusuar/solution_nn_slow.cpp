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
      bool bad = false;
      for (int i = 0; i < N; i++) {
        bool ok = false;
        for (int j = 0; j < N; j++) {
          if (i != j && A[i] == A[j]) {
            bool allLess = true;
            for (int k = min(i, j) + 1; k <= max(i, j) - 1; k++) {
              if (A[k] >= A[i]) {
                allLess = false;
              }
            }
            if (allLess) {
              ok = true;
            }
          }
        }
        if (!ok) {
          bad = true;
        }
      }
      if (bad) {
        return INF;
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

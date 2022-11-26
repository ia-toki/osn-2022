#include <bits/stdc++.h>
using namespace std;

using lint = long long;
const lint INF = 1e18;

lint Solve(vector<int> A) {
  int N = A.size();
  lint ans = 0;
  for (int i = N - 1; i >= 0; i--) {
    if (i == N - 1) {
      ans += A[i] - A[i - 1];
      A[i - 1] = A[i];
    } else if (i == 0) {
      ans += A[i + 1] - A[i];
      A[i] = A[i + 1];
    } else if (A[i + 1] - A[i] <= A[i] - A[i - 1]) {
      ans += A[i + 1] - A[i];
      A[i] = A[i + 1];
    } else {
      ans += A[i] - A[i - 1];
      A[i - 1] = A[i];
    }
  }
  return ans;
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

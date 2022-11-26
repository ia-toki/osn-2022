#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int N, Q;
  cin >> N >> Q;
  for (int q = 0; q < Q; q++) {
    long long X;
    cin >> X;
    long long ans = 0;

    // Case: [odd, even]
    if (X % (N + 1) == 0) {
      ans += max(0ll, N / 2 - X / (N + 1) + 1);
    }

    // Case: [even, odd]
    if (X % (N + 2) == 0) {
      ans += max(0ll, (N - 1) / 2 - X / (N + 2) + 1);
    }

    // Case: [odd, odd]
    ans += X % (N + 1) <= (N + 1) / 2 && X / (N + 1) <= X % (N + 1) - 1;

    // Case: [even, even]
    ans += X % (N + 2) >= (N + 3) / 2 && X / (N + 2) <= N - X % (N + 2);

    cout << ans << '\n';
  }
  return 0;
}

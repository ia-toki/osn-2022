#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100000;

int N;
long long A[MAX_N+5], W[MAX_N+5], V[MAX_N+5];
int pos[MAX_N+5];

int main() {
  ios_base::sync_with_stdio(0);
  cin >> N;
  for (int i = 1; i <= N; i++) cin >> A[i], pos[A[i]] = i;
  for (int i = 1; i <= N; i++) cin >> W[i];
  for (int i = 1; i <= N; i++) cin >> V[i];

  long long last = pos[1];
  long long mult = 1;
  long long tot = 0;
  for (int num = 1; num <= N; num++) {
    int idx = pos[num];
    tot += mult * (V[idx] + abs(last - idx));
    mult *= W[idx];
    last = idx;
  }
  cout << tot << "\n";
}

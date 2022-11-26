#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100000;

int N;
long long A[MAX_N+5], W[MAX_N+5], V[MAX_N+5];
int pos[MAX_N+5];

int main() {
  ios_base::sync_with_stdio(0);
  cin >> N;
  long long ans = 1e9;
  for (int i = 1; i <= N; i++) cin >> A[i];
  for (int i = 1; i <= N; i++) cin >> W[i];
  for (int i = 1; i <= N; i++) cin >> V[i], ans = min(ans, V[i]);
  
  cout << ans << "\n";
}

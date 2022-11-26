#include <iostream>
#include <vector>
#include <numeric>

using namespace std;
using ULL = unsigned long long;

int main()
{
  int N, M, Q;
  cin >> N >> M >> Q;
  vector<int> H(N);
  for (int i = 0; i < N; i++)
    cin >> H[i];

  ULL min = numeric_limits<ULL>::max();

  int idxMin = -1;

  for (int i = 0; i < N - 1; i++)
  {
    if (H[i] < min)
    {
      min = H[i];
      idxMin = i;
    }
  }

  cout << H[idxMin] + H[N - 1] << endl;

  if (Q == 1)
  {
    cout << 1 << endl;
    cout << idxMin + 1 << " " << N << endl;
  }

  return 0;
}
// solution-3

#include <bits/stdc++.h>

using namespace std;
using ULL = unsigned long long;

int main()
{
  int N, M, Q;
  cin >> N >> M >> Q;
  vector<ULL> H(N);
  for (int i = 0; i < N; i++)
    cin >> H[i];

  vector<pair<int, int>> kotaMin, kotaMax;
  for (int i = 0; i < N / 2; i++)
  {
    if (H[2 * i] > H[2 * i + 1])
      kotaMax.emplace_back(H[2 * i], 2 * i);
    else
      kotaMax.emplace_back(H[2 * i + 1], 2 * i + 1);
  }

  ULL total = accumulate(H.begin(), H.end(), ULL(0));
  sort(kotaMax.begin(), kotaMax.end());
  total -= kotaMax[N / 2 - 2].first + kotaMax[N / 2 - 1].first;

  int idxMax1 = kotaMax[N / 2 - 2].second;
  int idxMax2 = kotaMax[N / 2 - 1].second;

  int idxFirst, idxLast;
  if (idxMax1 % 2 == 0)
    idxFirst = idxMax1 + 1;
  else
    idxFirst = idxMax1 - 1;
  if (idxMax2 % 2 == 0)
    idxLast = idxMax2 + 1;
  else
    idxLast = idxMax2 - 1;

  int idxC1 = idxMax1 / 2;
  int idxC2 = idxMax2 / 2;

  vector<pair<int, int>> jembatan, pasangan;
  for (int i = 0; i < N / 2; i++)
  {
    if (i != idxC1 && i != idxC2)
      pasangan.emplace_back(2 * i, 2 * i + 1);
  }

  if (pasangan.empty())
    jembatan.emplace_back(idxFirst, idxLast);
  else
  {
    jembatan.emplace_back(idxFirst, pasangan[0].first);
    for (int i = 0; i < pasangan.size() - 1; i++)
      jembatan.emplace_back(pasangan[i].second, pasangan[i + 1].first);

    jembatan.emplace_back(pasangan[pasangan.size() - 1].second, idxLast);
  }
  cout
      << total << endl;

  cout << jembatan.size() << endl;
  for (const auto &[p, q] : jembatan)
    cout << p + 1 << " " << q + 1 << endl;
  return 0;
}
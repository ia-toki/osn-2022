// 2N + \sum_{i=1}^{N-1} ceil(log2(i)) + 3ceil(log2(N)) = 1161 queries
#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;
  map<pair<vector<int>, vector<int>>, int> memo;
  const auto Query = [&](vector<int> S, vector<int> T) {
    if (S.empty() || T.empty()) {
      return 0;
    }
    sort(begin(S), end(S));
    sort(begin(T), end(T));
    if (S > T) {
      swap(S, T);
    }
    if (memo.count({S, T})) {
      return memo[{S, T}];
    }
    vector<int> W(N);
    for (auto s : S) {
      W[s] = 1;
    }
    for (auto t : T) {
      W[t] = 2;
    }
    cout << '?';
    for (int i = 0; i < N; i++) {
      cout << ' ' << W[i];
    }
    cout << endl;
    int ret;
    cin >> ret;
    return memo[{S, T}] = ret;
  };
  int A = Query({0}, {1});
  int B = A;
  for (int b = 0; (1 << b) < N; b++) {
    vector<int> S, T;
    for (int i = 0; i < N; i++) {
      (((i >> b) & 1) ? S : T).emplace_back(i);
    }
    int sum = Query(S, T);
    if (sum != A * S.size() * T.size()) {
      while (S.size() > 1 || T.size() > 1) {
        if (S.size() > 1) {
          vector<int> S2(begin(S), begin(S) + S.size() / 2);
          if (Query(S2, T) != A * S2.size() * T.size()) {
            S.resize(S.size() / 2);
          } else {
            S.erase(begin(S), begin(S) + S.size() / 2);
          }
        } else {
          vector<int> T2(begin(T), begin(T) + T.size() / 2);
          if (Query(S, T2) != A * S.size() * T2.size()) {
            T.resize(T.size() / 2);
          } else {
            T.erase(begin(T), begin(T) + T.size() / 2);
          }
        }
      }
      B = Query(S, T);
      break;
    }
  }
  if (A > B) {
    swap(A, B);
  }
  if (A == B) {
    cout << '!' << ' ' << N - 1 << '\n';
    for (int i = 1; i < N; i++) {
      cout << 1 << ' ' << i + 1 << '\n';
    }
    cout << flush;
    return 0;
  }
  vector<int> vis(N);
  vector<pair<int, int>> ans;
  for (int s = 0; s < N; s++) {
    if (vis[s]) {
      continue;
    }
    vis[s] = 1;
    vector<int> S = {s};
    if (s != 0) {
      ans.emplace_back(0, s);
    }
    while (!S.empty()) {
      int S0 = S.back();
      vector<int> T;
      for (int i = 0; i < N; i++) {
        if (!vis[i]) {
          T.emplace_back(i);
        }
      }
      if (Query({S0}, T) == B * T.size()) {
        S.pop_back();
        continue;
      }
      while (T.size() > 1) {
        vector<int> T2(begin(T), begin(T) + T.size() / 2);
        if (Query({S0}, T2) != B * T2.size()) {
          T.resize(T.size() / 2);
        } else {
          T.erase(begin(T), begin(T) + T.size() / 2);
        }
      }
      ans.emplace_back(S0, T[0]);
      vis[T[0]] = 1;
      S.emplace_back(T[0]);
    }
  }
  cout << '!' << ' ' << ans.size() << '\n';
  for (auto [x, y] : ans) {
    cout << x + 1 << ' ' << y + 1 << '\n';
  }
  cout << flush;
  return 0;
}

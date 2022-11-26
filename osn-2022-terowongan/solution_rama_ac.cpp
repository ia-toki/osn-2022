// N + \sum_{i=1}^{N-1} ceil(log2(i)) = 997 queries
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
      int S0 = S[0];
      vector<int> T;
      for (int i = 0; i < N; i++) {
        if (!vis[i]) {
          T.emplace_back(i);
        }
      }
      int sum = Query({S0}, T);
      int sizeT = T.size();
      int numA = 0;
      if (A == B) {
        if (sum < A * T.size()) {
          int curSum = sum;
          while (T.size() > 1) {
            vector<int> T2(begin(T), begin(T) + T.size() / 2);
            if (Query({S0}, T2) != B * T2.size()) {
              curSum = Query({S0}, T2);
              T.resize(T.size() / 2);
            } else {
              curSum -= Query({S0}, T2);
              T.erase(begin(T), begin(T) + T.size() / 2);
            }
          }
          A = curSum;
          assert(A < B);
          numA -= 1;
          vis[T[0]] = 1;
          S.emplace_back(T[0]);
          ans.emplace_back(S0, T[0]);
          T.erase(begin(T));
        } else if (sum > A * T.size()) {
          while (!T.empty()) {
            B = Query({S0}, {T.back()});
            if (A == B) {
              numA -= 1;
              vis[T.back()] = 1;
              S.emplace_back(T.back());
              ans.emplace_back(S0, T.back());
              T.pop_back();
            } else {
              break;
            }
          }
          assert(A < B);
        } else {
          break;
        }
      }
      numA += sizeT - int(sum - A * sizeT) / (B - A);
      while (numA > 0) {
        numA -= 1;
        T.clear();
        for (int i = 0; i < N; i++) {
          if (!vis[i]) {
            T.emplace_back(i);
          }
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
      S.erase(begin(S));
    }
  }
  cout << '!' << ' ' << ans.size() << '\n';
  for (auto [x, y] : ans) {
    cout << x + 1 << ' ' << y + 1 << '\n';
  }
  cout << flush;
  return 0;
}

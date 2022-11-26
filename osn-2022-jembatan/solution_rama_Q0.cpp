#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M, Q;
  cin >> N >> M >> Q;
  vector<int> H(N);
  for (int i = 0; i < N; i++) {
    cin >> H[i];
  }
  vector<int> dsu(N, -1);
  function<int(int)> Find = [&](int x) {
    return dsu[x] < 0 ? x : dsu[x] = Find(dsu[x]);
  };
  int C = N;
  for (int i = 0; i < M; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    if (Find(u) != Find(v)) {
      C -= 1;
      dsu[Find(u)] = Find(v);
    }
  }
  if (C == 1) {
    cout << "0\n0\n";
    return 0;
  }
  long long ans = 0;
  vector<vector<int>> deg(N);
  vector<pair<int, int>> all;
  vector<vector<pair<int, int>>> ls(N);
  for (int i = 0; i < N; i++) {
    ls[Find(i)].emplace_back(H[i], i);
  }
  for (int i = 0; i < N; i++) {
    if (ls[i].empty()) {
      continue;
    }
    auto mn = min_element(begin(ls[i]), end(ls[i]));
    deg[i].emplace_back(mn->second);
    ans += mn->first;
    ls[i].erase(mn);
    all.insert(end(all), begin(ls[i]), end(ls[i]));
  }
  if (int(all.size()) < C - 2) {
    cout << "-1\n";
    return 0;
  }
  sort(begin(all), end(all));
  for (int i = 0; i < C - 2; i++) {
    ans += all[i].first;
    deg[Find(all[i].second)].emplace_back(all[i].second);
  }
  vector<int> que;
  vector<int> cand;
  for (int i = 0; i < N; i++) {
    if (deg[i].size() == 1) {
      que.emplace_back(i);
    } else if (deg[i].size() > 1) {
      cand.emplace_back(i);
    }
  }
  vector<pair<int, int>> edge;
  while (!que.empty()) {
    int i = que.back();
    que.pop_back();
    if (cand.empty()) {
      assert(que.size() == 1);
      int j = que.back();
      que.pop_back();
      edge.emplace_back(i, j);
    } else {
      int j = deg[cand.back()].back();
      edge.emplace_back(i, j);
      deg[cand.back()].pop_back();
      if (deg[cand.back()].size() == 1) {
        que.emplace_back(deg[cand.back()][0]);
        cand.pop_back();
      }
    }
  }
  cout << ans << '\n';
  return 0;
}

#include <bits/stdc++.h>
using namespace std;

using lint = long long;
const lint INF = 1e18;

lint Solve(vector<int> A) {
  int N = A.size();
  vector<int> V(N), IV(N);
  iota(begin(V), end(V), 0);
  sort(begin(V), end(V),
       [&A](int i, int j) { return pair(A[i], i) < pair(A[j], j); });
  for (int i = 0; i < N; i++) {
    IV[V[i]] = i;
  }
  vector<int> seg(2 * N);
  for (int i = 0; i < N; i++) {
    seg[N + i] = IV[i];
  }
  for (int i = N - 1; i > 0; i--) {
    seg[i] = max(seg[i * 2], seg[i * 2 + 1]);
  }
  vector<int> parent_list;
  map<array<int, 5>, lint> memo;
  const auto f = [&](const auto &f, int l, int r) {
    if (l > r) {
      return;
    }

    int s = -1;
    for (int i = l + N, j = r + N + 1; i < j; i /= 2, j /= 2) {
      if (i & 1) s = max(s, seg[i++]);
      if (j & 1) s = max(s, seg[--j]);
    }
    assert(s != -1);
    s = V[s];
    assert(l <= s && s <= r);

    parent_list.emplace_back(s);

    f(f, l, s - 1);
    f(f, s + 1, r);

    // I cannot prove this is correct (i.e. we take the 3 ancestors and
    // left/right endpoints)
    vector<int> Xs = {N};
    for (int xid = 0; xid < 4 && xid < int(parent_list.size()); xid++) {
      int x = parent_list[int(parent_list.size()) - 1 - xid];
      Xs.emplace_back(IV[x]);
    }
    if (l > 0) Xs.emplace_back(IV[l - 1]);
    if (r + 1 < N) Xs.emplace_back(IV[r + 1]);
    const auto lft = [&](int x, int cl, int cr) {
      if (l > s - 1) {
        return cl == 0 || cr == 0 ? INF : 0;
      }
      if (memo.count({l, s - 1, x, cl, cr})) {
        return memo[{l, s - 1, x, cl, cr}];
      }
      return INF;
    };
    const auto rgt = [&](int x, int cl, int cr) {
      if (s + 1 > r) {
        return cl == 0 || cr == 0 ? INF : 0;
      }
      if (memo.count({s + 1, r, x, cl, cr})) {
        return memo[{s + 1, r, x, cl, cr}];
      }
      return INF;
    };

    for (int x : Xs) {
      for (int cl = 0; cl < 2; cl++) {
        for (int cr = 0; cr < 2; cr++) {
          lint &ret = memo[{l, r, x, cl, cr}];
          ret = INF;

          // Case: do not increase A[s]
          ret = min(ret, lft(IV[s], cl, 0) + rgt(IV[s], 1, cr));
          ret = min(ret, lft(IV[s], cl, 1) + rgt(IV[s], 0, cr));

          // Case: increase A[s] to A[V[x]]
          if (x < N) {
            assert(A[s] <= A[V[x]]);
            ret = min(ret, A[V[x]] - A[s] + lft(x, cl, 1) + rgt(x, 1, cr));
          }

          // Case: increase A[s] to A[l - 1]
          if (cl == 0 && l > 0) {
            assert(A[l - 1] >= A[s]);
            ret = min(ret, A[l - 1] - A[s] + lft(IV[l - 1], 1, 1) +
                               rgt(min(x, IV[l - 1]), 1, cr));
          }

          // Case: increase A[s] to A[r + 1]
          if (cr == 0 && r < N - 1) {
            assert(A[r + 1] >= A[s]);
            ret = min(ret, A[r + 1] - A[s] + lft(min(x, IV[r + 1]), cl, 1) +
                               rgt(IV[r + 1], 1, 1));
          }
        }
      }
    }
    parent_list.pop_back();
    return;
  };
  f(f, 0, N - 1);
  lint ans = memo[{0, N - 1, N, 1, 1}];
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

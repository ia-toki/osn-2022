#include <bits/stdc++.h>
using namespace std;

using lint = long long;
const lint INF = 1e18;

lint Solve(vector<int> A) {
  int N = A.size();
  auto V = A;
  sort(begin(V), end(V));
  V.resize(unique(begin(V), end(V)) - begin(V));
  const auto Get = [&](int x) -> int {
    return lower_bound(begin(V), end(V), x) - begin(V);
  };
  vector<int> seg(2 * N);
  map<int, vector<int>> occ;
  for (int i = 0; i < N; i++) {
    seg[N + i] = A[i];
    occ[A[i]].emplace_back(i);
  }
  for (int i = N - 1; i >= 0; i--) {
    seg[i] = max(seg[i * 2], seg[i * 2 + 1]);
  }
  map<array<int, 5>, lint> memo;
  const auto f = [&](const auto &f, int l, int r, int cl, int cr, int x) {
    if (l > r) {
      return cl == 0 || cr == 0 ? INF : 0;
    }
    if (x < 0) {
      return INF;
    }
    if (memo.count({l, r, cl, cr, x})) {
      return memo[{l, r, cl, cr, x}];
    }
    lint &ret = memo[{l, r, cl, cr, x}];
    ret = INF;
    int mx = -1;
    for (int i = l + N, j = r + N + 1; i < j; i /= 2, j /= 2) {
      if (i & 1) mx = max(mx, seg[i++]);
      if (j & 1) mx = max(mx, seg[--j]);
    }
    auto lb = lower_bound(begin(occ[mx]), end(occ[mx]), l);
    auto rb = prev(upper_bound(begin(occ[mx]), end(occ[mx]), r));
    if (cl == 1 && cr == 1) {
      if (lb != rb) {
        lint sum = 0;
        int nxt = lower_bound(begin(V), end(V), mx) - begin(V);
        sum += f(f, l, *lb - 1, 1, 1, nxt);
        sum += f(f, *lb + 1, r, 1, 1, nxt);
        ret = min(ret, sum);
      } else {
        int s = *lb;
        if (x < int(V.size())) {
          assert(A[s] <= V[x]);
          ret = min(ret, V[x] - A[s] + f(f, l, s - 1, 1, 1, x) +
                             f(f, s + 1, r, 1, 1, x));
        }
        int nxt = lower_bound(begin(V), end(V), mx) - begin(V);
        ret = min(ret, f(f, l, s - 1, 1, 0, nxt) + f(f, s + 1, r, 1, 1, nxt));
        ret = min(ret, f(f, l, s - 1, 1, 1, nxt) + f(f, s + 1, r, 0, 1, nxt));
      }
    }
    if (cl == 0) {
      int s = *lb;
      int v = A[l - 1];
      assert(A[s] <= v);
      {
        lint sum = 0;
        sum += v - A[s];
        sum += f(f, l, s - 1, 1, 1, Get(v));
        sum += f(f, s + 1, r, 1, cr, min(x, Get(v)));
        ret = min(ret, sum);
      }
      if (lb != rb) {
        lint sum = 0;
        sum += f(f, l, s - 1, cl, 1, Get(A[s]));
        sum += f(f, s + 1, r, 1, cr, Get(A[s]));
        ret = min(ret, sum);
      } else {
        ret = min(ret, f(f, l, s - 1, cl, 0, Get(A[s])) +
                           f(f, s + 1, r, 1, cr, Get(A[s])));
        ret = min(ret, f(f, l, s - 1, cl, 1, Get(A[s])) +
                           f(f, s + 1, r, 0, cr, Get(A[s])));
        ret = min(ret, V[x] - A[s] + f(f, l, s - 1, cl, 1, x) +
                           f(f, s + 1, r, 1, cr, x));
      }
    }
    if (cr == 0) {
      int s = *rb;
      int v = A[r + 1];
      assert(A[s] <= v);
      {
        lint sum = 0;
        sum += v - A[s];
        sum += f(f, s + 1, r, 1, 1, Get(v));
        sum += f(f, l, s - 1, cl, 1, min(x, Get(v)));
        ret = min(ret, sum);
      }
      if (lb != rb) {
        lint sum = 0;
        sum += f(f, l, s - 1, cl, 1, Get(A[s]));
        sum += f(f, s + 1, r, 1, cr, Get(A[s]));
        ret = min(ret, sum);
      } else {
        ret = min(ret, f(f, l, s - 1, cl, 0, Get(A[s])) +
                           f(f, s + 1, r, 1, cr, Get(A[s])));
        ret = min(ret, f(f, l, s - 1, cl, 1, Get(A[s])) +
                           f(f, s + 1, r, 0, cr, Get(A[s])));
        ret = min(ret, V[x] - A[s] + f(f, l, s - 1, cl, 1, x) +
                           f(f, s + 1, r, 1, cr, x));
      }
    }
    return ret;
  };
  lint ans = f(f, 0, N - 1, 1, 1, V.size());
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

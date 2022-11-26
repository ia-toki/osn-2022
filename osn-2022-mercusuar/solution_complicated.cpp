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
  const auto f = [&](const auto &f, int l, int r, int cl, int cr, int cx) {
    assert(cx <= 2);
    if (l > r) {
      return cl == 0 || cr == 0 ? INF : 0;
    }
    if (cx < 0) {
      return INF;
    }
    if (memo.count({l, r, cl, cr, cx})) {
      return memo[{l, r, cl, cr, cx}];
    }
    lint &ret = memo[{l, r, cl, cr, cx}];
    ret = INF;
    int mx = -1;
    for (int i = l + N, j = r + N + 1; i < j; i /= 2, j /= 2) {
      if (i & 1) mx = max(mx, seg[i++]);
      if (j & 1) mx = max(mx, seg[--j]);
    }
    auto lb = lower_bound(begin(occ[mx]), end(occ[mx]), l);
    auto rb = prev(upper_bound(begin(occ[mx]), end(occ[mx]), r));
    const auto GetMin = [&f, &V](int l, int r, int cl, int cr, int x) {
      return min({f(f, l, r, cl, cr, 0), f(f, l, r, cl, cr, 1) + V[x],
                  f(f, l, r, cl, cr, 2) + V[x] + V[x]});
    };
    if (cl == 1 && cr == 1) {
      int nxt = lower_bound(begin(V), end(V), mx) - begin(V);
      if (lb != rb) {
        lint sum = 0;
        sum += GetMin(l, *lb - 1, 1, 1, nxt);
        sum += GetMin(*lb + 1, r, 1, 1, nxt);
        ret = min(ret, sum);
      } else {
        int s = *lb;
        if (cx > 0) {
          for (int cxl = 0; cxl <= 2; cxl++) {
            for (int cxr = 0; cxr <= 2; cxr++) {
              if (cxl + cxr == cx - 1) {
                ret = min(ret, -A[s] + f(f, l, s - 1, 1, 1, cxl) +
                                   f(f, s + 1, r, 1, 1, cxr));
              }
            }
          }
        }
        ret =
            min(ret, GetMin(l, s - 1, 1, 0, nxt) + GetMin(s + 1, r, 1, 1, nxt));
        ret =
            min(ret, GetMin(l, s - 1, 1, 1, nxt) + GetMin(s + 1, r, 0, 1, nxt));
      }
    }
    if (cl == 0) {
      int s = *lb;
      int v = A[l - 1];
      assert(A[s] <= v);
      {
        lint sum = 0;
        sum += v - A[s];
        sum += GetMin(l, s - 1, 1, 1, Get(v));
        sum += min(GetMin(s + 1, r, 1, cr, Get(v)), f(f, s + 1, r, 1, cr, cx));
        ret = min(ret, sum);
      }
      if (lb != rb) {
        lint sum = 0;
        sum += GetMin(l, s - 1, cl, 1, Get(A[s]));
        sum += GetMin(s + 1, r, 1, cr, Get(A[s]));
        ret = min(ret, sum);
      } else {
        ret = min(ret, GetMin(l, s - 1, cl, 0, Get(A[s])) +
                           GetMin(s + 1, r, 1, cr, Get(A[s])));
        ret = min(ret, GetMin(l, s - 1, cl, 1, Get(A[s])) +
                           GetMin(s + 1, r, 0, cr, Get(A[s])));
        if (cx > 0) {
          for (int cxl = 0; cxl <= 2; cxl++) {
            for (int cxr = 0; cxr <= 2; cxr++) {
              if (cxl + cxr == cx - 1) {
                ret = min(ret, -A[s] + f(f, l, s - 1, cl, 1, cxl) +
                                   f(f, s + 1, r, 1, cr, cxr));
              }
            }
          }
        }
      }
    }
    if (cr == 0) {
      int s = *rb;
      int v = A[r + 1];
      assert(A[s] <= v);
      {
        lint sum = 0;
        sum += v - A[s];
        sum += GetMin(s + 1, r, 1, 1, Get(v));
        sum += min(GetMin(l, s - 1, cl, 1, Get(v)), f(f, l, s - 1, cl, 1, cx));
        ret = min(ret, sum);
      }
      if (lb != rb) {
        lint sum = 0;
        sum += GetMin(l, s - 1, cl, 1, Get(A[s]));
        sum += GetMin(s + 1, r, 1, cr, Get(A[s]));
        ret = min(ret, sum);
      } else {
        ret = min(ret, GetMin(l, s - 1, cl, 0, Get(A[s])) +
                           GetMin(s + 1, r, 1, cr, Get(A[s])));
        ret = min(ret, GetMin(l, s - 1, cl, 1, Get(A[s])) +
                           GetMin(s + 1, r, 0, cr, Get(A[s])));
        if (cx > 0) {
          for (int cxl = 0; cxl <= 2; cxl++) {
            for (int cxr = 0; cxr <= 2; cxr++) {
              if (cxl + cxr == cx - 1) {
                ret = min(ret, -A[s] + f(f, l, s - 1, cl, 1, cxl) +
                                   f(f, s + 1, r, 1, cr, cxr));
              }
            }
          }
        }
      }
    }
    return ret;
  };
  lint ans = f(f, 0, N - 1, 1, 1, 0);
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

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
    for (int i = l; i <= r; i++) {
      mx = max(mx, A[i]);
    }
    vector<int> S;
    for (int i = l; i <= r; i++) {
      if (A[i] == mx) {
        S.emplace_back(i);
      }
    }
    if (cl == 1 && cr == 1) {
      if (S.size() >= 2) {
        lint sum = 0;
        int nxt = lower_bound(begin(V), end(V), mx) - begin(V);
        sum += f(f, l, S[0] - 1, 1, 1, nxt);
        sum += f(f, end(S)[-1] + 1, r, 1, 1, nxt);
        for (int i = 1; i < int(S.size()); i++) {
          sum += f(f, S[i - 1] + 1, S[i] - 1, 1, 1, nxt);
        }
        ret = min(ret, sum);
      } else {
        int s = S[0];
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
      int s = S[0];
      int v = A[l - 1];
      assert(A[s] <= v);
      {
        lint sum = 0;
        sum += v - A[s];
        sum += f(f, l, s - 1, 1, 1, Get(v));
        sum += f(f, s + 1, r, 1, cr, min(x, Get(v)));
        ret = min(ret, sum);
      }
      if (S.size() >= 2) {
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
      int s = S.back();
      int v = A[r + 1];
      assert(A[s] <= v);
      {
        lint sum = 0;
        sum += v - A[s];
        sum += f(f, s + 1, r, 1, 1, Get(v));
        sum += f(f, l, s - 1, cl, 1, min(x, Get(v)));
        ret = min(ret, sum);
      }
      if (S.size() >= 2) {
        int s = S.back();
        lint sum = 0;
        sum += f(f, l, s - 1, cl, 1, Get(A[s]));
        sum += f(f, s + 1, r, 1, cr, Get(A[s]));
        ret = min(ret, sum);
      } else {
        int s = S.back();
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

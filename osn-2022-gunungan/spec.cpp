#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <tcframe/spec.hpp>

using namespace std;
using namespace __gnu_pbds;
using namespace tcframe;

typedef tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef pair<int, int> pii;

const int MAX_Nsub4 = 2e3;
const int MAX_N = 1e5;
const int MAX_W = 1e9;
const int MAX_V = 1e9;
const long long MAX_ANS = 1e18;

mt19937 rng;

namespace solution {

const int MAX_N = 1e5;
const long long MAX_ANS = 1e18;

long long multiply(long long a, long long b) {
  if (a == 0 || b == 0) return 0;
  if (a > MAX_ANS || b > MAX_ANS) return MAX_ANS+1;
  if (a > MAX_ANS / b) return MAX_ANS+1;
  return a * b > MAX_ANS ? MAX_ANS + 1 : a * b;
}

int N, M;
int A[MAX_N + 5], W[MAX_N + 5], V[MAX_N + 5];
long long dp[MAX_N + 5];
vector<int> colorGroup[100005];

void compress() {
  vector<int> tmp;
  for (int i = 1; i <= N; i++) {
    tmp.emplace_back(A[i]);
  }

  sort(tmp.begin(), tmp.end());
  tmp.resize(unique(tmp.begin(), tmp.end()) - tmp.begin());

  M = tmp.size();
  for (int i = 1; i <= N; i++) {
    A[i] = upper_bound(tmp.begin(), tmp.end(), A[i]) - tmp.begin();
  }
}

int getNextIdx(int &p_1, int &p_2, vector<int> &vec1, vector<int> &vec2) {
  assert(p_1 < vec1.size() || p_2 < vec2.size());
  if (p_2 >= vec2.size()) return vec1[p_1++];
  if (p_1 >= vec1.size()) return vec2[p_2++];
  if (vec1[p_1] < vec2[p_2]) return vec1[p_1++];
  return vec2[p_2++];
}

void solve(int color) {
  if (color == M) {
    for (int idx : colorGroup[color]) {
      dp[idx] = V[idx];
    }
    return;
  }

  int p_1=0, p_2=0;
  vector<int> vec;
  while (p_1 < colorGroup[color].size() || p_2 < colorGroup[color+1].size()) {
    vec.emplace_back(getNextIdx(p_1, p_2, colorGroup[color], colorGroup[color+1]));
  }

  // iteration from the front for i > j cases;
  // perlu diperhatikan bug "optimal di normalize".
  long long optimal = 2e18;
  for (int i = 0; i < vec.size(); i++) {
    int idx = vec[i];
    if (A[idx] == color) {
      dp[idx] = min(dp[idx], multiply(optimal - (N - idx), W[idx]) + V[idx]);
    }else {
      optimal = min(optimal, dp[idx] + (N - idx));
    }
  }

  // iterate from behind
  optimal = 2e18;
  for (int i = vec.size()-1; i >= 0; i--) {
    int idx = vec[i];
    if (A[idx] == color) {
      dp[idx] = min(dp[idx], multiply(optimal - idx, W[idx]) + V[idx]);
    }else {
      optimal = min(optimal, dp[idx] + idx);
    }
  }
}

long long solveAll() {
  for (int i = M; i >= 1; i--) {
    solve(i);
  }

  long long ans = 2e18;
  for (int i = 1; i <= N; i++) {
    if (A[i] == 1) ans = min(ans, dp[i]);
  }

  return ans;
}

long long calculateSolution(int N, std::vector<int> A, std::vector<int> W, std::vector<int> V) {
  solution::N = N;
  for (int i = 0; i < N; i++) solution::A[i+1] = A[i];
  for (int i = 0; i < N; i++) solution::W[i+1] = W[i];
  for (int i = 0; i < N; i++) solution::V[i+1] = V[i];
  compress();

  for (int i = 1; i <= N; i++) {
    colorGroup[solution::A[i]].emplace_back(i);
  }
  memset(dp, 0x3f3f3f3fLL, sizeof(dp));
  long long ans = solveAll();
  
  for (int i = 1; i <= N; i++) colorGroup[i].clear();
  return ans;
}

}

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N;
  vector<int> A, W, V;

  long long ans;

  void InputFormat() {
    LINE(N);
    LINE(A % SIZE(N));
    LINE(W % SIZE(N));
    LINE(V % SIZE(N));
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAX_N);
    CONS(eachElementBetween(A, 1, N));
    CONS(eachElementBetween(W, 1, MAX_W));
    CONS(eachElementBetween(V, 1, MAX_V));
    CONS(solution::calculateSolution(N, A, W, V) <= MAX_ANS);
  }

  void Subtask1() {
    CONS(N == 9);
    CONS(A == vector<int>({1, 2, 4, 3, 5, 3, 6, 1, 2}));
    CONS(W == vector<int>({1, 2, 1, 3, 1, 3, 1, 1, 2}));
    CONS(V == vector<int>({3, 3, 1, 5, 5, 5, 1, 3, 3}));
    Points(9);
  }

  void Subtask2() {
    CONS(eachElementBetween(A, 1, 1));
    Points(4);
  }

  void Subtask3() {
    CONS(isPermutation(A));
    Points(10);
  }

  void Subtask4() {
    CONS(N <= MAX_Nsub4);
    CONS(eachElementBetween(W, 1, 2));
    Points(14);
  }

  void Subtask5() {
    CONS(N <= MAX_Nsub4);
    Points(27);
  }

  void Subtask6() {
    CONS(eachElementBetween(W, 1, 1));
    Points(17);
  }

  void Subtask7() {
    Points(19);
  }

  private:
  bool eachElementBetween(const vector<int> &A, int down, int up) {
    for (int a: A) {
      if (a < down || a > up) return false;
    }
    return true;
  }

  bool isPermutation(const vector<int> &A) {
    vector<int> B = A;
    sort(B.begin(), B.end());
    return unique(B.begin(), B.end()) == B.end();
  }

  bool eachElementMaxCount(const vector<int> &A, int max_cnt) {
    map<int, int> cnt;
    for (int num : A) {
      cnt[num]++;
      if (cnt[num] > max_cnt) return false;
    }
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  bool do_shuffle = false;

  void SampleTestCase1() {
    Subtasks({5 , 7});
    Input({
      "3",
      "1 1 2",
      "5 4 5",
      "3 2 10",
    });
    Output({
      "46",
    });
  }

  void SampleTestCase2() {
    Subtasks({5, 7});
    Input({
      "8",
      "1 3 5 2 1 3 3 5",
      "2 2 4 1 2 3 3 5",
      "4 8 1 6 7 1 1 2",
    });
    Output({
      "47",
    });
  }

  void BeforeTestCase() {
    multRandModifier = defMultRandModifier;
    do_shuffle = true;
    A.clear();
    W.clear();
    V.clear();
  }

  void AfterTestCase() {
    // shuffle the numeration (still maintaining the order)
    if (do_shuffle == false) return;
    vector<int> palet(N);
    for (int i = 0; i < N; i++) palet[i] = i+1;
    rnd.shuffle(palet.begin(), palet.end());

    int mx_A = *max_element(A.begin(), A.end());
  
    sort(palet.begin(), palet.begin() + mx_A);
    for (int i = 0; i < N; i++) {
      A[i] = palet[A[i] - 1];
    }
  }

  void TestGroup1() {
    Subtasks({1, 5, 7});

    CASE(N = 9, do_shuffle = false, 
      A = {1, 2, 4, 3, 5, 3, 6, 1, 2},
      W = {1, 2, 1, 3, 1, 3, 1, 1, 2},
      V = {3, 3, 1, 5, 5, 5, 1, 3, 3}
    );
  }

  // Smallest TC N = 1
  // A_i != A_j, A_i = 1, W_i = 1, N <= 5000
  void TestGroup2() {
    Subtasks({2, 3, 4, 5, 6, 7});

    CASE(N = 1, A = {1}, W = {1}, V = {MAX_V});
  }

  // A_1 = 1, W = 1, N <= 5000
  void TestGroup3() {
    Subtasks({2, 4, 5, 6, 7});

    CASE(N = MAX_Nsub4, do_shuffle = false,
      randArray(A, 1, 1),
      randArray(W, 1, 1),
      randArray(V, MAX_V-100, MAX_V)
    );
  }

  // A_i = 1, W = 1
  void TestGroup4() {
    Subtasks({2, 6, 7});

    // first element is the answer
    CASE(N = MAX_N, do_shuffle = false,
      randArray(A, 1, 1),
      randArray(W, 1, 1),
      randArray(V, MAX_V/2, MAX_V-1), V[0] = MAX_V/3
    );

    // last element is the answer
    CASE(N = MAX_N, do_shuffle = false,
      randArray(A, 1, 1),
      randArray(W, 1, 1),
      randArray(V, MAX_V/3, MAX_V-1), V.back() = MAX_V/4
    );

    CASE(N = MAX_N, do_shuffle = false,
      randArray(A, 1, 1),
      randArray(W, 1, 1),
      randArray(V, 1, MAX_V)
    );
  }

  // A_i = 1
  void TestGroup5() {
    Subtasks({2, 7});

    // all element is the same
    CASE(N = MAX_N, do_shuffle = false,
      randArray(A, 1, 1),
      randArray(W, 1, MAX_W),
      randArray(V, MAX_V, MAX_V)
    );

    // MAX_W for all
    CASE(N = MAX_N, do_shuffle = false,
      randArray(A, 1, 1),
      randArray(W, MAX_W, MAX_W),
      randArray(V, 1, MAX_V)
    );
  }

  // A_1 != A_j, W == 1
  void TestGroup6() {
    Subtasks({3, 6, 7});

    CASE(MaxAnsW1Case());
  }

  // A_1 != A_j, N <= 5000, W <= 2
  void TestGroup7() {
    Subtasks({3, 4, 5, 7});

    CASE(MaxAnsW2Case());
    
    CASE(
      initRandom(MAX_Nsub4),
      randomValidPath(N, pureRand1, 2)
    );
  }

  // A_i != A_j
  void TestGroup8() {
    Subtasks({3, 7});

    CASE(
      initRandom(randInt(MAX_N-50, MAX_N)),
      randomValidPath(N, pureRand2, 1000, {1, 1000})
    );

    CASE(
      initRandom(randInt(MAX_N-50, MAX_N)),
      randomValidPath(N, pureRand4, 1000, {1, 1000})
    );

    CASE(
      initRandom(randInt(MAX_N-50, MAX_N)),
      randomValidPath(N, pureRand8, 100, {1, 100})
    );

    CASE(
      initRandom(randInt(MAX_N-50, MAX_N)),
      randomValidPath(N, pureRand8)
    );

    CASE(
      initRandom(randInt(MAX_N-50, MAX_N)),
      randomValidPath(N, positionRand)
    );
  }

  // W <= 2, N <= 5000
  void TestGroup9() {
    Subtasks({4, 5, 7});

    // small V, large path
    CASE(
      N = randInt(MAX_Nsub4-50, MAX_Nsub4),
      initRandom(N, {1, N/10}, {1, 2}, {1, 50}), randArray12(W, 1, 1000), decreaseOneWithBigW(1),
      randomValidPaths(5, N/10, positionRand, 2, {1, 50})
    );

    CASE(
      N = randInt(MAX_Nsub4-50, MAX_Nsub4),
      initRandom(N, {1, N/100}, {1, 2}, {1, 100}), randArray12(W, 1, 100), decreaseOneWithBigW(1),
      randomValidPaths(5, N/100, pureRand2, 2, {1, 100})
    );

    // --- over twnty layers ---
    CASE(
      N = randInt(MAX_Nsub4-50, MAX_Nsub4),
      initRandom(N, {1, 75}, {1, 2}), randArray12(W, 1, 5), decreaseOneWithBigW(1),
      randomValidPaths(5, 75, pureRand1, 2, {1, 1000000})
    );

    CASE(
      N = randInt(MAX_Nsub4-50, MAX_Nsub4),
      initRandom(N, {1, 25}, {1, 2}), randArray12(W, 1, 4), decreaseOneWithBigW(1),
      randomValidPaths(5, 25, pureRand1, 2)
    );

    CASE(
      N = randInt(MAX_Nsub4-50, MAX_Nsub4),
      initRandom(N, {1, 10}, {1, 2}), randArray12(W, 1, 3), decreaseOneWithBigW(1),
      randomValidPaths(5, 10, pureRand1, 2)
    );

    // without valid path maker
    // all 2 with random
    CASE(
      N = randInt(MAX_Nsub4-50, MAX_Nsub4),
      pureRandom(N, {1, 35}, {2, 2})
    );

    CASE(
      N = randInt(MAX_Nsub4-50, MAX_Nsub4),
      pureRandom(N, {1, 45}, {2, 2}, {1, 1000})
    );

    // 1 and 2 with pure random
    CASE(
      N = randInt(MAX_Nsub4-50, MAX_Nsub4),
      pureRandom(N, {1, 30}, {1, 2})
    );

    CASE(
      N = randInt(MAX_Nsub4-50, MAX_Nsub4),
      pureRandom(N, {1, 85}, {1, 2})
    );
  }

  // N <= 5000
  void TestGroup10() {
    Subtasks({5, 7});

    // pure random but small tcs
    CASE(
      N = randInt(MAX_Nsub4-50, MAX_Nsub4),
      pureRandom(N, {1, 30}, {1, 250})
    );

    CASE(
      N = randInt(MAX_Nsub4-50, MAX_Nsub4),
      pureRandom(N, {1, 85}, {1, 20})
    );

    // ---- case with long path ----
    CASE(
      N = randInt(MAX_Nsub4-50, MAX_Nsub4),
      initRandom(N, {1, N/20}, {1, 1000}, {1, 1000}),
      randomValidPath(N/20, pureRand2, 1000, {1, 1000})
    );

    CASE(
      N = randInt(MAX_Nsub4-50, MAX_Nsub4),
      initRandom(N, {1, N/10}, {1, 100000}, {1, 100000}),
      randomValidPath(N/10, pureRand4)
    );

    CASE(
      N = randInt(MAX_Nsub4-50, MAX_Nsub4),
      initRandom(N, {1, N/6}, {1, 100}, {1, 100}),
      randomValidPath(N/6, pureRand8)
    );

    CASE(
      N = randInt(MAX_Nsub4-50, MAX_Nsub4),
      initRandom(N, {1, N/10}, {1, 10000}, {1, 10000}),
      randomValidPath(N/10, positionRand, 1000, {1, 10000})
    );

    CASE(
      N = randInt(MAX_Nsub4-50, MAX_Nsub4),
      initRandom(N, {1, N/10}),
      randomValidPath(N/10, positionRand)
    );

    // ---- case with short valid path ----
    CASE(
      N = randInt(MAX_Nsub4-50, MAX_Nsub4),
      initRandom(N, {1, N/100}, {1, MAX_W/1000}, {1, MAX_V/1000}),
      randomValidPath(N/100, positionRand)
    );

    CASE(
      N = randInt(MAX_Nsub4-50, MAX_Nsub4),
      initRandom(N, {1, N/100}, {1, MAX_W/1000}, {1, MAX_V/1000}),
      randomValidPath(N/100, pureRand2)
    );

    // ---- multiple valid path ----
    CASE(
      N = randInt(MAX_Nsub4-50, MAX_Nsub4),
      initRandom(N, {1, N/100}, {1, MAX_W/1000}, {1, MAX_V/1000}),
      randomValidPaths(5, N/100, pureRand2)
    );

    CASE(
      N = randInt(MAX_Nsub4-50, MAX_Nsub4),
      initRandom(N, {1, N/100}, {1, MAX_W/1000}, {1, MAX_V/1000}),
      randomValidPaths(3, N/100, pureRand1)
    );

    // ---- even smaller path ----
    CASE(
      N = randInt(MAX_Nsub4-50, MAX_Nsub4),
      initRandom(N, {1, N/500}),
      multRandModifier = {1, 2, 2},
      randomValidPaths(3, N/500, pureRand1)
    );

    CASE(
      N = randInt(MAX_Nsub4-50, MAX_Nsub4),
      initRandom(N, {1, N/1000}, {1, 10000}, {1, 10000}),
      multRandModifier = {1, 1, 2},
      randomValidPaths(5, N/1000, pureRand1)
    );

    // smaller random W and V
    CASE(
      N = randInt(MAX_Nsub4-50, MAX_Nsub4),
      initRandom(N, {1, N/1000}, {1, 100}, {1, 100}),
      multRandModifier = {2, 2, 2},
      randomValidPaths(5, N/1000, pureRand1)
    );

    // always the smallest modifier in binomial dist
    CASE(
      N = randInt(MAX_Nsub4-50, MAX_Nsub4),
      initRandom(N, {1, N/100}, {1, 100}, {1, 100}),
      multRandModifier = {0, 3, 10},
      randomValidPaths(5, N/100, pureRand1, 100)
    );

    CASE(
      N = randInt(MAX_Nsub4-50, MAX_Nsub4),
      initRandom(N, {1, N/100}, {1, 50}, {1, 50}),
      multRandModifier = {0, 3, 10},
      randomValidPaths(5, N/100, pureRand1, 100, {1, 50})
    );

    // 2 types only, always valid no matter what
    CASE(
      N = MAX_Nsub4,
      initRandom(N, {1, 2}, {999, 1000})
    );
  }

  // W == 1
  void TestGroup11() {
    Subtasks({6, 7});

    CASE(N = MAX_N, initRandom(N, {1, N-1}, {1, 1}));
    CASE(N = MAX_N, initRandom(N, {1, N/2}, {1, 1}));
    CASE(N = MAX_N-1, initRandom(N, {1, N/20}, {1, 1}, {1, 100}));
    CASE(N = rnd.nextInt(MAX_N-50, MAX_N), initRandom(N, {1, N/100}, {1, 1}, {1, 1000}));
    CASE(N = rnd.nextInt(MAX_N-50, MAX_N), initRandom(N, {1, N/5000}, {1, 1}, {1, 10000}));
    CASE(N = rnd.nextInt(MAX_N-50, MAX_N), initRandom(N, {1, 4}, {1, 1}, {1, 100000}));
    CASE(N = MAX_N, initRandom(N, {1, 2}, {1, 1}, {MAX_V/2, MAX_V}));
  }

  // no additional constraint
  void TestGroup12() {
    Subtasks({7});

    // 1 and 2 with pure random
    CASE(
      N = randInt(MAX_N-50, MAX_N),
      pureRandom(N, {1, 40}, {1, 2})
    );

    CASE(
      N = randInt(MAX_N-50, MAX_N),
      pureRandom(N, {1, 350}, {1, 2})
    );

    CASE(
      N = randInt(MAX_N-50, MAX_N),
      pureRandom(N, {1, 5000}, {1, 2})
    );

    // pure random but small tcs
    CASE(
      N = randInt(MAX_N-50, MAX_N),
      pureRandom(N, {1, 40}, {1, 6000})
    );

    CASE(
      N = randInt(MAX_N-50, MAX_N),
      pureRandom(N, {1, 100}, {1, 900})
    );

    CASE(
      N = randInt(MAX_N-50, MAX_N),
      pureRandom(N, {1, 350}, {1, 130})
    );

    CASE(
      N = randInt(MAX_N-50, MAX_N),
      pureRandom(N, {1, 1000}, {1, 27})
    );

    CASE(
      N = randInt(MAX_N-50, MAX_N),
      pureRandom(N, {1, 4900}, {1, 4})
    );

    CASE(
      N = randInt(MAX_N-50, MAX_N),
      pureRandom(N, {1, 4000}, {1, 5}, {1, 1000})
    );
    
    // ---- case with long path ----
    CASE(
      N = randInt(MAX_N-50, MAX_N),
      initRandom(N, {1, N/20}, {1, 1000}, {1, 1000}),
      randomValidPath(N/20, pureRand2, 1000, {1, 1000})
    );

    CASE(
      N = randInt(MAX_N-50, MAX_N),
      initRandom(N, {1, N/10}, {1, 10000}, {1, 10000}),
      randomValidPath(N/10, positionRand, 1000, {1, 10000})
    );

    // ---- case with short path ----

    CASE(
      N = randInt(MAX_N-50, MAX_N),
      initRandom(N, {1, 100}, {1, MAX_W}, {100, 1000}),
      randomValidPath(100, pureRand1)
    );


    CASE(
      N = randInt(MAX_N-50, MAX_N),
      initRandom(N, {1, 250}, {1, MAX_W}),
      randomValidPath(250, positionRand)
    );

    // always the smallest modifier in binomial dist
    CASE(
      N = randInt(MAX_N-50, MAX_N),
      initRandom(N, {1, N/100}, {1, 100}, {1, 100}),
      multRandModifier = {0, 3, 10},
      randomValidPaths(5, N/100, pureRand1, 100)
    );

    // 2-4 types only, always valid no matter what
    CASE(
      N = MAX_N,
      initRandom(N, {1, 2}, {999, 1000})
    );

    CASE(
      N = MAX_N,
      initRandom(N, {1, 3}, {999, 1000})
    );

    CASE(
      N = MAX_N,
      initRandom(N, {1, 4}, {999, 1000})
    );

    // ---- multiple valid path ----
    CASE(
      N = randInt(MAX_N-50, MAX_N),
      initRandom(N, {1, N/100}, {1, 1000}, {1, 1000}),
      randomValidPaths(5, N/100, pureRand2)
    );

    CASE(
      N = randInt(MAX_N-50, MAX_N),
      initRandom(N, {1, 100}, {1, 1000}, {1, 1000}),
      randomValidPaths(3, 100, pureRand1)
    );
  }

  private:
  int randInt(pair<int, int> range) {
    return randInt(range.first, range.second);
  }

  int randInt(int l, int r) {
    return rnd.nextInt(l, r);
  }

  bool randChance(int chance) {
    return chance == 0 ? false : randInt(1, chance) == 1;
  }

  void randArray(vector<int> &A, pii range) {
    A.resize(N);
    generate(A.begin(), A.end(), [&]() { return randInt(range); });
  }

  void randArray(vector<int> &A, int lo, int hi) {
    A.resize(N);
    generate(A.begin(), A.end(), [&]() { return randInt(lo, hi); });
  }

  void randArray12(vector<int> &A, int chance1, int chance2) {
    A.resize(N);
    generate(A.begin(), A.end(), [&]() { return randInt(1, chance1 + chance2) <= chance1 ? 1 : 2; });
  }

  void initRandom(int sz, pii A_range=pii(1, -1), pii W_range=pii(1, MAX_W), pii V_range=pii(1, MAX_V)) {
    N = sz;
    if (A_range.second == -1) A_range.second = sz;
    randArray(A, A_range);
    randArray(W, W_range);
    randArray(V, V_range);
  }


  // somehow function returning function always segfault
  function<bool(int, int)> pureRand1 = [&](int idx, int M) { return true; };
  function<bool(int, int)> pureRand2 = [&](int idx, int M) { return rnd.nextInt(1, 2) == 1; };
  function<bool(int, int)> pureRand4 = [&](int idx, int M) { return rnd.nextInt(1, 4) == 1; };
  function<bool(int, int)> pureRand8 = [&](int idx, int M) { return rnd.nextInt(1, 8) == 1; };

  function<bool(int, int)> positionRand = [&](int idx, int M) { return randInt(0, (idx+1)/2) == 0; };

  // modifier to manupulate the multiplier randomization
  const vector<int> defMultRandModifier = {3, 2, 10};
  vector<int> multRandModifier;

  int multRand(long long lo, long long hi) {
    if (lo == hi) return lo;
    hi = min(hi, 
      !randChance(multRandModifier[0]) ? 100LL :
        !randChance(multRandModifier[1]) ? 1000LL : 
          !randChance(multRandModifier[2]) ? 10000LL : hi
      );

    int tries = (hi-lo) * 2;
    binomial_distribution<> roll(tries, 0.5);
    int res = roll(rng);
    res = abs((hi-lo) - res) + lo;
    // cout << lo << " " << hi << " -> " << abs((hi-lo) - res) + lo << "\n";
    assert(lo <= res && res <= hi);
    return res;
  }

  // tried to make a random valid path
  void randomValidPath(int M, function<bool(int, int)> randomizer, int max_W=MAX_W, pii V_range = pii(1, MAX_V)) {
    assert(N >= M);
    ordered_set select_poll;
    vector<int> path;

    for (int i = 0; i < N; i++) select_poll.insert(i);

    // find random distinct sequence containing index of A
    for (int i = 1; i <= M; i++) {
      int pos = randInt(0, select_poll.size()-1);
      int now = *(select_poll.find_by_order(pos));
      path.emplace_back(now);
      select_poll.erase(now);
      A[now] = i;
    }

    // compute initial sum and random V
    long long sisa_cost = 0;
    int last = path[0];
    for (int idx : path) {
      V[idx] = randInt(V_range);
      W[idx] = 1;
      sisa_cost += V[idx] + abs(last - idx);
      last = idx;
    }
   
    long long now_sum = 0;
    for (int i = M-1; i >= 0; i--) {
      int idx = path[i];

      now_sum += V[idx];
      sisa_cost -= V[idx];
      if (i != M-1) {
        sisa_cost -= abs(path[i] - path[i+1]);
        now_sum += abs(path[i] - path[i+1]);
      }

      // try to random the W[i]
      if (randomizer(i, M)) {
        long long mx_mult = (MAX_ANS - sisa_cost) / now_sum;
        mx_mult = min(max_W * 1LL, mx_mult);
        W[idx] = multRand(1, mx_mult);
        now_sum *= W[idx];
      }
      assert(now_sum <= MAX_ANS && now_sum > 0);
    } 
  }

  void randomValidPaths(int tries, int M, function<bool(int, int)> randomizer, int max_W=MAX_W, pii V_range = pii(1, MAX_V)) {
    while (tries--)
      randomValidPath(M, randomizer, max_W, V_range);
  }

  void decreaseOneWithBigW(int limit) {
    for (int i = 0; i < N; i++) {
      if (W[i] > limit) {
        long long diff = W[i] - limit;
        switch (rnd.nextInt(0, 2)) {
          case 1:
            V[i] = randInt(max(1LL, V[i] - diff*2), V[i]);
            break;
          case 2:
            V[i] = randInt(max(1LL, V[i] - diff*(diff-1)), V[i]);
            break;
        }
      }
    }
  }

  // generate pure random cases 
  void pureRandom(int sz, pii A_range=pii(1, -1), pii W_range=pii(1, MAX_W), pii V_range=pii(1, MAX_V)) {
    do {
      initRandom(sz, A_range, W_range, V_range);
    } while (solution::calculateSolution(N, A, W, V) > MAX_ANS);
  }

  // --- custom cases ---
  void MaxAnsW1Case() {
    N = MAX_N;
    A.resize(N);
    randArray(W, 1, 1);
    randArray(V, MAX_V, MAX_V);
    // generates A
    int l = 0, r = N-1;
    int p_A = 1;
    while (l <= r) {
      if (p_A & 1) A[l++] = p_A++;
      else A[r--] = p_A++;
    }
  }

  void MaxAnsW2Case() {
    N = 58;
    A.resize(N);
    W.resize(N);
    V.resize(N);
    long long ans_left = 1e18;
    for (int i = 0; i < N; i++) {
      A[i] = i + 1;
      W[i] = 2;
      V[i] = 1;
      ans_left -= (1LL << i) * 2;
    }
    // 1 came from V[0] only, not from moving
    ans_left++;

    for (int i = N-1; i >= 0; i--) {
      if (ans_left >= (1LL << i)) {
        V[i] += ans_left / (1LL << i);
        ans_left %= (1LL << i);
      }
    }
  }
};

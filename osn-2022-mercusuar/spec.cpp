#include <bits/extc++.h>
#include <bits/stdc++.h>

#include <tcframe/spec.hpp>

#include "solutions.h"

using namespace std;
using namespace tcframe;
using namespace __gnu_pbds;

template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const double MAX_TIME_ANTI_ARRAY = 300;

const int MAXN = 1e5;
const int MAXA = 1e9;

const int MAXNN = 8;
const int MAXN5 = 30;
const int MAXN4 = 80;
const int MAXN3 = 300;
const int MAXN2 = 1500;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N;
  vector<int> A;

  long long ans;

  void InputFormat() {
    LINE(N);
    LINE(A % SIZE(N));
  }

  void OutputFormat() { LINE(ans); }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(512);
  }

  void Constraints() {
    CONS(2 <= N && N <= MAXN);
    CONS(N == int(A.size()));
    CONS(eachElementBetween(A, 1, MAXA));
  }

  void Subtask1() {
    Points(0);
    CONS(N == 12);
    CONS(A == vector<int>({9, 10, 4, 3, 5, 7, 5, 2, 7, 20, 2, 3}));
  }

  void Subtask2() {
    Points(0);
    CONS(N <= MAXNN);
  }

  void Subtask3() {
    Points(0);
    CONS(eachElementBetween(A, 1, 2));
  }

  void Subtask4() {
    Points(0);
    CONS(is_sorted(begin(A), end(A)));
  }

  void Subtask5() {
    Points(0);
    CONS(N <= MAXN5);
  }

  void Subtask6() {
    Points(0);
    CONS(N <= MAXN4);
  }

  void Subtask7() {
    Points(0);
    CONS(N <= MAXN3);
    CONS(isBitonic(A));
  }

  void Subtask8() {
    Points(0);
    CONS(N <= MAXN3);
  }

  void Subtask9() {
    Points(0);
    CONS(N <= MAXN2);
  }

  void Subtask10() { Points(0); }

 private:
  template <typename T>
  bool eachElementBetween(const vector<T>& A, const T& minA, const T& maxA) {
    for (const T& a : A) {
      if (!(minA <= a && a <= maxA)) {
        return false;
      }
    }
    return true;
  }

  template <typename T>
  bool isBitonic(const vector<T>& A) {
    int k = 1;
    while (k < int(A.size()) && A[k - 1] >= A[k]) {
      k += 1;
    }
    return is_sorted(begin(A) + k, end(A));
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({2, 5, 6, 8, 9, 10});
    Input({
        "6",
        "2 1 1 3 2 2",
    });
    Output({
        "1",
    });
  }

  void SampleTestCase2() {
    Subtasks({2, 5, 6, 8, 9, 10});
    Input({
        "4",
        "3 1 2 1",
    });
    Output({
        "3",
    });
  }

  void SampleTestCase3() {
    Subtasks({2, 5, 6, 8, 9, 10});
    Input({
        "8",
        "17 10 13 11 11 8 14 14",
    });
    Output({
        "11",
    });
  }

  void BeforeTestCase() {
    N = ans = 0;
    A.clear();
  }

  void TestGroup1() {
    // Open test case
    // 12
    // 9 10 4 3 5 7 5 2 7 20 2 3
    Subtasks({1, 5, 6, 8, 9, 10});
    CASE(N = 12; A = vector<int>({9, 10, 4, 3, 5, 7, 5, 2, 7, 20, 2, 3}));
  }

  void TestGroup2() {
    // N <= 8
    // A[i] <= 2
    // Sorted
    Subtasks({2, 3, 4, 5, 6, 7, 8, 9, 10});
    CASE(N = 2; A = {1, 1});
    CASE(N = 2; A = {1, 2});
    CASE(N = 2; A = {2, 2});
    CASE(N = 3; A = {1, 1, 2});
    CASE(N = 5; A = {1, 1, 1, 1, 2});
    CASE(N = 8; A = {1, 1, 1, 1, 1, 1, 1, 2});
    CASE(N = 8; A = {1, 1, 1, 1, 1, 1, 2, 2});
    CASE(N = 8; A = {1, 1, 2, 2, 2, 2, 2, 2});
    CASE(N = 8; A = {1, 2, 2, 2, 2, 2, 2, 2});
  }

  void TestGroup3() {
    // N <= 8
    // A[i] <= 2
    // Bitonic
    Subtasks({2, 3, 5, 6, 7, 8, 9, 10});
    CASE(N = 2; A = {2, 1});
    CASE(N = 3; A = {2, 1, 2});
    CASE(N = 3; A = {2, 1, 1});
    CASE(N = 5; A = {2, 2, 1, 2, 2});
    CASE(N = 8; A = {2, 2, 1, 1, 1, 2, 2, 2});
    CASE(N = 8; A = {2, 1, 1, 1, 1, 1, 1, 1});
    CASE(N = 8; A = {2, 1, 1, 1, 1, 1, 1, 2});
    CASE(N = 8; A = {2, 2, 2, 2, 2, 1, 2, 2});
  }

  void TestGroup4() {
    // N <= 8
    // A[i] <= 2
    Subtasks({2, 3, 5, 6, 8, 9, 10});
    CASE(N = 3; A = {1, 2, 1});
    CASE(N = 4; A = {1, 2, 1, 1});
    CASE(N = 4; A = {1, 2, 2, 1});
    CASE(N = 5; A = {1, 1, 2, 1, 1});
    CASE(N = 5; A = {1, 2, 1, 1, 1});
    CASE(N = 5; A = {1, 2, 1, 2, 1});
    CASE(N = 5; A = {2, 1, 1, 2, 1});
    CASE(N = 6; A = {1, 1, 2, 1, 1, 1});
    CASE(N = 6; A = {2, 1, 2, 1, 1, 1});
    CASE(N = 8; A = {1, 2, 1, 2, 1, 2, 1, 2});
    CASE(N = 8; A = {2, 1, 1, 2, 1, 2, 1, 1});
    CASE(N = 8; A = {2, 1, 1, 1, 2, 2, 1, 2});
    CASE(N = 8; A = {1, 2, 1, 2, 1, 1, 2, 1});
  }

  void TestGroup5() {
    // N <= 8
    // Sorted
    Subtasks({2, 4, 5, 6, 7, 8, 9, 10});

    CASE(N = 8; A = makeStrong(
                    [&]() { return sortedArray(N, floor(sqrt(N)), 1, MAXA); },
                    &solution_wa_sorted::Solve, &solution::Solve));
    CASE(N = 8; A = makeStrong([&]() { return sortedArray(N, N / 2, 1, MAXA); },
                               &solution_wa_sorted::Solve, &solution::Solve));
    CASE(N = 8; A = makeStrong([&]() { return sortedArray(N, N, 1, MAXA); },
                               &solution_wa_sorted::Solve, &solution::Solve));
    CASE(N = 8; A = makeStrong([&]() { return sortedArray(N, 1, MAXA); },
                               &solution_wa_sorted::Solve, &solution::Solve));

    CASE(N = 8; A = makeStrong(
                    [&]() { return sortedArray(N, floor(sqrt(N)), 1, MAXA); },
                    [](vector<int> A) { return -1; }, &solution::Solve));
    CASE(N = 8;
         A = makeStrong([&]() { return sortedArray(N, N / 2, 1, MAXA); },
                        [](vector<int> A) { return -1; }, &solution::Solve));
    CASE(N = 8;
         A = makeStrong([&]() { return sortedArray(N, N, 1, MAXA); },
                        [](vector<int> A) { return -1; }, &solution::Solve));
    CASE(N = 8;
         A = makeStrong([&]() { return sortedArray(N, 1, MAXA); },
                        [](vector<int> A) { return -1; }, &solution::Solve));
  }

  void TestGroup6() {
    // N <= 8
    // Bitonic
    Subtasks({2, 5, 6, 7, 8, 9, 10});

    CASE(N = 8; A = randomBitonicArray(N, 1, MAXA));
    CASE(N = 8; A = randomBitonicArray(N, N, 1, MAXA));
    CASE(N = 8; A = randomBitonicArray(N, N / 2, 1, MAXA));
    CASE(N = 8; A = randomBitonicArray(N, floor(sqrt(N)), 1, MAXA));

    CASE(N = 8; A = groupedBitonicArray(N, 6, 1, MAXA));
    CASE(N = 8; A = groupedBitonicArray(N, 6, N, 1, MAXA));

    CASE(N = 8; A = groupedBitonicArray(N, 4, 1, MAXA));
    CASE(N = 8; A = groupedBitonicArray(N, 4, N, 1, MAXA));

    CASE(N = 8; A = groupedBitonicArray(N, 2, 1, MAXA));
    CASE(N = 8; A = groupedBitonicArray(N, 2, N, 1, MAXA));
  }

  void TestGroup7() {
    // N <= 8
    Subtasks({2, 5, 6, 8, 9, 10});
    for (int t = 0; t < 5; t++) {
      for (int t2 = 0; t2 < 4; t2++) {
        CASE(N = 8; A = makeStrong([&]() { return randomArray(N, 1, MAXA); },
                                   [&](auto x) {
                                     int bad1 = solution_wa_n2::Solve(x) !=
                                                solution::Solve(x);
                                     int bad2 = solution_wa_n5::Solve(x) !=
                                                solution::Solve(x);
                                     return !isBitonic(x) &&
                                            (bad1 << 1) + bad2 == t2;
                                   }));
      }
    }
  }

  void TestGroup8() {
    // A[i] <= 2
    // Sorted
    Subtasks({3, 4, 10});
    CASE(N = rnd.nextInt(MAXN - 20, MAXN); A = vector<int>(N, 1));
    CASE(N = rnd.nextInt(MAXN - 20, MAXN); A = vector<int>(N, 2));
    CASE(N = rnd.nextInt(MAXN - 20, MAXN); A = vector<int>(N, 1);
         fill(begin(A) + rnd.nextInt(0, N), end(A), 2));
    CASE(N = rnd.nextInt(MAXN - 20, MAXN); A = vector<int>(N, 1);
         fill(begin(A) + rnd.nextInt(0, N), end(A), 2));
    CASE(N = rnd.nextInt(MAXN - 20, MAXN); A = vector<int>(N, 1);
         fill(begin(A) + rnd.nextInt(0, N), end(A), 2));
  }

  void TestGroup9() {
    // A[i] <= 2
    Subtasks({3, 10});

    CASE(N = rnd.nextInt(MAXN - 20, MAXN); A = vector<int>(N, 1); A[0] = 2);
    CASE(N = rnd.nextInt(MAXN - 20, MAXN); A = vector<int>(N, 1); A[1] = 2);
    CASE(N = rnd.nextInt(MAXN - 20, MAXN); A = vector<int>(N, 1); A[2] = 2);
    CASE(N = rnd.nextInt(MAXN - 20, MAXN); A = vector<int>(N, 1);
         A[rnd.nextInt(0, N - 1)] = 2);

    CASE(N = rnd.nextInt(MAXN - 20, MAXN); A = randomArray(N, N, 1, 2));
    CASE(N = rnd.nextInt(MAXN - 20, MAXN); A = randomArray(N, N, 1, 2);
         A[0] = 1; A[1] = 2);
    CASE(N = rnd.nextInt(MAXN - 20, MAXN); A = randomArray(N, N, 1, 2);
         A[N - 1] = 1; A[N - 2] = 2);
    CASE(N = rnd.nextInt(MAXN - 20, MAXN); A = randomArray(N, N, 1, 2);
         A[0] = A[N - 1] = 1; A[1] = A[N - 2] = 2);
  }

  void TestGroup10() {
    // Sorted
    Subtasks({4, 10});

    CASE(N = rnd.nextInt(MAXN - 50, MAXN);
         A = makeStrong([&]() { return sortedArray(N, 50, 1, MAXA); },
                        &solution_wa_sorted::Solve, &solution::Solve));
    CASE(N = rnd.nextInt(MAXN - 50, MAXN);
         A = makeStrong(
             [&]() { return sortedArray(N, floor(sqrt(N)), 1, MAXA); },
             &solution_wa_sorted::Solve, &solution::Solve));
    CASE(N = rnd.nextInt(MAXN - 50, MAXN);
         A = makeStrong([&]() { return sortedArray(N, N / 2, 1, MAXA); },
                        &solution_wa_sorted::Solve, &solution::Solve));
    CASE(N = rnd.nextInt(MAXN - 50, MAXN);
         A = makeStrong([&]() { return sortedArray(N, N, 1, MAXA); },
                        &solution_wa_sorted::Solve, &solution::Solve));
    CASE(N = rnd.nextInt(MAXN - 50, MAXN);
         A = makeStrong([&]() { return sortedArray(N, 1, MAXA); },
                        &solution_wa_sorted::Solve, &solution::Solve));

    CASE(N = rnd.nextInt(MAXN - 50, MAXN);
         A = makeStrong([&]() { return sortedArray(N, 50, 1, MAXA); },
                        [](vector<int> A) { return -1; }, &solution::Solve));
    CASE(N = rnd.nextInt(MAXN - 50, MAXN);
         A = makeStrong(
             [&]() { return sortedArray(N, floor(sqrt(N)), 1, MAXA); },
             [](vector<int> A) { return -1; }, &solution::Solve));
    CASE(N = rnd.nextInt(MAXN - 50, MAXN);
         A = makeStrong([&]() { return sortedArray(N, N / 2, 1, MAXA); },
                        [](vector<int> A) { return -1; }, &solution::Solve));
    CASE(N = rnd.nextInt(MAXN - 50, MAXN);
         A = makeStrong([&]() { return sortedArray(N, N, 1, MAXA); },
                        [](vector<int> A) { return -1; }, &solution::Solve));
    CASE(N = rnd.nextInt(MAXN - 50, MAXN);
         A = makeStrong([&]() { return sortedArray(N, 1, MAXA); },
                        [](vector<int> A) { return -1; }, &solution::Solve));
  }

  void TestGroup11() {
    // N <= 30
    // Sorted
    Subtasks({4, 5, 6, 7, 8, 9, 10});

    CASE(N = MAXN5;
         A = makeStrong(
             [&]() { return sortedArray(N, floor(sqrt(N)), 1, MAXA); },
             &solution_wa_sorted::Solve, &solution::Solve));
    CASE(N = MAXN5;
         A = makeStrong([&]() { return sortedArray(N, N / 2, 1, MAXA); },
                        &solution_wa_sorted::Solve, &solution::Solve));
    CASE(N = MAXN5;
         A = makeStrong([&]() { return sortedArray(N, N, 1, MAXA); },
                        &solution_wa_sorted::Solve, &solution::Solve));
    CASE(N = MAXN5;
         A = makeStrong([&]() { return sortedArray(N, 1, MAXA); },
                        &solution_wa_sorted::Solve, &solution::Solve));

    CASE(N = MAXN5;
         A = makeStrong(
             [&]() { return sortedArray(N, floor(sqrt(N)), 1, MAXA); },
             [](vector<int> A) { return -1; }, &solution::Solve));
    CASE(N = MAXN5;
         A = makeStrong([&]() { return sortedArray(N, N / 2, 1, MAXA); },
                        [](vector<int> A) { return -1; }, &solution::Solve));
    CASE(N = MAXN5;
         A = makeStrong([&]() { return sortedArray(N, N, 1, MAXA); },
                        [](vector<int> A) { return -1; }, &solution::Solve));
    CASE(N = MAXN5;
         A = makeStrong([&]() { return sortedArray(N, 1, MAXA); },
                        [](vector<int> A) { return -1; }, &solution::Solve));
  }

  void TestGroup12() {
    // N <= 30
    // Bitonic
    Subtasks({5, 6, 7, 8, 9, 10});

    CASE(N = MAXN5; A = randomBitonicArray(N, 1, MAXA));
    CASE(N = MAXN5; A = randomBitonicArray(N, N, 1, MAXA));
    CASE(N = MAXN5; A = randomBitonicArray(N, N / 2, 1, MAXA));
    CASE(N = MAXN5; A = randomBitonicArray(N, floor(sqrt(N)), 1, MAXA));

    CASE(N = MAXN5; A = groupedBitonicArray(N, floor(sqrt(N)), 1, MAXA));
    CASE(N = MAXN5; A = groupedBitonicArray(N, floor(sqrt(N)), N, 1, MAXA));
    CASE(N = MAXN5;
         A = groupedBitonicArray(N, floor(sqrt(N)), floor(sqrt(N)), 1, MAXA));

    CASE(N = MAXN5; A = groupedBitonicArray(N, 10, 1, MAXA));
    CASE(N = MAXN5; A = groupedBitonicArray(N, 10, N, 1, MAXA));
    CASE(N = MAXN5; A = groupedBitonicArray(N, 10, floor(sqrt(N)), 1, MAXA));

    CASE(N = MAXN5; A = groupedBitonicArray(N, N / 10, 1, MAXA));
    CASE(N = MAXN5; A = groupedBitonicArray(N, N / 10, N, 1, MAXA));
    CASE(N = MAXN5;
         A = groupedBitonicArray(N, N / 10, floor(sqrt(N)), 1, MAXA));
  }

  void TestGroup13() {
    // N <= 30
    Subtasks({5, 6, 8, 9, 10});

    // Break `solution_wa_magic.cpp`
    for (int t = 0; t < 3; t++) {
      CASE(N = MAXN5;
           A = makeStrong([&]() { return antiMagicArray(N, 1, MAXA); },
                          &solution_wa_magic::Solve, &solution::Solve,
                          MAX_TIME_ANTI_ARRAY));
    }

    for (int t = 0; t < 2; t++) {
      for (int t2 = 0; t2 < 4; t2++) {
        CASE(N = MAXN5;
             A = makeStrong(
                 [&]() { return randomArray(N, 1, MAXA); },
                 [&](auto x) {
                   int bad1 = solution_wa_n2::Solve(x) != solution::Solve(x);
                   int bad2 = solution_wa_n5::Solve(x) != solution::Solve(x);
                   return (bad1 << 1) + bad2 == t2;
                 }));
      }
    }

    CASE(N = MAXN5; A = randomArray(N, 1, MAXA));
    CASE(N = MAXN5; A = randomArray(N, floor(sqrt(N)), 1, MAXA));
    CASE(N = MAXN5; A = randomArray(N, N / 2, 1, MAXA));
    CASE(N = MAXN5; A = randomArray(N, N, 1, MAXA));

    CASE(N = MAXN5; A = swapArray(sortedArray(N, 1, MAXA), N / 10));
    CASE(N = MAXN5; A = swapArray(sortedArray(N, N, 1, MAXA), N / 10));
    CASE(N = MAXN5; A = swapArray(groupedBitonicArray(N, 10, 1, MAXA), N / 10));
    CASE(N = MAXN5;
         A = swapArray(groupedBitonicArray(N, 10, N, 1, MAXA), N / 10));

    CASE(N = MAXN5; A = customCartesianTree(N, -1, 0, 1, 0, 0, 1, MAXA,
                                            N - N / 3, 4, 1e-1));
    CASE(N = MAXN5; A = customCartesianTree(N, N, 0, 1, 0, 0, 1, MAXA,
                                            N - N / 3, 4, 1e-1));
    CASE(N = MAXN5; A = customCartesianTree(N, -1, 0, 1, 0, 0, 1, MAXA,
                                            N - N / 3, 4, 1e-1));
    CASE(N = MAXN5; A = customCartesianTree(N, N, 0, 1, 0, 0, 1, MAXA,
                                            N - N / 3, 4, 1e-1));
  }

  void TestGroup14() {
    // N <= 80
    // Sorted
    Subtasks({4, 6, 7, 8, 9, 10});

    CASE(N = rnd.nextInt(MAXN4 - 2, MAXN4);
         A = makeStrong(
             [&]() { return sortedArray(N, floor(sqrt(N)), 1, MAXA); },
             &solution_wa_sorted::Solve, &solution::Solve));
    CASE(N = rnd.nextInt(MAXN4 - 2, MAXN4);
         A = makeStrong([&]() { return sortedArray(N, N / 2, 1, MAXA); },
                        &solution_wa_sorted::Solve, &solution::Solve));
    CASE(N = rnd.nextInt(MAXN4 - 2, MAXN4);
         A = makeStrong([&]() { return sortedArray(N, N, 1, MAXA); },
                        &solution_wa_sorted::Solve, &solution::Solve));
    CASE(N = rnd.nextInt(MAXN4 - 2, MAXN4);
         A = makeStrong([&]() { return sortedArray(N, 1, MAXA); },
                        &solution_wa_sorted::Solve, &solution::Solve));

    CASE(N = rnd.nextInt(MAXN4 - 2, MAXN4);
         A = makeStrong(
             [&]() { return sortedArray(N, floor(sqrt(N)), 1, MAXA); },
             [](vector<int> A) { return -1; }, &solution::Solve));
    CASE(N = rnd.nextInt(MAXN4 - 2, MAXN4);
         A = makeStrong([&]() { return sortedArray(N, N / 2, 1, MAXA); },
                        [](vector<int> A) { return -1; }, &solution::Solve));
    CASE(N = rnd.nextInt(MAXN4 - 2, MAXN4);
         A = makeStrong([&]() { return sortedArray(N, N, 1, MAXA); },
                        [](vector<int> A) { return -1; }, &solution::Solve));
    CASE(N = rnd.nextInt(MAXN4 - 2, MAXN4);
         A = makeStrong([&]() { return sortedArray(N, 1, MAXA); },
                        [](vector<int> A) { return -1; }, &solution::Solve));
  }

  void TestGroup15() {
    // N <= 80
    // Bitonic
    Subtasks({6, 7, 8, 9, 10});

    CASE(N = rnd.nextInt(MAXN4 - 2, MAXN4); A = randomBitonicArray(N, 1, MAXA));
    CASE(N = rnd.nextInt(MAXN4 - 2, MAXN4);
         A = randomBitonicArray(N, N, 1, MAXA));
    CASE(N = rnd.nextInt(MAXN4 - 2, MAXN4);
         A = randomBitonicArray(N, N / 2, 1, MAXA));
    CASE(N = rnd.nextInt(MAXN4 - 2, MAXN4);
         A = randomBitonicArray(N, floor(sqrt(N)), 1, MAXA));

    CASE(N = rnd.nextInt(MAXN4 - 2, MAXN4);
         A = groupedBitonicArray(N, floor(sqrt(N)), 1, MAXA));
    CASE(N = rnd.nextInt(MAXN4 - 2, MAXN4);
         A = groupedBitonicArray(N, floor(sqrt(N)), N, 1, MAXA));
    CASE(N = rnd.nextInt(MAXN4 - 2, MAXN4);
         A = groupedBitonicArray(N, floor(sqrt(N)), floor(sqrt(N)), 1, MAXA));

    CASE(N = rnd.nextInt(MAXN4 - 2, MAXN4);
         A = groupedBitonicArray(N, 10, 1, MAXA));
    CASE(N = rnd.nextInt(MAXN4 - 2, MAXN4);
         A = groupedBitonicArray(N, 10, N, 1, MAXA));
    CASE(N = rnd.nextInt(MAXN4 - 2, MAXN4);
         A = groupedBitonicArray(N, 10, floor(sqrt(N)), 1, MAXA));

    CASE(N = rnd.nextInt(MAXN4 - 2, MAXN4);
         A = groupedBitonicArray(N, N / 10, 1, MAXA));
    CASE(N = rnd.nextInt(MAXN4 - 2, MAXN4);
         A = groupedBitonicArray(N, N / 10, N, 1, MAXA));
    CASE(N = rnd.nextInt(MAXN4 - 2, MAXN4);
         A = groupedBitonicArray(N, N / 10, floor(sqrt(N)), 1, MAXA));
  }

  void TestGroup16() {
    // N <= 80
    Subtasks({6, 8, 9, 10});

    // Break `solution_wa_magic.cpp`

    // N, K, antiNum, antiC, antiSizeL, antiSizeR, loC, hiC, longChain,
    // numLongChain, double probChangeDir) {
    CASE(N = MAXN4; A = customCartesianTree(N, -1, 1, 1000, 14, 20, 5,
                                            MAXA / 1000, N - N / 5, 6, 1e-1));
    CASE(N = MAXN4; A = customCartesianTree(N, N, 1, 1000, 14, 20, 5,
                                            MAXA / 1000, N - N / 5, 6, 1e-1));
    CASE(N = MAXN4; A = customCartesianTree(N, -1, 1, 1000, 14, 20, 5,
                                            MAXA / 1000, N - N / 5, 6, 1e-1));
    CASE(N = MAXN4; A = customCartesianTree(N, N, 1, 1000, 14, 20, 5,
                                            MAXA / 1000, N - N / 5, 6, 1e-1));

    for (int t = 0; t < 3; t++) {
      CASE(N = MAXN4;
           A = makeStrong([&]() { return antiMagicArray(N, 1, MAXA); },
                          &solution_wa_magic_weaker::Solve, &solution::Solve,
                          MAX_TIME_ANTI_ARRAY));
    }

    CASE(N = MAXN4; A = randomArray(N, 1, MAXA));
    CASE(N = MAXN4; A = randomArray(N, floor(sqrt(N)), 1, MAXA));
    CASE(N = MAXN4; A = randomArray(N, N / 2, 1, MAXA));
    CASE(N = MAXN4; A = randomArray(N, N, 1, MAXA));

    CASE(N = MAXN4; A = swapArray(sortedArray(N, 1, MAXA), N / 10));
    CASE(N = MAXN4; A = swapArray(sortedArray(N, N, 1, MAXA), N / 10));
    CASE(N = MAXN4; A = swapArray(groupedBitonicArray(N, 10, 1, MAXA), N / 10));
    CASE(N = MAXN4;
         A = swapArray(groupedBitonicArray(N, 10, N, 1, MAXA), N / 10));

    CASE(N = MAXN4; A = customCartesianTree(N, -1, 0, 1, 0, 0, 1, MAXA,
                                            N - N / 5, 6, 1e-1));
    CASE(N = MAXN4; A = customCartesianTree(N, N, 0, 1, 0, 0, 1, MAXA,
                                            N - N / 5, 6, 1e-1));
    CASE(N = MAXN4; A = customCartesianTree(N, -1, 0, 1, 0, 0, 1, MAXA,
                                            N - N / 5, 6, 1e-1));
    CASE(N = MAXN4; A = customCartesianTree(N, N, 0, 1, 0, 0, 1, MAXA,
                                            N - N / 5, 6, 1e-1));
  }

  void TestGroup17() {
    // N <= 300
    // Sorted
    Subtasks({4, 7, 8, 9, 10});

    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = makeStrong(
             [&]() { return sortedArray(N, floor(sqrt(N)), 1, MAXA); },
             &solution_wa_sorted::Solve, &solution::Solve));
    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = makeStrong([&]() { return sortedArray(N, N / 2, 1, MAXA); },
                        &solution_wa_sorted::Solve, &solution::Solve));
    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = makeStrong([&]() { return sortedArray(N, N, 1, MAXA); },
                        &solution_wa_sorted::Solve, &solution::Solve));
    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = makeStrong([&]() { return sortedArray(N, 1, MAXA); },
                        &solution_wa_sorted::Solve, &solution::Solve));

    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = makeStrong(
             [&]() { return sortedArray(N, floor(sqrt(N)), 1, MAXA); },
             [](vector<int> A) { return -1; }, &solution::Solve));
    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = makeStrong([&]() { return sortedArray(N, N / 2, 1, MAXA); },
                        [](vector<int> A) { return -1; }, &solution::Solve));
    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = makeStrong([&]() { return sortedArray(N, N, 1, MAXA); },
                        [](vector<int> A) { return -1; }, &solution::Solve));
    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = makeStrong([&]() { return sortedArray(N, 1, MAXA); },
                        [](vector<int> A) { return -1; }, &solution::Solve));
  }

  void TestGroup18() {
    // N <= 300
    // Bitonic
    Subtasks({7, 8, 9, 10});

    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = randomBitonicArray(N, 1, MAXA));
    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = randomBitonicArray(N, N, 1, MAXA));
    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = randomBitonicArray(N, N / 2, 1, MAXA));
    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = randomBitonicArray(N, floor(sqrt(N)), 1, MAXA));

    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = groupedBitonicArray(N, floor(sqrt(N)), 1, MAXA));
    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = groupedBitonicArray(N, floor(sqrt(N)), N, 1, MAXA));
    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = groupedBitonicArray(N, floor(sqrt(N)), floor(sqrt(N)), 1, MAXA));

    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = groupedBitonicArray(N, 10, 1, MAXA));
    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = groupedBitonicArray(N, 10, N, 1, MAXA));
    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = groupedBitonicArray(N, 10, floor(sqrt(N)), 1, MAXA));

    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = groupedBitonicArray(N, N / 10, 1, MAXA));
    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = groupedBitonicArray(N, N / 10, N, 1, MAXA));
    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = groupedBitonicArray(N, N / 10, floor(sqrt(N)), 1, MAXA));
  }

  void TestGroup19() {
    // N <= 300
    Subtasks({8, 9, 10});

    // Break `solution_wa_magic.cpp`

    // N, K, antiNum, antiC, antiSizeL, antiSizeR, loC, hiC, longChain,
    // numLongChain, double probChangeDir) {
    CASE(N = MAXN3; A = customCartesianTree(N, -1, 3, 1000, 14, 30, 5,
                                            MAXA / 1000, N - N / 5, 10, 3e-2));
    CASE(N = MAXN3; A = customCartesianTree(N, N, 3, 1000, 14, 30, 5,
                                            MAXA / 1000, N - N / 5, 10, 3e-2));
    CASE(N = MAXN3; A = customCartesianTree(N, -1, 3, 1000, 14, 30, 5,
                                            MAXA / 1000, N - N / 5, 10, 3e-2));
    CASE(N = MAXN3; A = customCartesianTree(N, N, 3, 1000, 14, 30, 5,
                                            MAXA / 1000, N - N / 5, 10, 3e-2));

    for (int t = 0; t < 3; t++) {
      CASE(N = MAXN3;
           A = makeStrong([&]() { return antiMagicArray(N, 1, MAXA); },
                          &solution_wa_magic_weaker::Solve, &solution::Solve,
                          MAX_TIME_ANTI_ARRAY));
    }

    // Random
    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3); A = randomArray(N, 1, MAXA));
    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = randomArray(N, floor(sqrt(N)), 1, MAXA));
    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = randomArray(N, N / 2, 1, MAXA));
    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3); A = randomArray(N, N, 1, MAXA));

    // Almost Bitonic
    CASE(N = MAXN3; A = swapArray(sortedArray(N, 1, MAXA), 5));
    CASE(N = MAXN3; A = swapArray(sortedArray(N, N, 1, MAXA), 5));
    CASE(N = MAXN3; A = swapArray(groupedBitonicArray(N, 10, 1, MAXA), 5));
    CASE(N = MAXN3; A = swapArray(groupedBitonicArray(N, 10, N, 1, MAXA), 5));

    // Cartesian
    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = customCartesianTree(N, -1, 0, 1, 0, 0, 1, MAXA, N - N / 5, 10,
                                 3e-2));
    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = customCartesianTree(N, N, 0, 1, 0, 0, 1, MAXA, N - N / 5, 10,
                                 3e-2));
    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = customCartesianTree(N, -1, 0, 1, 0, 0, 1, MAXA, N - N / 5, 10,
                                 3e-2));
    CASE(N = rnd.nextInt(MAXN3 - 10, MAXN3);
         A = customCartesianTree(N, N, 0, 1, 0, 0, 1, MAXA, N - N / 5, 10,
                                 3e-2));
  }

  void TestGroup20() {
    // N <= 1500
    // Sorted
    Subtasks({4, 9, 10});

    CASE(N = rnd.nextInt(MAXN2 - 20, MAXN2);
         A = makeStrong([&]() { return sortedArray(N, N, 1, MAXA); },
                        &solution_wa_sorted::Solve, &solution::Solve));
    CASE(N = rnd.nextInt(MAXN2 - 20, MAXN2);
         A = makeStrong([&]() { return sortedArray(N, 1, MAXA); },
                        &solution_wa_sorted::Solve, &solution::Solve));
    CASE(N = rnd.nextInt(MAXN2 - 20, MAXN2);
         A = makeStrong([&]() { return sortedArray(N, N, 1, MAXA); },
                        [](vector<int> A) { return -1; }, &solution::Solve));
    CASE(N = rnd.nextInt(MAXN2 - 20, MAXN2);
         A = makeStrong([&]() { return sortedArray(N, 1, MAXA); },
                        [](vector<int> A) { return -1; }, &solution::Solve));
  }

  void TestGroup21() {
    // N <= 1500
    Subtasks({9, 10});

    // Break `solution_wa_magic.cpp`

    // N, K, antiNum, antiC, antiSizeL, antiSizeR, loC, hiC, longChain,
    // numLongChain, double probChangeDir) {
    CASE(N = MAXN2; A = customCartesianTree(N, -1, 3, 1000, 14, 30, 5,
                                            MAXA / 1000, N - N / 5, 15, 1e-2));
    CASE(N = MAXN2; A = customCartesianTree(N, N, 3, 1000, 14, 30, 5,
                                            MAXA / 1000, N - N / 5, 15, 1e-2));
    CASE(N = MAXN2; A = customCartesianTree(N, -1, 3, 1000, 14, 30, 5,
                                            MAXA / 1000, N - N / 5, 15, 1e-2));
    CASE(N = MAXN2; A = customCartesianTree(N, N, 3, 1000, 14, 30, 5,
                                            MAXA / 1000, N - N / 5, 15, 1e-2));

    for (int t = 0; t < 3; t++) {
      CASE(N = MAXN2;
           A = makeStrong([&]() { return antiMagicArray(N, 1, MAXA); },
                          &solution_wa_magic_weaker::Solve, &solution::Solve,
                          MAX_TIME_ANTI_ARRAY));
    }

    // Bitonic
    CASE(N = MAXN2; A = groupedBitonicArray(N, floor(sqrt(N)), 1, MAXA));
    CASE(N = MAXN2; A = groupedBitonicArray(N, 10, 1, MAXA));
    CASE(N = MAXN2; A = groupedBitonicArray(N, N / 10, 1, MAXA));

    // Random
    CASE(N = rnd.nextInt(MAXN2 - 50, MAXN2); A = randomArray(N, 1, MAXA));
    CASE(N = rnd.nextInt(MAXN2 - 50, MAXN2);
         A = randomArray(N, floor(sqrt(N)), 1, MAXA));
    CASE(N = rnd.nextInt(MAXN2 - 50, MAXN2);
         A = randomArray(N, N / 2, 1, MAXA));
    CASE(N = rnd.nextInt(MAXN2 - 50, MAXN2); A = randomArray(N, N, 1, MAXA));

    // Almost Bitonic
    CASE(N = MAXN2; A = swapArray(sortedArray(N, 1, MAXA), 5));
    CASE(N = MAXN2; A = swapArray(sortedArray(N, N, 1, MAXA), 5));
    CASE(N = MAXN2; A = swapArray(groupedBitonicArray(N, 10, 1, MAXA), 5));
    CASE(N = MAXN2; A = swapArray(groupedBitonicArray(N, 10, N, 1, MAXA), 5));

    // Cartesian
    CASE(N = rnd.nextInt(MAXN2 - 50, MAXN2);
         A = customCartesianTree(N, -1, 0, 1, 0, 0, 1, MAXA, N - N / 5, 15,
                                 1e-2));
    CASE(N = rnd.nextInt(MAXN2 - 50, MAXN2);
         A = customCartesianTree(N, N, 0, 1, 0, 0, 1, MAXA, N - N / 5, 15,
                                 1e-2));
    CASE(N = rnd.nextInt(MAXN2 - 50, MAXN2);
         A = customCartesianTree(N, -1, 0, 1, 0, 0, 1, MAXA, N - N / 5, 15,
                                 1e-2));
    CASE(N = rnd.nextInt(MAXN2 - 50, MAXN2);
         A = customCartesianTree(N, N, 0, 1, 0, 0, 1, MAXA, N - N / 5, 15,
                                 1e-2));
  }

  void TestGroup22() {
    Subtasks({10});

    // Break `solution_wa_magic.cpp`

    // N, K, antiNum, antiC, antiSizeL, antiSizeR, loC, hiC, longChain,
    // numLongChain, double probChangeDir) {
    CASE(N = MAXN; A = customCartesianTree(N, -1, 3, 1000, 14, 30, 5,
                                           MAXA / 1000, N - N / 5, 100, 1e-3));
    CASE(N = MAXN; A = customCartesianTree(N, N, 3, 1000, 14, 30, 5,
                                           MAXA / 1000, N - N / 5, 100, 1e-3));
    CASE(N = MAXN; A = customCartesianTree(N, -1, 3, 1000, 14, 30, 5,
                                           MAXA / 1000, N - N / 5, 100, 1e-3));
    CASE(N = MAXN; A = customCartesianTree(N, N, 3, 1000, 14, 30, 5,
                                           MAXA / 1000, N - N / 5, 100, 1e-3));

    for (int t = 0; t < 3; t++) {
      CASE(N = MAXN;
           A = makeStrong([&]() { return antiMagicArray(N, 1, MAXA); },
                          &solution_wa_magic_weaker::Solve, &solution::Solve,
                          MAX_TIME_ANTI_ARRAY));
    }

    // Bitonic
    CASE(N = MAXN; A = groupedBitonicArray(N, floor(sqrt(N)), 1, MAXA));
    CASE(N = MAXN; A = groupedBitonicArray(N, 10, 1, MAXA));
    CASE(N = MAXN; A = groupedBitonicArray(N, N / 10, 1, MAXA));

    // Random
    CASE(N = rnd.nextInt(MAXN - 50, MAXN); A = randomArray(N, 1, MAXA));
    CASE(N = rnd.nextInt(MAXN - 50, MAXN);
         A = randomArray(N, floor(sqrt(N)), 1, MAXA));
    CASE(N = rnd.nextInt(MAXN - 50, MAXN); A = randomArray(N, N / 2, 1, MAXA));
    CASE(N = rnd.nextInt(MAXN - 50, MAXN); A = randomArray(N, N, 1, MAXA));

    // Almost Bitonic
    CASE(N = MAXN; A = swapArray(sortedArray(N, 1, MAXA), 20));
    CASE(N = MAXN; A = swapArray(sortedArray(N, N, 1, MAXA), 20));
    CASE(N = MAXN; A = swapArray(groupedBitonicArray(N, 10, 1, MAXA), 20));
    CASE(N = MAXN; A = swapArray(groupedBitonicArray(N, 10, N, 1, MAXA), 20));

    // Cartesian
    CASE(N = rnd.nextInt(MAXN - 50, MAXN);
         A = customCartesianTree(N, -1, 0, 1, 0, 0, 1, MAXA, N - N / 5, 100,
                                 1e-3));
    CASE(N = rnd.nextInt(MAXN - 50, MAXN);
         A = customCartesianTree(N, N, 0, 1, 0, 0, 1, MAXA, N - N / 5, 100,
                                 1e-3));
    CASE(N = rnd.nextInt(MAXN - 50, MAXN);
         A = customCartesianTree(N, -1, 0, 1, 0, 0, 1, MAXA, N - N / 5, 100,
                                 1e-3));
    CASE(N = rnd.nextInt(MAXN - 50, MAXN);
         A = customCartesianTree(N, N, 0, 1, 0, 0, 1, MAXA, N - N / 5, 100,
                                 1e-3));
  }

 private:
  void expandCoordinate(vector<int>& A, int K, int loC, int hiC) {
    vector<int> coords(K);
    for (int i = 0; i < K; i++) {
      coords[i] = rnd.nextInt(loC, hiC);
    }
    sort(begin(coords), end(coords));
    for (int i = 0; i < int(A.size()); i++) {
      assert(0 <= A[i] && A[i] < K);
      A[i] = coords[A[i]];
    }
  }

  vector<int> randomArray(int N, int loC, int hiC) {
    vector<int> ret(N);
    for (int i = 0; i < N; i++) {
      ret[i] = rnd.nextInt(loC, hiC);
    }
    return ret;
  }

  vector<int> randomArray(int N, int K, int loC, int hiC) {
    vector<int> ret = randomArray(N, 0, K - 1);
    expandCoordinate(ret, K, loC, hiC);
    return ret;
  }

  vector<int> sortedArray(int N, int loC, int hiC) {
    vector<int> ret = randomArray(N, loC, hiC);
    sort(begin(ret), end(ret));
    return ret;
  }

  vector<int> sortedArray(int N, int K, int loC, int hiC) {
    vector<int> ret = randomArray(N, K, loC, hiC);
    sort(begin(ret), end(ret));
    return ret;
  }

  vector<int> randomBitonicArray(int N, int loC, int hiC) {
    vector<int> coords(N);
    for (int i = 0; i < N; i++) {
      coords[i] = rnd.nextInt(loC, hiC);
    }
    sort(begin(coords), end(coords));
    deque<int> dq;
    for (auto c : coords) {
      if (rnd.nextInt(0, 1) == 0) {
        dq.emplace_back(c);
      } else {
        dq.emplace_front(c);
      }
    }
    vector<int> ret;
    for (auto i : dq) {
      ret.emplace_back(i);
    }
    if (is_sorted(begin(ret), end(ret))) {
      ret = randomBitonicArray(N, loC, hiC);
    }
    return ret;
  }

  vector<int> randomBitonicArray(int N, int K, int loC, int hiC) {
    vector<int> ret = randomBitonicArray(N, 0, K - 1);
    expandCoordinate(ret, K, loC, hiC);
    return ret;
  }

  vector<int> groupedBitonicArray(int N, int B, int loC, int hiC) {
    vector<int> coords(N);
    for (int i = 0; i < N; i++) {
      coords[i] = rnd.nextInt(loC, hiC);
    }
    sort(begin(coords), end(coords));
    vector<int> color;
    for (int i = 0; i < N; i++) {
      color.emplace_back(rnd.nextInt(0, B - 1));
    }
    sort(begin(color), end(color));
    deque<int> dq;
    for (int i = 0; i < N; i++) {
      if (color[i] & 1) {
        dq.emplace_back(coords[i]);
      } else {
        dq.emplace_front(coords[i]);
      }
    }
    vector<int> ret;
    for (auto i : dq) {
      ret.emplace_back(i);
    }
    if (is_sorted(begin(ret), end(ret))) {
      ret = groupedBitonicArray(N, B, loC, hiC);
    }
    return ret;
  }

  vector<int> groupedBitonicArray(int N, int B, int K, int loC, int hiC) {
    vector<int> ret = groupedBitonicArray(N, B, 0, K - 1);
    expandCoordinate(ret, K, loC, hiC);
    return ret;
  }

  vector<int> antiMagicArray(int N, int loC, int hiC) {
    assert(N % 2 == 0);
    vector<int> coords(N);
    for (int i = 0; i < N; i++) {
      coords[i] = rnd.nextInt(loC, hiC / 2);
    }
    vector<int> ret;
    sort(begin(coords), end(coords));
    coords.pop_back();
    coords.emplace_back(hiC);
    for (int i = 0; i < N; i++) {
      if (i + 1 < N) {
        if (i == 0) {
          coords[i + 1] =
              rnd.nextInt(coords[i], (coords[i + 2] + coords[i]) / 2);
          ret.emplace_back(coords[i + 1]);
          ret.emplace_back(coords[i]);
          ret.emplace_back(coords[i + 2]);
          i += 1;
        } else {
          ret.emplace_back(coords[i + 1]);
          ret.emplace_back(coords[i]);
        }
        i += 1;
      } else {
        ret.insert(begin(ret), coords[i]);
      }
    }
    assert(ret.size() == N);
    return ret;
  }

  vector<int> customCartesianTree(int N, int K, int antiNum, int antiC,
                                  int antiSizeL, int antiSizeR, int loC,
                                  int hiC, int longChain, int numLongChain,
                                  double probChangeDir) {
    vector<int> ret(N, -1);
    vector<pair<int, int>> ranges;
    int ID = 0;
    vector<int> placeMid(N);
    for (int i = 0; i < numLongChain; i++) {
      placeMid[i] = 1;
    }
    rnd.shuffle(begin(placeMid), end(placeMid));
    const auto Dfs = [&](const auto& self, int L, int R, int lastdir,
                         ordered_set<pair<int, int>>& oset) -> void {
      if (L > R) return;
      int id = ID++;
      int len = R - L + 1;
      assert(oset.size() == len);
      if (antiSizeL <= len && len <= antiSizeR) {
        if (len % 2 == 0) {
          ranges.emplace_back(L, R);
        } else {
          int p = rnd.nextInt(2);
          if (p == 0) {
            ret[L] = prev(end(oset))->first;
            oset.erase(prev(end(oset)));
            self(self, L + 1, R, 0, oset);
          } else {
            ret[R] = prev(end(oset))->first;
            oset.erase(prev(end(oset)));
            self(self, L, R - 1, 1, oset);
          }
        }
        return;
      }
      int M = -1;
      if (placeMid[id]) {
        M = rnd.nextInt(L, R);
      } else {
        if (lastdir == -1 || rnd.nextDouble(1) < probChangeDir) {
          lastdir = rnd.nextInt(2);
        }
        if (lastdir == 0) {
          M = rnd.nextInt(L, min(R, L + longChain));
        } else {
          M = rnd.nextInt(max(L, R - longChain), R);
        }
      }
      ret[M] = prev(end(oset))->first;
      oset.erase(prev(end(oset)));
      int cnt = min(M - L, R - M);
      ordered_set<pair<int, int>> other;
      while (cnt--) {
        int id = rnd.nextInt(oset.size());
        auto it = oset.find_by_order(id);
        other.insert(*it);
        oset.erase(it);
      }
      if (M - L <= R - M) {
        self(self, L, M - 1, lastdir == 0 ? -1 : lastdir, other);
        self(self, M + 1, R, lastdir == 1 ? -1 : lastdir, oset);
      } else {
        self(self, L, M - 1, lastdir == 0 ? -1 : lastdir, oset);
        self(self, M + 1, R, lastdir == 1 ? -1 : lastdir, other);
      }
    };
    ordered_set<pair<int, int>> oset;
    while (oset.size() < N) {
      oset.insert({K == -1 ? rnd.nextInt(loC, hiC) : rnd.nextInt(0, K - 1),
                   rnd.nextInt(MAXA)});
    }
    Dfs(Dfs, 0, N - 1, -1, oset);
    if (K != -1) {
      vector<int> coords(K);
      for (int i = 0; i < K; i++) {
        coords[i] = rnd.nextInt(loC, hiC);
      }
      sort(begin(coords), end(coords));
      for (int i = 0; i < N; i++) {
        if (ret[i] != -1) {
          assert(0 <= ret[i] && ret[i] < K);
          ret[i] = coords[ret[i]];
        }
      }
    }
    for (int i = 0; i < N; i++) {
      if (ret[i] != -1) {
        ret[i] *= antiC;
      }
    }
    rnd.shuffle(begin(ranges), end(ranges));
    for (int i = 0; i < int(ranges.size()); i++) {
      auto [l, r] = ranges[i];
      vector<int> anti = makeStrong(
          [&]() {
            return antiMagicArray(r - l + 1, 1,
                                  rnd.nextInt(2 * antiC / 3, antiC));
          },
          [&](auto x) {
            if (i < antiNum) {
              return solution_wa_magic::Solve(x);
            } else {
              return -1ll;
            }
          },
          &solution::Solve, MAX_TIME_ANTI_ARRAY);
      for (int j = l; j <= r; j++) {
        ret[j] = anti[j - l];
      }
    }
    return ret;
  }

  vector<int> swapArray(vector<int> A, int swaps) {
    while (swaps--) {
      int i = rnd.nextInt(A.size());
      int j = rnd.nextInt(A.size());
      swap(A[i], A[j]);
    }
    return A;
  }

  template <typename T, typename U>
  vector<int> makeStrong(const T& test, const U& condition,
                         const double MAX_TIME = 10.0) {
    const double start_time = clock();
    vector<int> ret = test();
    int count_iters = 0;
    while ((double(clock() - start_time) / CLOCKS_PER_SEC < MAX_TIME) &&
           !condition(ret)) {
      ret = test();
      count_iters++;
      if (count_iters % 10000 == 0) {
        cerr << "Current it: " << count_iters << '\n';
      }
    }
    if (!condition(ret)) {
      cerr << "fail to generate counter\n";
    }
    return ret;
  }

  template <typename T, typename U, typename S>
  vector<int> makeStrong(const T& test, const U& wa, const S& ac,
                         const double MAX_TIME = 10.0) {
    return makeStrong(
        test, [&](auto x) { return wa(x) != ac(x); }, MAX_TIME);
  }

  template <typename T>
  bool isBitonic(const vector<T>& A) {
    int k = 1;
    while (k < int(A.size()) && A[k - 1] >= A[k]) {
      k += 1;
    }
    return is_sorted(begin(A) + k, end(A));
  }
};

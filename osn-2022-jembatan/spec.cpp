#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

#include "common_include.hpp"

using namespace std;
using namespace tcframe;

constexpr int SmallN = 1000;
constexpr int MaxN = 100000;
constexpr int MaxM = 200000;
constexpr int MaxH = 1000000000;

class ProblemSpec : public BaseProblemSpec
{

protected:
  int N, M, Q;
  vector<int> U, V, H;
  long long total;
  int B;
  vector<int> S, T;

  void StyleConfig()
  {
    CustomScorer();
  }

  void
  InputFormat()
  {
    LINE(N, M, Q);
    LINE(H % SIZE(N));
    LINES(U, V) % SIZE(M);
  }

  void OutputFormat1()
  {
    LINE(total);
  }

  void OutputFormat2()
  {
    LINE(total);
    LINE(B);
    LINES(S, T) % SIZE(B);
  }

  void GradingConfig()
  {
    TimeLimit(1);
    MemoryLimit(64);
  }

  void Constraints()
  {
    CONS(1 <= N && N <= MaxN);
    CONS(0 <= M && M <= MaxM);
    CONS(Q == 0 || Q == 1);
    CONS(U.size() == V.size());
    CONS(N == H.size());
    CONS(M == U.size());
    CONS(eachElementBetween(U, 1, N));
    CONS(eachElementBetween(V, 1, N));
    CONS(eachElementBetween(H, 1, MaxH));
    CONS(noSelfLoop(U, V));
    CONS(noRepeatedEdges(U, V));
    CONS(vectorElementsSmaller(U, V));
  }

  void Subtask1()
  {
    Points(7);

    CONS(N == 15);
    CONS(M == 15);
    CONS(Q == 1);
    CONS(H == vector<int>({1, 6, 9, 1, 6, 10, 2, 6, 8, 1, 7, 10, 3, 4, 5}));
    CONS(U == vector<int>({1, 2, 1, 4, 5, 4, 7, 7, 8, 10, 11, 10, 13, 13, 14}));
    CONS(V == vector<int>({2, 3, 3, 6, 6, 5, 9, 8, 9, 12, 12, 11, 14, 15, 15}));
  }

  void Subtask2()
  {
    Points(8);

    CONS(M == N - 2);
    CONS(edgesConnectConsecutiveNodes(U, V));
    CONS(vectorContentsEqualRange(U, 1, 1));
    CONS(vectorContentsEqualRange(V, 2, 1));
    CONS(numberOfComponents(N, U, V) == 2);
  }

  void Subtask3()
  {
    Points(11);

    CONS(N == 2 * M);
    CONS(edgesConnectConsecutiveNodes(U, V));
    CONS(vectorContentsEqualRange(U, 1, 2));
    CONS(vectorContentsEqualRange(V, 2, 2));
    CONS(numberOfComponents(N, U, V) == N / 2);
  }

  void Subtask4()
  {
    Points(27);
    CONS(eachElementBetween(H, 1, 1));
  }

  void Subtask5()
  {
    Points(10);
    CONS(N <= SmallN);
    CONS(numberOfComponents(N, U, V) <= 2);
  }

  void Subtask6()
  {
    Points(13);
    CONS(N <= SmallN);
    CONS(Q == 0);
  }

  void Subtask7()
  {
    Points(12);
    CONS(Q == 0);
  }

  void Subtask8()
  {
    Points(12);
  }

private:
  bool eachElementBetween(const vector<int> &v, int lo, int hi)
  {
    for (int x : v)
    {
      if (x < lo || x > hi)
      {
        return false;
      }
    }
    return true;
  }

  bool allAreEqual(const vector<int> &v)
  {
    for (int x : v)
    {
      if (x != v[0])
      {
        return false;
      }
    }
    return true;
  }

  bool noSelfLoop(const vector<int> &u, const vector<int> &v)
  {
    assert(u.size() == v.size());
    for (int i = 0; i < u.size(); i++)
    {
      if (u[i] == v[i])
      {
        return false;
      }
    }
    return true;
  }

  bool noRepeatedEdges(const vector<int> &u, const vector<int> &v)
  {
    assert(u.size() == v.size());

    set<pair<int, int>> edges;
    for (int i = 0; i < u.size(); i++)
    {
      auto findIt = edges.find(make_pair(u[i], v[i]));
      if (findIt != edges.end())
        return false;

      edges.emplace(u[i], v[i]);
    }
    return true;
  }

  bool vectorElementsSmaller(const vector<int> &u, const vector<int> &v)
  {
    assert(u.size() == v.size());
    for (int i = 0; i < u.size(); i++)
    {
      if (u[i] >= v[i])
        return false;
    }

    return true;
  }

  bool edgesConnectConsecutiveNodes(const vector<int> &u, const vector<int> &v)
  {
    assert(u.size() == v.size());
    for (int i = 0; i < u.size(); i++)
    {
      if (u[i] != v[i] - 1)
        return false;
    }
    return true;
  }

  bool vectorContentsEqualRange(const vector<int> &v, int start, int inc)
  {
    std::vector<int> vv(v.begin(), v.end());
    sort(vv.begin(), vv.end());
    for (int i = 0, val = start; i < vv.size(); ++i, val += inc)
    {
      if (vv[i] != val)
        return false;
    }

    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec>
{
protected:
  void SampleTestCase1()
  {
    Subtasks({8});
    Input({"5 2 1",
           "4 6 1 3 2",
           "1 3",
           "2 4"});

    Output({"10",
            "2",
            "1 4",
            "3 5"});
  }

  void SampleTestCase2()
  {
    Subtasks({8});
    Input({"5 1 1",
           "2 1 4 3 4",
           "3 5"});

    Output({"-1"});
  }

  void SampleTestCase3()
  {
    Subtasks({5, 6, 7, 8});
    Input({"3 1 0",
           "2 8 1",
           "1 3"});

    Output({"9"});
  }

  void BeforeTestCase()
  {
    U.clear();
    V.clear();
    H.clear();
  }

  void TestGroup1()
  {
    Subtasks({1, 8});
    CASE(N = 15, M = 15, Q = 1, H = {1, 6, 9, 1, 6, 10, 2, 6, 8, 1, 7, 10, 3, 4, 5},
         U = {1, 2, 1, 4, 5, 4, 7, 7, 8, 10, 11, 10, 13, 13, 14}, V = {2, 3, 3, 6, 6, 5, 9, 8, 9, 12, 12, 11, 14, 15, 15});
  }

  void TestGroup2()
  {
    // ST1, Small N, Q = 0
    Subtasks({2, 5, 6, 7, 8});
    CASE(N = 382, M = N - 2, Q = 0, linearTree(N - 1, U, V), randomH(N, H, 1, MaxH));
    CASE(N = 777, M = N - 2, Q = 0, linearTree(N - 1, U, V), randomH(N, H, 1, MaxH));
    CASE(N = 1000, M = N - 2, Q = 0, linearTree(N - 1, U, V), randomH(N, H, 1, MaxH));
    CASE(N = 1000, M = N - 2, Q = 0, linearTree(N - 1, U, V), H.assign(N, MaxH));
  }

  void TestGroup3()
  {
    // ST1, Small N, Q = 1
    Subtasks({2, 5, 8});
    CASE(N = 253, M = N - 2, Q = 1, linearTree(N - 1, U, V), randomH(N, H, 1, MaxH));
    CASE(N = 185, M = N - 2, Q = 1, linearTree(N - 1, U, V), randomH(N, H, 1, MaxH));
    CASE(N = 823, M = N - 2, Q = 1, linearTree(N - 1, U, V), randomH(N, H, 1, MaxH));
    CASE(N = 1000, M = N - 2, Q = 1, linearTree(N - 1, U, V), randomH(N, H, 1, MaxH));
  }

  void TestGroup4()
  {
    Subtasks({2, 7, 8});
    CASE(N = 10810, M = N - 2, Q = 0, linearTree(N - 1, U, V), randomH(N, H, 1, MaxH));
    CASE(N = 80818, M = N - 2, Q = 0, linearTree(N - 1, U, V), randomH(N, H, 1, MaxH));
    CASE(N = 100000, M = N - 2, Q = 0, linearTree(N - 1, U, V), randomH(N, H, 1, MaxH));
    CASE(N = 100000, M = N - 2, Q = 0, linearTree(N - 1, U, V), H.assign(N, MaxH));
  }

  void TestGroup5()
  {
    Subtasks({2, 8});
    CASE(N = 25382, M = N - 2, Q = 1, linearTree(N - 1, U, V), randomH(N, H, 1, MaxH));
    CASE(N = 12191, M = N - 2, Q = 1, linearTree(N - 1, U, V), randomH(N, H, 1, MaxH));
    CASE(N = 95959, M = N - 2, Q = 1, linearTree(N - 1, U, V), randomH(N, H, 1, MaxH));
    CASE(N = 100000, M = N - 2, Q = 1, linearTree(N - 1, U, V), randomH(N, H, 1, MaxH));
  }

  void TestGroup6()
  {
    Subtasks({3, 6, 7, 8});
    CASE(N = 888, M = N / 2, Q = 0, evenOddEdges(N, U, V), randomH(N, H, 1, MaxH));
    CASE(N = 950, M = N / 2, Q = 0, evenOddEdges(N, U, V), randomH(N, H, 1, MaxH));
    CASE(N = 1000, M = N / 2, Q = 0, evenOddEdges(N, U, V), randomH(N, H, 1, MaxH));
  }

  void TestGroup7()
  {
    Subtasks({3, 7, 8});
    CASE(N = 23112, M = N / 2, Q = 0, evenOddEdges(N, U, V), randomH(N, H, 1, MaxH));
    CASE(N = 99560, M = N / 2, Q = 0, evenOddEdges(N, U, V), randomH(N, H, MaxH - 10, MaxH));
    CASE(N = 100000, M = N / 2, Q = 0, evenOddEdges(N, U, V), randomH(N, H, 1, MaxH));
    CASE(N = 100000, M = N / 2, Q = 0, evenOddEdges(N, U, V), randomH(N, H, MaxH - 10, MaxH));
  }

  void TestGroup8()
  {
    Subtasks({3, 8});
    CASE(N = 25382, M = N / 2, Q = 1, evenOddEdges(N, U, V), randomH(N, H, 1, MaxH));
    CASE(N = 98766, M = N / 2, Q = 1, evenOddEdges(N, U, V), randomH(N, H, MaxH - 10, MaxH));
    CASE(N = 100000, M = N / 2, Q = 1, evenOddEdges(N, U, V), randomH(N, H, 1, MaxH));
    CASE(N = 100000, M = N / 2, Q = 1, evenOddEdges(N, U, V), randomH(N, H, MaxH - 10, MaxH));
  }

  void TestGroup9()
  {
    Subtasks({4, 5, 6, 7, 8});

    // Total = 0 (c = 1)
    CASE(N = 808, M = 1000, Q = 0, randomGraph(N, M, U, V), H.assign(N, 1));
    CASE(N = 1000, M = 20000, Q = 0, randomGraph(N, M, U, V), H.assign(N, 1));

    // c = 2
    CASE(N = 990, Q = 0, randomDisconnectedGraph(N, U, V, 500, 700), M = U.size(), H.assign(N, 1));
    CASE(N = 1000, Q = 0, randomDisconnectedGraph(N, U, V, 500, 700), M = U.size(), H.assign(N, 1));
  }

  void TestGroup10()
  {
    // Total = -1
    Subtasks({4, 6, 7, 8});
    CASE(N = 101, M = 0, Q = 0, U = {}, V = {}, H.assign(N, 1));
    CASE(N = 1000, M = 0, Q = 0, U = {}, V = {}, H.assign(N, 1));
    CASE(N = 101, M = N / 2 - 1, Q = 0, randomGraph(N / 2 - 1, M, U, V), H.assign(N, 1));
    CASE(N = 1000, M = N / 2 - 1, Q = 0, randomGraph(N / 2 - 1, M, U, V), H.assign(N, 1));

    // c > 2
    CASE(N = 900, Q = 0, randomDisconnectedGraph(N, U, V, 200, 300), M = U.size(), H.assign(N, 1));

    for (int t = 0; t < 2; t++) {
      CASE(N = 1000, Q = 0, randomDisconnectedGraph(N, U, V, 1, 5), M = U.size(), H.assign(N, 1));
      CASE(N = 1000, Q = 0, randomDisconnectedGraph(N, U, V, 5, 10), M = U.size(), H.assign(N, 1));
      CASE(N = 1000, Q = 0, randomDisconnectedGraph(N, U, V, 10, 20), M = U.size(), H.assign(N, 1));
      CASE(N = 1000, Q = 0, randomDisconnectedGraph(N, U, V, 20, 50), M = U.size(), H.assign(N, 1));
      CASE(N = 1000, Q = 0, randomDisconnectedGraph(N, U, V, 50, 100), M = U.size(), H.assign(N, 1));
      CASE(N = 1000, Q = 0, randomDisconnectedGraph(N, U, V, 100, 200), M = U.size(), H.assign(N, 1));
      CASE(N = 1000, Q = 0, randomDisconnectedGraph(N, U, V, 200, 300), M = U.size(), H.assign(N, 1));
    }
  }

  void TestGroup11()
  {
    Subtasks({4, 7, 8});

    // c > 2
    CASE(N = 80000, Q = 0, randomDisconnectedGraph(N, U, V, 1000, 2000), M = U.size(), H.assign(N, 1));
    CASE(N = 99900, Q = 0, randomDisconnectedGraph(N, U, V, 2000, 4000), M = U.size(), H.assign(N, 1));

    CASE(N = 100000, Q = 0, randomDisconnectedGraph(N, U, V, 1, 5), M = U.size(), H.assign(N, 1));
    CASE(N = 100000, Q = 0, randomDisconnectedGraph(N, U, V, 5, 10), M = U.size(), H.assign(N, 1));
    CASE(N = 100000, Q = 0, randomDisconnectedGraph(N, U, V, 10, 20), M = U.size(), H.assign(N, 1));
    CASE(N = 100000, Q = 0, randomDisconnectedGraph(N, U, V, 20, 50), M = U.size(), H.assign(N, 1));
    CASE(N = 100000, Q = 0, randomDisconnectedGraph(N, U, V, 50, 100), M = U.size(), H.assign(N, 1));
    CASE(N = 100000, Q = 0, randomDisconnectedGraph(N, U, V, 100, 1000), M = U.size(), H.assign(N, 1));
    CASE(N = 100000, Q = 0, randomDisconnectedGraph(N, U, V, 1000, 10000), M = U.size(), H.assign(N, 1));
  }

  void TestGroup12()
  {
    // Total = -1
    Subtasks({4, 8});
    CASE(N = 1000, M = 0, Q = 1, U = {}, V = {}, H.assign(N, 1));
    CASE(N = 101, M = N / 2 - 1, Q = 1, randomGraph(N / 2 - 1, M, U, V), H.assign(N, 1));
    CASE(N = 1000, M = N / 2 - 1, Q = 1, randomGraph(N / 2 - 1, M, U, V), H.assign(N, 1));

    // Total = 0 (c = 1)
    CASE(N = 25382, M = 30000, Q = 1, randomGraph(N, M, U, V), H.assign(N, 1));
    CASE(N = 18583, M = 20000, Q = 1, randomGraph(N, M, U, V), H.assign(N, 1));
    CASE(N = 100000, M = 200000, Q = 1, randomGraph(N, M, U, V), H.assign(N, 1));

    // c > 2
    CASE(N = 100000, Q = 1, randomDisconnectedGraph(N, U, V, 1, 5), M = U.size(), H.assign(N, 1));
    CASE(N = 100000, Q = 1, randomDisconnectedGraph(N, U, V, 5, 10), M = U.size(), H.assign(N, 1));
    CASE(N = 100000, Q = 1, randomDisconnectedGraph(N, U, V, 10, 20), M = U.size(), H.assign(N, 1));
    CASE(N = 100000, Q = 1, randomDisconnectedGraph(N, U, V, 20, 50), M = U.size(), H.assign(N, 1));
    CASE(N = 100000, Q = 1, randomDisconnectedGraph(N, U, V, 50, 100), M = U.size(), H.assign(N, 1));
    CASE(N = 100000, Q = 1, randomDisconnectedGraph(N, U, V, 100, 1000), M = U.size(), H.assign(N, 1));
    CASE(N = 100000, Q = 1, randomDisconnectedGraph(N, U, V, 1000, 10000), M = U.size(), H.assign(N, 1));
  }

  void TestGroup13()
  {
    Subtasks({5, 6, 7, 8});

    // Total = 0 (c = 1)
    CASE(N = 707, M = 1000, Q = 0, randomGraph(N, M, U, V), randomH(N, H, 1, MaxH));
    CASE(N = 1000, M = 20000, Q = 0, randomGraph(N, M, U, V), randomH(N, H, 1, MaxH));

    // c = 2
    CASE(N = 990, Q = 0, randomDisconnectedGraph(N, U, V, 500, 700), M = U.size(), randomH(N, H, 1, MaxH));
    CASE(N = 1000, Q = 0, randomDisconnectedGraph(N, U, V, 600, 700), M = U.size(), randomH(N, H, 1, MaxH));
  }

  void TestGroup14()
  {
    Subtasks({5, 8});

    // Total = 0 (c = 1)
    CASE(N = 909, M = 1000, Q = 1, randomGraph(N, M, U, V), randomH(N, H, 1, MaxH));
    CASE(N = 1000, M = 20000, Q = 1, randomGraph(N, M, U, V), randomH(N, H, 1, MaxH));

    // c = 2
    CASE(N = 990, Q = 1, randomDisconnectedGraph(N, U, V, 500, 700), M = U.size(), randomH(N, H, 1, MaxH));
    CASE(N = 1000, Q = 1, randomDisconnectedGraph(N, U, V, 600, 700), M = U.size(), randomH(N, H, 1, MaxH));
  }

  void TestGroup15()
  {
    // Total = -1
    Subtasks({6, 7, 8});
    CASE(N = 1000, M = N / 2 - 1, Q = 0, randomGraph(N / 2 - 1, M, U, V), randomH(N, H, 1, MaxH));
    CASE(N = 100, M = 0, Q = 0, U = {}, V = {}, randomH(N, H, 1, MaxH));

    CASE(N = 100, M = 0, Q = 0, U = {}, V = {}, randomH(N, H, 1, MaxH));
    CASE(N = 1000, M = 0, Q = 0, U = {}, V = {}, randomH(N, H, 1, MaxH));
    CASE(N = 101, M = N / 2 - 1, Q = 0, randomGraph(N / 2 - 1, M, U, V), randomH(N, H, 1, MaxH));
    CASE(N = 1000, M = N / 2 - 1, Q = 0, randomGraph(N / 2 - 1, M, U, V), randomH(N, H, 1, MaxH));

    // c > 2
    CASE(N = 900, Q = 0, randomDisconnectedGraph(N, U, V, 200, 300), M = U.size(), randomH(N, H, 1, MaxH));

    for (int t = 0; t < 2; t++) {
      CASE(N = 1000, Q = 0, randomDisconnectedGraph(N, U, V, 1, 5), M = U.size(), randomH(N, H, 1, MaxH));
      CASE(N = 1000, Q = 0, randomDisconnectedGraph(N, U, V, 5, 10), M = U.size(), randomH(N, H, 1, MaxH));
      CASE(N = 1000, Q = 0, randomDisconnectedGraph(N, U, V, 10, 20), M = U.size(), randomH(N, H, 1, MaxH));
      CASE(N = 1000, Q = 0, randomDisconnectedGraph(N, U, V, 20, 50), M = U.size(), randomH(N, H, 1, MaxH));
      CASE(N = 1000, Q = 0, randomDisconnectedGraph(N, U, V, 50, 100), M = U.size(), randomH(N, H, 1, MaxH));
      CASE(N = 1000, Q = 0, randomDisconnectedGraph(N, U, V, 100, 200), M = U.size(), randomH(N, H, 1, MaxH));
      CASE(N = 1000, Q = 0, randomDisconnectedGraph(N, U, V, 200, 300), M = U.size(), randomH(N, H, 1, MaxH));
    }
  }

  void TestGroup16()
  {
    // Total = -1
    Subtasks({7, 8});
    CASE(N = 10010, M = 0, Q = 0, U = {}, V = {}, randomH(N, H, 1, MaxH));
    CASE(N = 25038, M = 0, Q = 0, U = {}, V = {}, randomH(N, H, 1, MaxH));

    // Total = 0 (c = 1)
    CASE(N = 99000, M = 150000, Q = 0, randomGraph(N, M, U, V), randomH(N, H, 1, MaxH));
    CASE(N = 100000, M = 200000, Q = 0, randomGraph(N, M, U, V), randomH(N, H, 1, MaxH));

    // c > 2
    CASE(N = 100000, Q = 0, randomDisconnectedGraph(N, U, V, 1000, 2000), M = U.size(), randomH(N, H, MaxH - 100, MaxH));

    CASE(N = 100000, Q = 0, randomDisconnectedGraph(N, U, V, 1, 5), M = U.size(), randomH(N, H, 1, MaxH));
    CASE(N = 100000, Q = 0, randomDisconnectedGraph(N, U, V, 5, 10), M = U.size(), randomH(N, H, 1, MaxH));
    CASE(N = 100000, Q = 0, randomDisconnectedGraph(N, U, V, 10, 20), M = U.size(), randomH(N, H, 1, MaxH));
    CASE(N = 100000, Q = 0, randomDisconnectedGraph(N, U, V, 20, 50), M = U.size(), randomH(N, H, 1, MaxH));
    CASE(N = 100000, Q = 0, randomDisconnectedGraph(N, U, V, 50, 100), M = U.size(), randomH(N, H, 1, MaxH));
    CASE(N = 100000, Q = 0, randomDisconnectedGraph(N, U, V, 100, 1000), M = U.size(), randomH(N, H, 1, MaxH));
    CASE(N = 100000, Q = 0, randomDisconnectedGraph(N, U, V, 1000, 10000), M = U.size(), randomH(N, H, 1, MaxH));
  }

  void TestGroup17()
  {
    // Total = -1
    Subtasks({8});
    CASE(N = 41082, M = N / 2 - 1, Q = 1, randomGraph(N / 2 - 1, M, U, V), randomH(N, H, 1, MaxH));
    CASE(N = 100000, M = N / 2 - 1, Q = 1, randomGraph(N / 2 - 1, M, U, V), randomH(N, H, 1, MaxH));

    // Total = 0 (c = 1)
    CASE(N = 99000, M = 150000, Q = 1, randomGraph(N, M, U, V), randomH(N, H, 1, MaxH));
    CASE(N = 100000, M = 200000, Q = 1, randomGraph(N, M, U, V), randomH(N, H, 1, MaxH));

    // c > 2
    CASE(N = 100000, Q = 1, randomDisconnectedGraph(N, U, V, 1000, 2000), M = U.size(), randomH(N, H, MaxH - 100, MaxH));

    CASE(N = 100000, Q = 1, randomDisconnectedGraph(N, U, V, 1, 5), M = U.size(), randomH(N, H, 1, MaxH));
    CASE(N = 100000, Q = 1, randomDisconnectedGraph(N, U, V, 5, 10), M = U.size(), randomH(N, H, 1, MaxH));
    CASE(N = 100000, Q = 1, randomDisconnectedGraph(N, U, V, 10, 20), M = U.size(), randomH(N, H, 1, MaxH));
    CASE(N = 100000, Q = 1, randomDisconnectedGraph(N, U, V, 20, 50), M = U.size(), randomH(N, H, 1, MaxH));
    CASE(N = 100000, Q = 1, randomDisconnectedGraph(N, U, V, 50, 100), M = U.size(), randomH(N, H, 1, MaxH));
    CASE(N = 100000, Q = 1, randomDisconnectedGraph(N, U, V, 100, 1000), M = U.size(), randomH(N, H, 1, MaxH));
    CASE(N = 100000, Q = 1, randomDisconnectedGraph(N, U, V, 1000, 10000), M = U.size(), randomH(N, H, 1, MaxH));
  }

private:
  void randomH(int n, vector<int> &h, int minH = 1, int maxH = MaxH)
  {
    for (int i = 0; i < n; i++)
    {
      h.push_back(rnd.nextInt(minH, maxH));
    }
  }

  void linearTree(int n, vector<int> &u, vector<int> &v)
  {
    u.resize(n - 1);
    v.resize(n - 1);
    iota(u.begin(), u.end(), 1);
    iota(v.begin(), v.end(), 2);
  }

  void evenOddEdges(int n, vector<int> &u, vector<int> &v)
  {
    assert(n % 2 == 0);

    u.resize(n / 2);
    v.resize(n / 2);
    for (int i = 1; i <= n / 2; i++)
    {
      u[i - 1] = 2 * i - 1;
      v[i - 1] = 2 * i;
    }
  }

  template <typename T>
  void apply_permutation(vector<T> &v, const vector<int> &perm)
  {
    vector<int> indices(perm);
    for (size_t i = 0; i < indices.size(); i++)
    {
      auto current = i;
      while (i != static_cast<size_t>(indices[current]))
      {
        auto next = indices[current];
        swap(v[current], v[next]);
        indices[current] = current;
        current = next;
      }
      indices[current] = current;
    }
  }

  void reshuffle_edges(vector<int> &u, vector<int> &v)
  {
    assert(u.size() == v.size());
    vector<int> nodes, mappedNodes;
    for (int i = 0; i < u.size(); i++) {
      nodes.emplace_back(u[i]);
      nodes.emplace_back(v[i]);
    }
    sort(begin(nodes), end(nodes));
    nodes.resize(unique(begin(nodes), end(nodes)) - begin(nodes));
    mappedNodes = nodes;
    rnd.shuffle(begin(mappedNodes), end(mappedNodes));

    vector<pair<int, int>> edges;
    for (int i = 0; i < u.size(); ++i) {
      int x = lower_bound(begin(nodes), end(nodes), u[i]) - begin(nodes);
      int y = lower_bound(begin(nodes), end(nodes), v[i]) - begin(nodes);
      edges.emplace_back(mappedNodes[x], mappedNodes[y]);
    }

    vector<int> permutation;
    for (int i = 0; i < u.size(); i++)
    {
      permutation.push_back(i);
    }
    rnd.shuffle(permutation.begin(), permutation.end());
    apply_permutation(edges, permutation);

    for (int i = 0; i < edges.size(); i++)
    {
      u[i] = edges[i].first;
      v[i] = edges[i].second;
      if (u[i] > v[i]) swap(u[i], v[i]);
    }
  }

  void randomTree(int n, vector<int> &u, vector<int> &v, int offset = 0)
  {
    for (int i = 2; i <= n; i++)
    {
      u.push_back(rnd.nextInt(1, i - 1) + offset);
      v.push_back(i + offset);
    }
  }

  void randomGraph(int n, int m, vector<int> &u, vector<int> &v, int offset = 0)
  {
    randomTree(n, u, v, offset);
    set<pair<int, int>> edges;
    for (int i = 0; i < u.size(); i++)
      edges.emplace(u[i], v[i]);

    while (u.size() < m)
    {
      int newU = rnd.nextInt(1, n - 1);
      int newV = rnd.nextInt(newU + 1, n);
      if (edges.find(make_pair(newU + offset, newV + offset)) == edges.end())
      {
        u.push_back(newU + offset);
        v.push_back(newV + offset);
        edges.emplace(newU + offset, newV + offset);
      }
    }

    reshuffle_edges(u, v);
  }

  void randomDisconnectedGraph(int n, vector<int> &u, vector<int> &v, int minSizeComp, int maxSizeComp)
  {
    assert(minSizeComp >= 1);
    assert(maxSizeComp <= n);
    assert(minSizeComp <= maxSizeComp);

    int totalN = 0;
    while (totalN < n - maxSizeComp)
    {
      int nCurrent = rnd.nextInt(minSizeComp, maxSizeComp);
      int mCurrent = min(nCurrent * (nCurrent - 1) / 2, rnd.nextInt(nCurrent, 2 * nCurrent));
      vector<int> uCurrent, vCurrent;
      randomGraph(nCurrent, mCurrent, uCurrent, vCurrent, totalN);
      u.insert(u.end(), uCurrent.begin(), uCurrent.end());
      v.insert(v.end(), vCurrent.begin(), vCurrent.end());
      totalN += nCurrent;
    }

    if (totalN < n)
    {
      int nCurrent = n - totalN;
      int mCurrent = min(nCurrent * (nCurrent - 1) / 2, rnd.nextInt(nCurrent, 2 * nCurrent));
      vector<int> uCurrent, vCurrent;
      randomGraph(nCurrent, mCurrent, uCurrent, vCurrent, totalN);

      u.insert(u.end(), uCurrent.begin(), uCurrent.end());
      v.insert(v.end(), vCurrent.begin(), vCurrent.end());
    }

    reshuffle_edges(u, v);
  }
};
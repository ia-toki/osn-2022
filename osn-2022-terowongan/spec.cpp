#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 140, MAXW = 1000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, A, B;
  bool P;
  vector< vector<bool> > adj;

  void InputFormat() {
    LINE(N, A, B, P);
    GRID(adj) % SIZE(N, N);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(256);
  }

  void StyleConfig() {
    InteractiveEvaluator();
  }

  void Constraints() {
    CONS(2 <= N && N <= MAXN);
    CONS(1 <= A && A < B && B <= MAXW);
    CONS(validGraph(adj));
  }

  void Subtask1() {
    Points(14);
    CONS(!P);
    CONS(N <= 5);
  }

  void Subtask2() {
    Points(11);
    CONS(!P);
    CONS(N <= 60);
  }

  void Subtask3() {
    Points(16);
    CONS(!P);
    CONS(A == 1);
    CONS(B == 2);
    CONS(directedForest(adj));
  }

  void Subtask4() {
    Points(15);
    CONS(!P);
    CONS(A == 1);
    CONS(B == 2);
  }

  void Subtask5() {
    Points(9);
    CONS(!P);
    CONS(countEdges(adj) <= 1);
  }

  void Subtask6() {
    Points(35);
  }

 private:
  bool validGraph(vector< vector<bool> > adj) {
    int n = adj.size();
    for (int i=0; i<n; i++) {
      if (adj[i].size() != n) {
        return false;
      }
      if (adj[i][i]) {
        return false;
      }
      for (int j=0; j<i; j++) {
        if (adj[i][j] != adj[j][i]) {
          return false;
        }
      }
    }
    return true;
  }

  bool directedForest(vector< vector<bool> > adj) {
    int n = adj.size();
    for (int i=0; i<n; i++) {
      int cnt = 0;
      for (int j=i+1; j<n; j++) {
        if (adj[i][j]) {
          cnt++;
        }
      }
      if (cnt > 1) {
        return false;
      }
    }
    return true;
  }

  int countEdges(vector< vector<bool> > adj) {
    int n = adj.size();
    int cnt = 0;
    for (int i=0; i<n; i++) {
      for (int j=i+1; j<n; j++) {
        if (adj[i][j]) {
          cnt++;
        }
      }
    }
    return cnt;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({1, 2, 4, 6});
    Input({
      "4 1 2 0",
      "0 1 1 0",
      "1 0 0 0",
      "1 0 0 0",
      "0 0 0 0"
    });
  }

  void BeforeTestCase() {
    A = 1;
    B = 2;
    P = false;
  }

  void AfterTestCase() {
    for (int i=0; i<N; i++) {
      adj[i][i] = false;
      for (int j=0; j<i; j++) {
        adj[i][j] = adj[j][i] = adj[i][j] | adj[j][i];
      }
    }
  }

  void TestGroup1() {
    Subtasks({1, 2, 3, 4, 5, 6});
    CASE(N=2, adj=emptyGraph(N));
    CASE(N=2, adj=emptyGraph(N), addRandomEdges(N, 1));
    CASE(N=5, adj=emptyGraph(N));
    CASE(N=5, adj=emptyGraph(N), addRandomEdges(N, 1));
  }

  void TestGroup2() {
    Subtasks({1, 2, 6});
    CASE(N=5, randomWeight(), adj=emptyGraph(N), lineGraph(N, true));
    CASE(N=5, randomWeight(), adj=emptyGraph(N), spanningTree(N));
    CASE(N=5, randomWeight(), adj=emptyGraph(N), twoCompletes(N));
    CASE(N=5, randomWeight(), adj=emptyGraph(N), addRandomEdges(N, N*(N-1)/2-1));
    CASE(N=5, randomWeight(), adj=emptyGraph(N), addRandomEdges(N, N*(N-1)/2));
  }

  void TestGroup3() {
    Subtasks({2, 5, 6});
    CASE(N=60, randomWeight(), adj=emptyGraph(N));
    CASE(N=60, randomWeight(), adj=emptyGraph(N), addRandomEdges(N, 1));
  }

  void TestGroup4() {
    Subtasks({2, 6});
    CASE(N=60, randomWeight(), adj=emptyGraph(N), lineGraph(N, true));
    CASE(N=60, randomWeight(), adj=emptyGraph(N), directedStar(N));
    CASE(N=60, randomWeight(), adj=emptyGraph(N), directedForest(N));
    CASE(N=60, randomWeight(), adj=emptyGraph(N), spanningTree(N));
    CASE(N=60, randomWeight(), adj=emptyGraph(N), twoCompletes(N));
    CASE(N=60, randomWeight(), adj=emptyGraph(N), addRandomEdges(N, 2*N));
    CASE(N=60, randomWeight(), adj=emptyGraph(N), addRandomEdges(N, 8*N));
    CASE(N=60, randomWeight(), adj=emptyGraph(N), addRandomEdges(N, N*(N-1)/4));
    CASE(N=60, randomWeight(), adj=emptyGraph(N), addRandomEdges(N, N*(N-1)/2-1));
    CASE(N=60, randomWeight(), adj=emptyGraph(N), addRandomEdges(N, N*(N-1)/2));
  }

  void TestGroup5() {
    Subtasks({3, 4, 5, 6});
    CASE(N=140, adj=emptyGraph(N));
    CASE(N=140, adj=emptyGraph(N), addRandomEdges(N, 1));
  }

  void TestGroup6() {
    Subtasks({3, 4, 6});
    CASE(N=140, adj=emptyGraph(N), lineGraph(N, false));
    CASE(N=140, adj=emptyGraph(N), directedStar(N));
    for (int i=1; i<=3; i++) {
      CASE(N=140, adj=emptyGraph(N), directedForest(N));
    }
  }

  void TestGroup7() {
    Subtasks({4, 6});
    CASE(N=140, adj=emptyGraph(N), lineGraph(N, true));
    CASE(N=140, adj=emptyGraph(N), lineGraph(N, true), addRandomEdges(N, N/2));
    CASE(N=140, adj=emptyGraph(N), directedStar(N), addRandomEdges(N, N/2));
    CASE(N=140, adj=emptyGraph(N), directedForest(N), addRandomEdges(N, N/2));
    CASE(N=140, adj=emptyGraph(N), spanningTree(N));
    CASE(N=140, adj=emptyGraph(N), spanningTree(N), addRandomEdges(N, N/2));
    CASE(N=140, adj=emptyGraph(N), twoCompletes(N));
    CASE(N=140, adj=emptyGraph(N), addRandomEdges(N, 2*N));
    CASE(N=140, adj=emptyGraph(N), addRandomEdges(N, 12*N));
    CASE(N=140, adj=emptyGraph(N), addRandomEdges(N, N*(N-1)/4));
    CASE(N=140, adj=emptyGraph(N), addRandomEdges(N, N*(N-1)/2-1));
    CASE(N=140, adj=emptyGraph(N), addRandomEdges(N, N*(N-1)/2));
  }

  void TestGroup8() {
    Subtasks({5, 6});
    CASE(N=140, randomWeight(), adj=emptyGraph(N));
    for (int i=1; i<=5; i++) {
      CASE(N=140, randomWeight(), adj=emptyGraph(N), addRandomEdges(N, 1));
    }
  }

  void TestGroup9() {
    Subtasks({6});
    CASE(N=140, P=true, randomWeight(), adj=emptyGraph(N));
    CASE(N=140, P=true, randomWeight(), adj=emptyGraph(N), lineGraph(N, false));
    CASE(N=140, P=true, randomWeight(), adj=emptyGraph(N), lineGraph(N, true));
    CASE(N=140, P=true, randomWeight(), adj=emptyGraph(N), lineGraph(N, true), addRandomEdges(N, 5));
    CASE(N=140, P=true, randomWeight(), adj=emptyGraph(N), lineGraph(N, true), addRandomEdges(N, N/2));
    CASE(N=140, P=true, randomWeight(), adj=emptyGraph(N), directedStar(N));
    CASE(N=140, P=true, randomWeight(), adj=emptyGraph(N), directedStar(N), addRandomEdges(N, 5));
    CASE(N=140, P=true, randomWeight(), adj=emptyGraph(N), directedStar(N), addRandomEdges(N, N/2));
    CASE(N=140, P=true, randomWeight(), adj=emptyGraph(N), directedForest(N));
    CASE(N=140, P=true, randomWeight(), adj=emptyGraph(N), directedForest(N), addRandomEdges(N, 5));
    CASE(N=140, P=true, randomWeight(), adj=emptyGraph(N), directedForest(N), addRandomEdges(N, N/2));
    CASE(N=140, P=true, randomWeight(), adj=emptyGraph(N), spanningTree(N));
    CASE(N=140, P=true, randomWeight(), adj=emptyGraph(N), spanningTree(N), addRandomEdges(N, 5));
    CASE(N=140, P=true, randomWeight(), adj=emptyGraph(N), spanningTree(N), addRandomEdges(N, N/2));
    CASE(N=140, P=true, randomWeight(), adj=emptyGraph(N), twoCompletes(N));
    CASE(N=140, P=true, randomWeight(), adj=emptyGraph(N), twoCompletes(N), addRandomEdges(N, 1));
    CASE(N=140, P=true, randomWeight(), adj=emptyGraph(N), addRandomEdges(N, 1));
    CASE(N=140, P=true, randomWeight(), adj=emptyGraph(N), addRandomEdges(N, 10));
    CASE(N=140, P=true, randomWeight(), adj=emptyGraph(N), addRandomEdges(N, N/2));
    CASE(N=140, P=true, randomWeight(), adj=emptyGraph(N), addRandomEdges(N, 2*N));
    CASE(N=140, P=true, randomWeight(), adj=emptyGraph(N), addRandomEdges(N, 12*N));
    CASE(N=140, P=true, randomWeight(), adj=emptyGraph(N), addRandomEdges(N, N*(N-1)/4));
    CASE(N=140, P=true, randomWeight(), adj=emptyGraph(N), addRandomEdges(N, N*(N-1)/2-1));
    CASE(N=140, P=true, randomWeight(), adj=emptyGraph(N), addRandomEdges(N, N*(N-1)/2));
  }

 private:
  void randomWeight() {
    A = rnd.nextInt(1, 1000);
    B = rnd.nextInt(1, 999);
    if (A <= B) {
      B++;
    }
    else {
      swap(A, B);
    }
  }

  vector< vector<bool> > emptyGraph(int n) {
    vector< vector<bool> > ret(n, vector<bool>(n, false)); 
    return ret;
  }

  void lineGraph(int n,bool r) {
    vector <int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    if (r) {
      rnd.shuffle(perm.begin(), perm.end());
    }
    for (int i=1; i<n; i++) {
      adj[perm[i-1]][perm[i]] = true;
    }
  }

  void directedStar(int n) {
    for (int i=0; i<n-1; i++) {
      adj[i][n-1] = true;
    }
  }

  void directedForest(int n) {
    for (int i=0; i<n; i++) {
      int j = rnd.nextInt(i, n-1);
      adj[i][j] = true;
    }
  }

  void spanningTree(int n) {
    vector <int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    rnd.shuffle(perm.begin(), perm.end());
    for (int i=1; i<n; i++) {
      adj[perm[i]][perm[rnd.nextInt(i)]] = true;
    }
  }

  void twoCompletes(int n) {
    vector <int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    rnd.shuffle(perm.begin(), perm.end());
    int mid = n/2;
    for (int i=0; i<mid; i++) {
      for (int j=0; j<i; j++) {
        adj[perm[i]][perm[j]] = true;
      }
    }
    for (int i=mid; i<n; i++) {
      for (int j=mid; j<i; j++) {
        adj[perm[i]][perm[j]] = true;
      }
    }
  }

  void addRandomEdges(int n,int c) {
    vector< pair<int,int> > cand;
    for (int i=0; i<n; i++) {
      for (int j=0; j<i; j++) {
        if (!adj[i][j] && !adj[j][i]) {
          cand.push_back({i,j});
        }
      }
    }
    rnd.shuffle(cand.begin(), cand.end());
    for (int i=0; i<c; i++) {
      adj[cand[i].first][cand[i].second] = true;
    }
  }
};

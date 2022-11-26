#include <bits/stdc++.h>
using namespace std;

const int MAXN = 145, INF = 1e6;

int N, ans;
bool adj[MAXN][MAXN];
vector <int> U, V;

int ask(int u,int v) {
  cout<<"?";
  for (int i=1; i<=N; i++) {
    if (i == u) {
      cout<<" 1";
    }
    else if (i == v) {
      cout<<" 2";
    }
    else {
      cout<<" 0";
    }
  }
  cout<<endl;
  
  int res;
  cin>>res;
  return res;
}

bool dfs(int par,int now,int tar) {
  if (now == tar) {
    return true;
  }
  
  for (int i=1; i<=N; i++) {
    if (i == par || !adj[now][i]) {
      continue;
    }
    
    if (dfs(now, i, tar)) {
      return true;
    }
  }
  
  return false;
}

void solve(int u,int v,int n) {
  if (v > N) {
    if (n == 1) {
      int sum = 0;
      for (int i=2; i<=N; i++) {
        for (int j=1; j<i; j++) {
          if (adj[i][j]) {
            sum += ask(i, j);
          }
        }
      }
      
      if (sum < ans) {
        ans = sum;
        U.clear();
        V.clear();
        for (int i=2; i<=N; i++) {
          for (int j=1; j<i; j++) {
            if (adj[i][j]) {
              U.push_back(i);
              V.push_back(j);
            }
          }
        }
      }
    }
    return;
  }
  
  if (u+1 == v) {
    solve(1, v+1, n);
  }
  else {
    solve(u+1, v, n);
  }
  
  if (dfs(0, u, v)) {
    return;
  }
  
  adj[u][v] = adj[v][u] = true;
  
  if (u+1 == v) {
    solve(1, v+1, n-1);
  }
  else {
    solve(u+1, v, n-1);
  }
  
  adj[u][v] = adj[v][u] = false;
}

int main () {
  cin>>N;
  ans = INF;
  solve(1, 2, N);
  
  cout<<"! "<<N-1<<endl;
  for (int i=0; i<N-1; i++) {
    cout<<U[i]<<" "<<V[i]<<endl;
  }
}

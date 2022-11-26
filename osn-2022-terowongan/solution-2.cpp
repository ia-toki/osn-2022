#include <bits/stdc++.h>
using namespace std;

const int MAXN = 145;

int N, A, B;
int adj[MAXN][MAXN];
bool vis[MAXN];
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

void dfs(int now) {
  vis[now] = true;
  
  for (int i=1; i<=N; i++) {
    if (!vis[i] && adj[now][i] == A) {
      U.push_back(now);
      V.push_back(i);
      dfs(i);
    }
  }
}

int main () {
  cin>>N;
  A = B = adj[1][2] = adj[2][1] = ask(1, 2);
  for (int i=3; i<=N; i++) {
    for (int j=1; j<i; j++) {
      adj[i][j] = adj[j][i] = ask(i, j);
      A = min(A, adj[i][j]);
      B = max(B, adj[i][j]);
    }
  }
  
  dfs(1);
  for (int i=2; i<=N; i++) {
    if (!vis[i]) {
      U.push_back(1);
      V.push_back(i);
      dfs(i);
    }
  }
  
  cout<<"! "<<N-1<<endl;
  for (int i=0; i<N-1; i++) {
    cout<<U[i]<<" "<<V[i]<<endl;
  }
}

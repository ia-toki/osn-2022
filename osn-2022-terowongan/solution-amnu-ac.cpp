#include <bits/stdc++.h>
using namespace std;

const int MAXN = 145, LOG = 8;

int N, C, A, B;
bool vis[MAXN];
queue <int> Q;
vector <int> U, V;

void visit(int u,int v) {
  U.push_back(u);
  V.push_back(v);
  vis[v] = true;
  Q.push(v);
  C--;
}

void pre() {
  cout<<"? 1 2";
  for (int i=3; i<=N; i++) {
    cout<<" 0";
  }
  cout<<endl;
  cin>>A;
  B = A;
}

int ada(int now,int L,int R) {
  int cnt = 0;
  
  cout<<"?";
  for (int i=1; i<=N; i++) {
    if (i == now) {
      cout<<" 1";
      continue;
    }
    if (vis[i]) {
      cout<<" 0";
      continue;
    }
    cnt++;
    if (cnt >= L && cnt <= R) {
      cout<<" 2";
    }
    else {
      cout<<" 0";
    }
  }
  cout<<endl;
  
  int res;
  cin>>res;
  
  if (A == B) {
    if (res > B*(R-L+1)) {
      for (int i=1; i<=N; i++) {
        if (vis[i]) {
          continue;
        }
        
        cout<<"?";
        for (int j=1; j<=N; j++) {
          if (j == now) {
            cout<<" 1";
          }
          else if (j == i) {
            cout<<" 2";
          }
          else {
            cout<<" 0";
          }
        }
        cout<<endl;
        
        cin>>B;
        if (A != B) {
          return ada(now,1,C);
        }
        visit(now, i);
      }
      
      assert(false);
    }
    
    if (res < B*(R-L+1)) {
      A = 0;
    }
  }
  
  if (res == B*(R-L+1)) {
    return 0;
  }
  
  if (A <= 0) {
    if (L == R) {
      if (res != B) {
        A = res;
      }
      else if (A < 0) {
        A = -A-B;
      }
    }
    
    if (L+1 == R) {
      A = -res;
    }
    
    return N+1;
  }
  
  return (B*(R-L+1) - res)/(B - A);
}

int binser(int now) {
  int L = 1;
  int R = C;
  
  while (L < R) {
    int mid = (L+R)/2;
    if (ada(now,L,mid)) {
      R = mid;
    }
    else {
      L = mid+1;
    }
  }
  
  int cnt = 0;
  for (int i=1; i<=N; i++) {
    if (vis[i]) {
      continue;
    }
    cnt++;
    if (cnt == L) {
      return i;
    }
  }
  
  assert(false);
}

void bfs() {
  while (!Q.empty()) {
    int now = Q.front();
    Q.pop();
    int rest = ada(now,1,C);
    while (rest--) {
      int next = binser(now);
      visit(now, next);
      if (rest == N) {
        rest = ada(now,1,C);
      }
    }
  }
}

int main () {
  cin>>N;
  C = N;
  pre();
  
  for (int i=1; i<=N; i++) {
    if (!vis[i]) {
      visit(1,i);
      bfs();
    }
  }
  
  cout<<"! "<<N-1<<endl;
  for (int i=1; i<N; i++) {
    cout<<U[i]<<" "<<V[i]<<endl;
  }
}

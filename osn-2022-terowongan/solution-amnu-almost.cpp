#include <bits/stdc++.h>
using namespace std;

const int MAXN = 145, LOG = 8;

int N, C, A, B;
bool sp;
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

bool ada(int now,int L,int R) {
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
      if (sp) {
        for (int i=1; i<=N; i++) {
          if (!vis[i]) {
            visit(1, i);
          }
        }
        return false;
      }
      
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
      A--;
    }
    else {
      sp = true;
    }
  }
  
  return res < B*(R-L+1);
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
    while (ada(now,1,C)) {
      int next = binser(now);
      visit(now, next);
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

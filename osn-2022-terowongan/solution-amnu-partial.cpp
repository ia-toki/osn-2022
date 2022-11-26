#include <bits/stdc++.h>
using namespace std;

const int MAXN = 145, LOG = 8;

int N, C, A, B;
int part[MAXN];
bool vis[MAXN];
vector <int> U, V;

void pre() {
  cout<<"? 1 2";
  for (int i=3; i<=N; i++) {
    cout<<" 0";
  }
  cout<<endl;
  cin>>A;
  
  int X, Y, Z;
  for (int i=0; i<LOG; i++) {
    X = 0;
    Y = 0;
    cout<<"?";
    for (int j=1; j<=N; j++) {
      if ((j>>i)&1) {
        X++;
        part[j] = 1;
        cout<<" 1";
      }
      else {
        Y++;
        part[j] = 2;
        cout<<" 2";
      }
    }
    cout<<endl;
    
    cin>>Z;
    if (Z != A*X*Y) {
      break;
    }
  }
  
  if (Z == A*X*Y) {
    B = A;
    return;
  }
  
  while (X > 1) {
    int mid = X/2;
    cout<<"?";
    for (int i=1; i<=N; i++) {
      if (part[i] == 1 && mid > 0) {
        mid--;
        cout<<" 0";
      }
      else {
        cout<<" "<<part[i];
      }
    }
    cout<<endl;
    
    mid = X/2;
    cin>>Z;
    if (Z == A*(X-mid)*Y) {
      for (int i=1; i<=N; i++) {
        if (part[i] == 1) {
          if (mid > 0) {
            mid--;
          }
          else {
            part[i] = 0;
          }
        }
      }
      X = X/2;
    }
    else {
      for (int i=1; i<=N; i++) {
        if (part[i] == 1) {
          if (mid > 0) {
            mid--;
            part[i] = 0;
          }
        }
      }
      X -= X/2;
    }
  }
  
  while (Y > 1) {
    int mid = Y/2;
    cout<<"?";
    for (int i=1; i<=N; i++) {
      if (part[i] == 2 && mid > 0) {
        mid--;
        cout<<" 0";
      }
      else {
        cout<<" "<<part[i];
      }
    }
    cout<<endl;
    
    mid = Y/2;
    cin>>Z;
    if (Z == A*X*(Y-mid)) {
      for (int i=1; i<=N; i++) {
        if (part[i] == 2) {
          if (mid > 0) {
            mid--;
          }
          else {
            part[i] = 0;
          }
        }
      }
      Y = Y/2;
    }
    else {
      for (int i=1; i<=N; i++) {
        if (part[i] == 2) {
          if (mid > 0) {
            mid--;
            part[i] = 0;
          }
        }
      }
      Y -= Y/2;
    }
  }
  
  cout<<"?";
  for (int i=1; i<=N; i++) {
    cout<<" "<<part[i];
  }
  cout<<endl;
  cin>>B;
  
  if (A > B) {
    swap(A, B);
  }
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

void dfs(int now) {
  vis[now] = true;
  C--;
  
  while (ada(now,1,C)) {
    int next = binser(now);
    U.push_back(now);
    V.push_back(next);
    dfs(next);
  }
}

int main () {
  cin>>N;
  C = N;
  pre();
  
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

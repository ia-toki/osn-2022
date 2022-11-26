#include <bits/stdc++.h>
using namespace std;

const int MAXN = 145;

int N, C, A, B;
bool vis[MAXN];
vector <int> U, V;

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
  A = 1;
  B = 2;
  
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

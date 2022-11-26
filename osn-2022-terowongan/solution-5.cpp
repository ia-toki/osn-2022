#include <bits/stdc++.h>
using namespace std;

const int MAXN = 145, INF = 1e6;

int N, U, X, ans;

int main () {
  cin>>N;
  ans = INF;
  
  for (int i=1; i<=N; i++) {
    cout<<"?";
    for (int j=1; j<=N; j++) {
      if (i == j) {
        cout<<" 1";
      }
      else {
        cout<<" 2";
      }
    }
    cout<<endl;
    
    cin>>X;
    if (X < ans) {
      ans = X;
      U = i;
    }
  }
  
  cout<<"! "<<N-1<<endl;
  for (int i=1; i<=N; i++) {
    if (i != U) {
      cout<<U<<" "<<i<<endl;
    }
  }
}

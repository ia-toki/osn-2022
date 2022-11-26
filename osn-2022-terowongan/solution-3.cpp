#include <bits/stdc++.h>
using namespace std;

const int MAXN = 145;

int N, A, B;
vector <int> U, V;

bool ada(int now,int L,int R) {
  cout<<"?";
  for (int i=1; i<=N; i++) {
    if (i == now) {
      cout<<" 1";
    }
    else if (i >= L && i <= R) {
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
  int L = now+1;
  int R = N;
  
  while (L < R) {
    int mid = (L+R)/2;
    if (ada(now,L,mid)) {
      R = mid;
    }
    else {
      L = mid+1;
    }
  }
  
  return L;
}

int main () {
  cin>>N;
  A = 1;
  B = 2;
  
  for (int i=1; i<N; i++) {
    U.push_back(i);
    if (!ada(i,i+1,N)) {
      V.push_back(N);
    }
    else {
      V.push_back(binser(i));
    }
  }
  
  cout<<"! "<<N-1<<endl;
  for (int i=0; i<N-1; i++) {
    cout<<U[i]<<" "<<V[i]<<endl;
  }
}

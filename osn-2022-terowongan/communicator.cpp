#include <bits/stdc++.h>
using namespace std;

void ac() {
  cerr << "AC\n";
  exit(0);
}

void wa() {
  cerr << "WA\n";
  exit(0);
}

void ok(double pts) {
  cerr << "OK\n";
  cerr << fixed << setprecision(0) << pts;
  exit(0);
}

void eof() {
  string s;
  if (cin >> s) {
    wa();
  }
}

string read() {
  string s;
  if (!(cin >> s)) {
    wa();
  }
  return s;
}

int readInt() {
  string s = read();
  if (s.length() > 4) {
    wa();
  }
  if (s == "0") {
    return 0;
  }
  if (s[0] == '0') {
    wa();
  }
  int t = 0;
  for (char c:s) {
    if (c < '0' || c > '9') wa();
    t = t * 10 + c - '0';
  }
  return t;
}

const int MAXN = 145, MAXQ = 2000;

int N, A, B;
int Q, C;
int par[MAXN];

bool P;
bool vis[MAXN];
bool adj[MAXN][MAXN];

int find(int now) {
  if (par[now] == now) {
    return now;
  }
  return par[now] = find(par[now]);
}

void dfs(int now) {
  vis[now] = true;
  for (int i = 1; i <= N; i++) {
    if (adj[now][i] && !vis[i]) {
      dfs(i);
    }
  }
}

void init() {
  for (int i = 1; i <= N; i++) {
    par[i] = i;
    if (!vis[i]) {
      C++;
      dfs(i);
    }
  }
}

void ask() {
  if (++Q > MAXQ) {
    wa();
  }
  
  vector <int> S, T;
  for (int i = 1; i <= N; i++) {
    int W = readInt();
    if (W < 0 || W > 2) {
      wa();
    }
    if (W == 1) {
      S.push_back(i);
    }
    if (W == 2) {
      T.push_back(i);
    }
  }
  
  int cnt[2] = {0,0};
  for (int i : S) {
    for (int j : T) {
      cnt[adj[i][j]]++;
    }
  }
  
  cout << A*cnt[1] + B*cnt[0] << endl;
}

void answer() {
  int M = readInt();
  if (M != N-1) {
    wa();
  }
  
  int cnt = 0;
  for (int i = 1; i < N; i++) {
    int U = readInt(), V = readInt();
    if (U < 1 || U > N || V < 1 || V > N || U == V) {
      wa();
    }
    if (find(U) == find(V)) {
      wa();
    }
    par[find(U)] = find(V);
    if (!adj[U][V]) {
      cnt++;
    }
  }
  
  if (cnt != C-1) {
    wa();
  }
  eof();
  if (P && Q > 1000) {
    if (Q > 1170) {
      ok(floor(5 + 2000.0 / (Q - 1000)));
    }
    else {
      ok(floor(36 - pow(2, (Q - 1000) / 40.0)));
    }
  }
  else {
    ac();
  }
}

int main(int argc, char* argv[]) {
  ifstream tc_in(argv[1]);
  tc_in >> N >> A >> B >> P;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      tc_in >> adj[i][j];
    }
  }
  
  init();
  cout << N << endl;
  
  while (true) {
    string S = read();
    
    if (S == "?") {
      ask();
    }
    else if (S == "!") {
      answer();
    }
    else {
      wa();
    }
  }
}

#include <bits/stdc++.h>
using namespace std;

class UFDS
{
public:
  UFDS(int n) : _parent(n)
  {
    for (int i = 0; i < n; i++)
      _parent[i] = i;
  }

  ~UFDS() = default;

  int find(int p)
  {
    if (_parent[p] != p)
    {
      _parent[p] = find(_parent[p]);
      return _parent[p];
    }
    else
      return p;
  }

  void connect(int p, int q)
  {
    int pp = find(p);
    int qq = find(q);
    if (pp == qq)
      return;
    _parent[pp] = qq;
  }

  bool same(int p, int q)
  {
    return find(p) == find(q);
  }

private:
  vector<int> _parent;
  bool valid_index(int i) { return 0 <= i && i < _parent.size(); }
};

int numberOfComponents(int n, const vector<int> &u, const vector<int> &v)
{
  UFDS g(n);
  for (int i = 0; i < u.size(); i++)
    g.connect(u[i] - 1, v[i] - 1);

  std::vector<int> parent(n);
  for (int i = 0; i < n; i++)
    parent[i] = g.find(i);

  sort(parent.begin(), parent.end());
  auto it = unique(parent.begin(), parent.end());
  return distance(parent.begin(), it);
}

using ULL = unsigned long long;

int wa()
{
  cout << "WA" << endl;
  return 0;
}

int ac()
{
  cout << "AC" << endl;
  return 0;
}

bool readInt(const string &s, int &x)
{
  if (s.size() > 8)
    return false;

  if (s[0] == '0' && s.size() > 1)
    return false;

  x = 0;
  for (char c : s)
  {
    if (c < '0' || c > '9')
      return false;
    x = x * 10 + c - '0';
  }
  return true;
}

int main(int argc, char *argv[])
{
  ifstream tc_in(argv[1]);
  ifstream tc_out(argv[2]);
  ifstream con_out(argv[3]);

  string tc_ans;
  tc_out >> tc_ans;

  string con_ans;
  if (!(con_out >> con_ans))
  {
    return wa();
  }

  if (tc_ans != con_ans)
  {
    return wa();
  }
  else
  {
    int N, M, Q;
    tc_in >> N >> M >> Q;

    vector<int> H(N);
    for (int i = 0; i < N; i++)
      tc_in >> H[i];

    if (Q == 0 || tc_ans == "-1")
      return ac();
    else
    {
      ULL ans = strtoull(tc_ans.c_str(), NULL, 10);

      vector<int> U(M), V(M);
      for (int j = 0; j < M; j++)
        tc_in >> U[j] >> V[j];

      int C = numberOfComponents(N, U, V);

      int B;
      string sB;
      if (!(con_out >> sB))
        return wa();

      if (!readInt(sB, B))
        return wa();

      if (B != C - 1)
        return wa();

      set<int> kotaJembatan;
      ULL cons_total = 0;
      for (int i = 0; i < B; i++)
      {
        int p, q;
        string sp, sq;
        if (!(con_out >> sp >> sq))
          return wa();

        if (!readInt(sp, p))
          return wa();

        if (!readInt(sq, q))
          return wa();

        if (p < 1 || p > N)
          return wa();

        if (q < 1 || q > N)
          return wa();

        if (kotaJembatan.find(p) != kotaJembatan.end())
          return wa();

        if (kotaJembatan.find(q) != kotaJembatan.end())
          return wa();

        U.push_back(p);
        V.push_back(q);
        cons_total += H[p - 1] + H[q - 1];

        kotaJembatan.insert(p);
        kotaJembatan.insert(q);
      }

      if (numberOfComponents(N, U, V) == 1 && cons_total == ans)
        return ac();
      else
        return wa();
    }
  }
}
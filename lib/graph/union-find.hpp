#include <vector>
using namespace std;

struct UnionFind {
  private:
  vector<int> par, siz;
  int N, cnt;

  public:
  UnionFind(int n=0) { init(n); }

  void init(int n) {
    N = n;
    cnt = n;
    par = vector<int>(N, -1);
    siz = vector<int>(N, 1);
  }

  int leader(int v) {
    if (par[v] == -1) return v;
    return par[v] = leader(par[v]);
  }

  bool merge(int u, int v) {
    u = leader(u);
    v = leader(v);
    if (u == v) return false;
    if (siz[u] > siz[v]) swap(u,v);
    par[u] = v;
    siz[v] += siz[u];
    cnt--;
    return true;
  }

  bool same(int u, int v) { return leader(u) == leader(v); }

  int size(int v) { return siz[leader(v)]; }

  int count() { return cnt; }

  vector<vector<int>> groups() {
    vector<vector<int>> res(cnt);
    vector<int> idx(N,-1);
    int now = 0;
    for (int i = 0; i < N; i++) {
      int v = leader(i);
      if (idx[v] == -1) {
        idx[v] = now++;
      }
      res[idx[v]].push_back(i);
    }
    return res;
  }
};
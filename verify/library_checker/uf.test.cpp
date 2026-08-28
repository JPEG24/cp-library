// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/unionfind
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;

#include "lib/util.hpp"
#include "lib/unionfind.hpp"

void solve() {
  int N, Q;
  cin >> N >> Q;
  UnionFind uf(N);
  rep(i,0,Q) {
    int t, u, v;
    cin >> t >> u >> v;
    if (t == 0) {
      uf.merge(u,v);
    } else {
      if (uf.same(u,v)) {
        cout << 1 << '\n';
      } else {
        cout << 0 << '\n';
      }
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int t = 1;
  // cin >> t;
  for (int ti = 0; ti < t; ti++) solve();

  return 0;
}
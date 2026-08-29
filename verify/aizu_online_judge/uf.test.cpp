// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/DSL_1_A
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;

#include "util.hpp"
#include "graph/union-find.hpp"

void solve() {
  int n, q;
  cin >> n >> q;
  UnionFind uf(n);
  rep(i,0,q) {
    int com, x, y;
    cin >> com >> x >> y;
    if (com == 0) {
      uf.merge(x,y);
    } else {
      if (uf.same(x,y)) {
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
// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_1_A
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;

#include "lib/util.hpp"
#include "lib/unionfind.hpp"

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
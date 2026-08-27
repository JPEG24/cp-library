// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;

#include "util.hpp"
#include "segtree.hpp"

int op(int a, int b) { return min(a,b); }
int e() { return INT_MAX; }

void solve() {
  int n, q;
  cin >> n >> q;
  segtree<int, op, e> seg(n);
  rep(i,0,q) {
    int com, x, y;
    cin >> com >> x >> y;
    if (com == 0) {
      seg.set(x,y);
    } else {
      int ans = seg.prod(x,y+1);
      cout << ans << '\n';
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
// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_B
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;

#include "util.hpp"
#include "struct/fenwicktree.hpp"

void solve() {
  int n, q;
  cin >> n >> q;
  fenwick_tree<int> fw(n);
  rep(i,0,q) {
    int com, x, y;
    cin >> com >> x >> y;
    if (com == 0) {
      x--;
      fw.add(x,y);
    } else {
      x--; y--;
      int ans = fw.sum(x,y+1);
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
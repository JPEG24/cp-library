// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/point_add_range_sum
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;

#include "lib/util.hpp"
#include "lib/fenwicktree.hpp"

void solve() {
  int N, Q;
  cin >> N >> Q;
  vector<ll> a(N);
  rep(i,0,N) cin >> a[i];
  FenwickTree<ll> fw(N);
  rep(i,0,N) fw.add(i,a[i]);
  rep(i,0,Q) {
    int type;
    cin >> type;
    if (type == 0) {
      int p, x;
      cin >> p >> x;
      fw.add(p,x);
    } else {
      int l, r;
      cin >> l >> r;
      ll ans = fw.sum(l,r);
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
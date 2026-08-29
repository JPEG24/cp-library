// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/staticrmq
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;

#include "lib/util.hpp"
#include "lib/struct/sparse_table.hpp"

int op(int a, int b) { return min(a, b); }

void solve() {
  int N, Q;
  cin >> N >> Q;
  vector<int> a(N);
  rep(i,0,N) cin >> a[i];
  SparseTable<int,op> st(a);
  rep(i,0,Q) {
    int l, r;
    cin >> l >> r;
    int ans = st.prod(l,r);
    cout << ans << '\n';
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
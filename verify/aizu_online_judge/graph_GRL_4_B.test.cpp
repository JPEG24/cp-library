// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_B
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;

#include "lib/util.hpp"
#include "lib/graph.hpp"

void solve() {
  int n, m;
  cin >> n >> m;
  Graph g(n);
  rep(i,0,m) {
    int s, t;
    cin >> s >> t;
    g.add(s,t);
  }

  auto ans = topological_sort(g);
  rep(i,0,n) cout << ans[i] << endl;
}

int main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int t = 1;
  // cin >> t;
  for (int ti = 0; ti < t; ti++) solve();

  return 0;
}
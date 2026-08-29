// competitive-verfier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_2_A
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
    ll w;
    cin >> s >> t >> w;
    g.add_undirected(s,t,w);
  }

  auto [ans,_] = min_kruskal(g);
  cout << ans << endl;
}

int main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int t = 1;
  // cin >> t;
  for (int ti = 0; ti < t; ti++) solve();

  return 0;
}
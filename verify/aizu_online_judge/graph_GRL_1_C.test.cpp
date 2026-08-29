// competitive-verfier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_C
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
    ll d;
    cin >> s >> t >> d;
    g.add(s,t,d);
  }

  if (has_negative_cycle(g)) {
    cout << "NEGATIVE CYCLE" << endl;
    return;
  }

  auto dist = Warshall_Floyd(g);
  rep(i,0,n) rep(j,0,n) {
    if (dist[i][j] == g.INF) cout << "INF";
    else cout << dist[i][j];
    
    if (j != n-1) cout << ' ';
    else cout << endl;
  }
}

int main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int t = 1;
  // cin >> t;
  for (int ti = 0; ti < t; ti++) solve();

  return 0;
}
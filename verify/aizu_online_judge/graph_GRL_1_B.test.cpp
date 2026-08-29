// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_B
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;

#include "lib/util.hpp"
#include "lib/graph.hpp"

void solve() {
  int n, m, r;
  cin >> n >> m >> r;
  Graph g(n);
  rep(i,0,m) {
    int s, t;
    ll d;
    cin >> s >> t >> d;
    g.add(s,t,d);
  }

  auto [ok,dist] = Bellman_Ford(g,r);
  if (!ok) {
    cout << "NEGATIVE CYCLE" << endl;
  } else {
    rep(i,0,n) {
      if (dist[i] == g.INF) cout << "INF" << endl;
      else cout << dist[i] << endl;
    }
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
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/minimum_spanning_tree
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;

#include "../../lib/util.hpp"
#include "../../lib/graph/kruskal.hpp"

void solve() {
  int N, M;
  cin >> N >> M;
  Graph G(N);
  rep(i,0,M) {
    int a, b;
    ll c;
    cin >> a >> b >> c;
    G.add_undirected(a,b,c);
  }

  auto [x,e] = min_kruskal(G);
  cout << x << endl;
  rep(i,0,sz(e)) {
    cout << e[i];
    if (i < sz(e)-1) cout << ' ';
    else cout << '\n';
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
// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/CGL_1_C
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;

#include "../../lib/util.hpp"
#include "../../lib/geom/vector_int.hpp"

void solve() {
  V p0, p1;
  cin >> p0 >> p1;
  int q;
  cin >> q;
  rep(i,0,q) {
    V p2;
    cin >> p2;

    V a = p1-p0, b = p2-p0;
    ll c = a.cross(b);
    if (c > 0) {
      cout << "COUNTER_CLOCKWISE\n";
    } else if (c < 0) {
      cout << "CLOCKWISE\n";
    } else {
      if (a.dot(b) < 0) {
        cout << "ONLINE_BACK\n";
      } else if (a.norm2() < b.norm2()) {
        cout << "ONLINE_FRONT\n";
      } else {
        cout << "ON_SEGMENT\n";
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
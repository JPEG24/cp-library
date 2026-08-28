// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/CGL_2_A
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;

#include "lib/util.hpp"
#include "vector_int.hpp"

void solve() {
  V p0, p1, p2, p3;
  cin >> p0 >> p1 >> p2 >> p3;
  V s1 = p1-p0, s2 = p3-p2;
  if (s1.cross(s2) == 0) {
    cout << "2\n";
  } else if (s1.dot(s2) == 0) {
    cout << "1\n";
  } else {
    cout << "0\n";
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int q = 1;
  cin >> q;
  for (int i = 0; i < q; i++) solve();

  return 0;
}
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;

#include "lib/util.hpp"
#include "comb.hpp"
using mint = modint;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int t, m;
  cin >> t >> m;
  mint::set_mod(m);
  Combination<mint> comb;
  for (int ti = 0; ti < t; ti++) {
    int n, k;
    cin >> n >> k;
    mint ans = comb(n,k);
    cout << ans.val() << '\n';
  }

  return 0;
}
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;
#define rep(i,n) for (int i = 0; i < (n); i++)
using ll = long long;

int randint(int l, int r) {
  static mt19937 rng(random_device{}());
  uniform_int_distribution<int> dist(l, r);
  return dist(rng);
}

long double randdouble(long double l=0, long double r=1) {
  static mt19937 rng(random_device{}());
  uniform_real_distribution<long double> dist(l, r);
  return dist(rng);
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);


  return 0;
}
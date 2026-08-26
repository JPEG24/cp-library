#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;

#include "lib/util.hpp"

int randint(int l, int r) {
  static mt19937 mt(random_device{}());
  uniform_int_distribution<int> dist(l, r);
  return dist(mt);
}

long double randdouble(long double l, long double r) {
  static mt19937 mt(random_device{}());
  uniform_real_distribution<long double> dist(l, r);
  return dist(mt);
}

void gen() {
  
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int t = 1;
  // t = randint(1,r);
  for (int ti = 0; ti < t; ti++) gen();

  return 0;
}

// inter/judge.cpp
// rtest/gen.cpp
#include <vector>
#include <utility>
using namespace std;

struct Sieve {
  int n;
  vector<int> f, primes;
  Sieve(int n=1):n(n), f(n+1) {
    f[0] = f[1] = -1;
    for (long long i = 2; i <= n; ++i) {
      if (f[i]) continue;
      primes.push_back(i);
      f[i] = i;
      for (long long j = i*i; j <= n; j += i) {
        if (!f[j]) f[j] = i;
      }
    }
  }
  bool isPrime(long long x) {
    if (x <= n) return f[x] == x;

    for (long long p : primes) {
      if (p * p > x) return true;
      if (x % p == 0) return false;
    }
    return true;
  }
  vector<int> factorList(long long x) {
    vector<int> res;
    while (x > n) {
      bool found = false;
      for (int p : primes) {
        if (1ll * p * p > x) break;
        if (x % p == 0) {
          res.push_back(p);
          x /= p;
          found = true;
          break;
        }
      }
      if (!found) {
        res.push_back(x);
        return res;
      }
    }
    while (x != 1) {
      res.push_back(f[x]);
      x /= f[x];
    }
    return res;
  }
  vector<pair<int,int>> factor(int x) {
    vector<int> fl = factorList(x);
    if (fl.size() == 0) return {};
    vector<pair<int,int>> res(1, pair<int,int>(fl[0], 0));
    for (int p : fl) {
      if (res.back().first == p) {
        res.back().second++;
      } else {
        res.emplace_back(p, 1);
      }
    }
    return res;
  }
  vector<pair<long long,int>> factor(long long x) {
    vector<pair<long long,int>> res;
    for (int p : primes) {
      int y = 0;
      while (x%p == 0) x /= p, ++y;
      if (y != 0) res.emplace_back(p,y);
    }
    if (x != 1) res.emplace_back(x,1);
    return res;
  }
};
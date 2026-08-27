#include <vector>
#include <utility>
using namespace std;
using ll = long long;

struct Sieve {
  int n;
  vector<int> f, primes;
  Sieve(int n=1): n(n), f(n+1) {
    f[0] = f[1] = -1;
    for (ll i = 2; i <= n; ++i) {
      if (f[i]) continue;
      primes.push_back(i);
      f[i] = i;
      for (ll j = i*i; j <= n; j += i) {
        if (!f[j]) f[j] = i;
      }
    }
  }
  bool isPrime(ll x) {
    if (x <= n) return f[x] == x;

    for (ll p : primes) {
      if (p * p > x) return true;
      if (x % p == 0) return false;
    }
    return true;
  }
  vector<ll> factorList(ll x) {
    vector<ll> res;
    while (x > n) {
      bool found = false;
      for (ll p : primes) {
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
    vector<ll> fl = factorList(x);
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
  vector<pair<ll,int>> factor(ll x) {
    vector<pair<ll,int>> res;
    for (int p : primes) {
      int y = 0;
      while (x%p == 0) x /= p, ++y;
      if (y != 0) res.emplace_back(p,y);
    }
    if (x != 1) res.emplace_back(x,1);
    return res;
  }
};
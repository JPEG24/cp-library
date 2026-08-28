#include <vector>
using namespace std;
#include <atcoder/modint>
using namespace atcoder;

template <class mint>
struct Combination {
  private:
  int n;
  vector<mint> inv, fact, ifact;

  void expand(int m) {
    if (m <= n) return;

    inv.resize(m + 1);
    fact.resize(m + 1);
    ifact.resize(m + 1);

    for (int i = n + 1; i <= m; i++) {
      inv[i] = -inv[mint::mod() % i] * (mint::mod() / i);
      fact[i] = fact[i - 1] * i;
      ifact[i] = ifact[i - 1] * inv[i];
    }

    n = m;
  }

  public:
  Combination(): n(1), inv({0, 1}), fact({1, 1}), ifact({1, 1}) {}

  mint comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    expand(n);
    return fact[n] * ifact[k] * ifact[n - k];
  }

  mint operator()(int n, int k) {
    return comb(n, k);
  }

  mint perm(int n, int k) {
    if (k < 0 || k > n) return 0;
    expand(n);
    return fact[n] * ifact[n - k];
  }

  mint homo(int n, int k) {
    expand(n + k - 1);
    return comb(n + k - 1, k);
  }
};
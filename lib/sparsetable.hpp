#include <vector>
#include <cassert>
using namespace std;

template<class S, S (*op)(S,S)>
struct SparseTable {
  private:
  int N, K;
  vector<int> log_table;
  vector<vector<S>> table;

  public:
  SparseTable() : N(0), K(0) {}
  SparseTable(const vector<S>& A) { init(A); }

  void init(const vector<S>& A) {
    N = A.size();
    K = 0;
    while (1 << (K + 1) <= N) ++K;

    table.resize(K + 1);
    table[0] = A;
    for (int k = 0; k < K; ++k) {
      int m = N - (1 << (k + 1)) + 1;
      table[k + 1].resize(m);
      for (int i = 0; i < m; ++i) {
        table[k + 1][i] = op(table[k][i], table[k][i + (1 << k)]);
      }
    }

    log_table.resize(N + 1);
    for (int k = 0; k <= K; ++k) {
      int s = 1 << k, t = min((1 << (k + 1)) - 1, N);
      for (int n = s; n <= t; ++n) {
        log_table[n] = k;
      }
    }
  }

  S prod(int l, int r) const {
    assert(0 <= l && l <= r && r <= N);
    int k = log_table[r - l];
    return op(table[k][l], table[k][r - (1 << k)]);
  }
};
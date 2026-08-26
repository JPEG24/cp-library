#include <vector>
using namespace std;

template<class S, S (*op)(S,S)>
struct SparseTable {
  private:
  int N, K;
  vector<int> log_table;
  vector<vector<S>> table;

  public:
  SparseTable(const vector<S>& A) {
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

  S prod(int L, int R) {
    int k = log_table[R - L];
    return op(table[k][L], table[k][R - (1 << k)]);
  }
};
#include <vector>
using namespace std;

template<class S, S (*op)(S,S)>
struct DisjointSparseTable {
	private:
  int N;
  vector<S> A;
  vector<vector<S>> table;
  vector<int> log_table;

	public:
  DisjointSparseTable(const vector<S>& A) : A(A) {
    N = A.size();
    int K = 0;
    while ((1 << K) < N) ++K;
    table.resize(K);

    for (int k = 0; k < K; ++k) {
      table[k] = A;
      int w = 1 << k;
      for (int a = 0; a + w < N; a += 2 * w) {
        int b = a + 2 * w, c = a + w;
        b = min(b, N);
        for (int i = (c-1)-1; i >= a; --i) table[k][i] = op(A[i], table[k][i + 1]);
        for (int i = c+1; i < b; ++i) table[k][i] = op(table[k][i - 1], A[i]);
      }
    }

    log_table.resize(1 << K);
    for (int k = 0; k < K; ++k) {
      for (int i = (1 << k); i < 1 << (k + 1); ++i) {
        log_table[i] = k;
      }
    }
	}

  S prod(int L, int R) {
    if (R == L + 1) return A[L];
    int k = log_table[L ^ (R - 1)];
    return op(table[k][L], table[k][R - 1]);
  }
};
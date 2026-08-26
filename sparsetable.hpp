#include <vector>
using namespace std;

template<class S, S (*op)(S, S)>
struct SparseTable {
  private:
  int n, lg;
  vector<vector<S>> st;
  vector<int> log_table;

  public:
  SparseTable(const vector<S>& v=vector<S>()) {
    build(v);
  }

  void build(const vector<S>& v) {
    n = (int)v.size();

    log_table.assign(n + 1, 0);
    for (int i = 2; i <= n; i++) {
      log_table[i] = log_table[i >> 1] + 1;
    }

    lg = log_table[n] + 1;
    st.assign(lg, vector<S>(n));

    st[0] = v;

    for (int k = 1; k < lg; k++) {
      for (int i = 0; i + (1 << k) <= n; i++) {
        st[k][i] = op(
          st[k - 1][i],
          st[k - 1][i + (1 << (k - 1))]
        );
      }
    }
  }

  S prod(int l, int r) const {
    int k = log_table[r - l];
    return op(
      st[k][l],
      st[k][r - (1 << k)]
    );
  }
};
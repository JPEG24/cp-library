#include <vector>
#include <cassert>
using namespace std;
int topbit(int x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }

template <typename S,  S (*op)(S,S)>
struct SqrtTree {
	private:
  S N;

  vector<S> A;
  vector<vector<S>> prefix, suffix;
  vector<vector<S>> between;

  vector<int> sz_log;     // log_2(node size)
  vector<int> bit_to_lv;  // topbit(xor(L,R)) -> lv

	public:
  SqrtTree(const vector<S>& A) : A(A) {
    N = A.size();

    // N <= 2^K
    int K = 0;
    while ((1 << K) < N) ++K;

    bit_to_lv.assign(K, -1);
    while (K > 1) {
      for (int i = K / 2; i < K; ++i) bit_to_lv[i] = sz_log.size();
      sz_log.emplace_back(K), K /= 2;
    }
    for (int lv = 0; lv < int(sz_log.size()); ++lv) build(lv);
  }

  void build(int lv) {
    int K1 = sz_log[lv], K2 = K1 / 2;
    int mask2 = (1 << K2) - 1;
    // prefix, suffix
    vector<S> pre = A, suf = A;
    for (int i = 0; i < N; ++i) if (i & mask2) pre[i] = op(pre[i - 1], A[i]);
    for (int i = N - 1; i >= 0; --i) if (i & mask2) suf[i - 1] = op(A[i - 1], suf[i]);
    prefix.emplace_back(pre), suffix.emplace_back(suf);

    int n = N >> K2;
    vector<S> blk_prod(n);
    for (int i = 0; i < n; ++i) blk_prod[i] = suf[i << K2];

    // between.
    // j について昇順, i について降順に格納.
    vector<S> B;
    for (int j = 0; j < n; ++j) {
      int s = j >> (K1 - K2) << (K1 - K2);
      B.emplace_back(blk_prod[j]);
      for (int i = j-1; i >= s; --i) { B.emplace_back(op(blk_prod[i], B.back())); }
    }
    between.emplace_back(B);
  }

  S prod(S L, S R) {
    --R;
    assert(L <= R);
    if (L == R) return A[L];
    int lv = bit_to_lv[topbit(L ^ R)];
    if (lv == -1) {
      assert(R == L + 1);
      return op(A[L], A[R]);
    }
    int K1 = sz_log[lv], K2 = K1 / 2;

    S ANS = suffix[lv][L];
    int a = 1 + (L >> K2), b = (R >> K2) - 1;
    int m = 1 << (K1 - K2);  // ひとつのノードにある子区間の個数
    if (a <= b) {
      int k = a >> (K1 - K2);
      a -= k * m, b -= k * m;
      int idx = k * (m * (m + 1) / 2);
      idx += (b + 1) * b / 2;
      idx += b - a;
      ANS = op(ANS, between[lv][idx]);
    }
    ANS = op(ANS, prefix[lv][R]);
    return ANS;
  }
};
#include <vector>
#include <cassert>
using namespace std;

template <class T>
class FenwickTree {
	private:
	int N;
	vector<T> bit;

	public:
	FenwickTree(int n=0) : N(n), bit(n + 1, 0) {}
	FenwickTree(const vector<T>& v) {
		N = v.size();
		bit = vector<T>(N + 1, 0);
		for (int i = 0; i < N; i++) add(i + 1, v[i]);
	}

	T sum(int i) const {
		assert(0 <= i && i <= N);
		T res = 0;
		while (i > 0) {
			res += bit[i];
			i -= -i & i;
		}
		return res;
	}

	T sum(int l, int r) const {
		assert(0 <= l && l <= r && r <= N);
		return sum(r) - sum(l - 1);
	}

	T add(int i, T x) {
		assert(0 <= i && i <= N);
		while (i <= N) {
			bit[i] += x;
			i += -i & i;
		}
	}
};
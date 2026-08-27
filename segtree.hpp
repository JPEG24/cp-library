#include <vector>
#include <cassert>
using namespace std;

template<class S, S (*op)(S,S), S (*e)()>
class SegmentTree {
	private:
	vector<S> data;
	int N, siz, log;

	void update(int k) {
		data[k] = op(data[2*k], data[2*k+1]);
	}

	public:
	SegmentTree(): SegmentTree(0) {}
	SegmentTree(int n): SegmentTree(vector<S>(n, e())) {}
	SegmentTree(const vector<S>& v) { init(v); }

	void init(const vector<S>& v) {
		N = v.size();
		siz = 1;
		while (siz < N) siz <<= 1;
		log = __builtin_ctz(siz);
		data = vector<S>(2 * siz, e());
		for (int i = 0; i < N; i++) data[siz + i] = v[i];
		for (int i = siz - 1; i >= 1; i--) update(i);
	}

	void set(int p, S x) {
		assert(0 <= p && p < N);
		p += siz;
		data[p] = x;
		for (int i = 1; i <= log; i++) update(p >> i);
	}

	S get(int p) const {
		assert(0 <= p && p < N);
		return data[p + siz];
	}

	S prod(int l, int r) const {
		assert(0 <= l && l <= r && r <= N);
		S sml = e(), smr = e();
		l += siz;
		r += siz;
		while (l < r) {
			if (l & 1) sml = op(sml, data[l++]);
			if (r & 1) smr = op(data[--r], smr);
			l >>= 1;
			r >>= 1;
		}
		return op(sml, smr);
	}

	S all_prod() const { return data[1]; }

	template<bool (*f)(S)>
	int max_right(int l) const {
		return max_right(l, [](S x) { return f(x); });
	}
	template<class F>
	int max_right(int l, F f) const {
		assert(0 <= l && l <= N);
		assert(f(e()));
		if (l == N) return N;
		l += siz;
		S sm = e();
		do {
			while (l % 2 == 0) l >>= 1;
			if (!f(op(sm, data[l]))) {
				while (l < siz) {
					l = (2 * l);
					if (f(op(sm, data[l]))) {
						sm = op(sm, data[l]);
						l++;
					}
				}
				return l - siz;
			}
			sm = op(sm, data[l]);
			l++;
		} while ((l & -l) != l);
		return N;
	}

	template<bool (*f)(S)>
	int min_left(int r) const {
		return min_left(r, [](S x) { return f(x); });
	}
	template<class F>
	int min_left(int r, F f) const {
		assert(0 <= r && r <= N);
		assert(f(e()));
		if (r == 0) return 0;
		r += siz;
		S sm = e();
		do {
			r--;
			while (r > 1 && (r % 2)) r >>= 1;
			if (!f(op(data[r], sm))) {
				while (r < siz) {
					r = (2 * r + 1);
					if (f(op(data[r], sm))) {
						sm = op(data[r], sm);
						r--;
					}
				}
				return r + 1 - siz;
			}
			sm = op(data[r], sm);
		} while ((r & -r) != r);
		return 0;
	}
};
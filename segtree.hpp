#include <vector>
#include <cassert>
using namespace std;

template <class S, S (*op)(S, S), S (*e)()>
struct segtree {
private:
	int _n, size, log;
	vector<S> d;

public:
	segtree(int n) : _n(n) {
		size = 1;
		log = 0;
		while (size < _n) {
			size <<= 1;
			log++;
		}
		d.assign(2 * size, e());
	}

	void apply(int l, int r, S x) {
		assert(0 <= l && l <= r && r <= _n);

		l += size;
		r += size;

		while (l < r) {
			if (l & 1) d[l] = op(d[l], x), l++;
			if (r & 1) --r, d[r] = op(d[r], x);
			l >>= 1;
			r >>= 1;
		}
	}

	S get(int p) const {
		assert(0 <= p && p < _n);

		S res = e();
		p += size;

		while (p) {
			res = op(res, d[p]);
			p >>= 1;
		}

		return res;
	}
};

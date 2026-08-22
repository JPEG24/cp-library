#include <vector>
#include <cassert>
using namespace std;

template <class S, S (*op)(S, S), S (*e)()>
class SegmentTree {
	private:
	int siz = 1;
	vector<S> dat;

	public:
	SegmentTree(int n=0) {
		init(n);
	}

	void init(int n) {
		siz = 1;
		while (siz < n) siz *= 2;
		dat.assign(siz * 2, e());
	}

	void apply(int l, int r, S x) {
		assert(0 <= l && l <= r && r <= siz);

		l += siz;
		r += siz;

		while (l < r) {
			if (l & 1) dat[l] = op(dat[l], x), l++;
			if (r & 1) --r, dat[r] = op(dat[r], x);
			l /= 2;
			r /= 2;
		}
	}

	S get(int p) {
		assert(0 <= p && p < siz);

		p += siz;
		S ans = e();

		while (p >= 1) {
			ans = op(ans, dat[p]);
			p /= 2;
		}

		return ans;
	}
};
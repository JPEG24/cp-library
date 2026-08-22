#include <vector>
#include <cassert>
using namespace std;

template <class T>
struct FenwickTree {
	private:
	int _n;
	vector<T> data;
	void add(int p, T x) {
		assert(0 <= p && p < _n);
		p++;
		while (p <= _n) {
			data[p - 1] += x;
			p += p & -p;
		}
	}

	T sum(int r) const {
		T s = 0;
		while (r > 0) {
			s += data[r - 1];
			r -= r & -r;
		}
		return s;
	}

	public:
	FenwickTree(int n=0) : _n(n), data(n) {}
	
	void apply(int l, int r, T x) {
		assert(0 <= l && l <= r && r <= _n);
		add(l, x);
		if (r < _n) add(r, -x);
	}

	T get(int p) const {
		assert(0 <= p && p < _n);
		return sum(p + 1);
	}

	void set(int p, T x) {
		T cur = get(p);
		apply(p, p + 1, x - cur);
	}
};
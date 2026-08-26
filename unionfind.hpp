#include <vector>
using namespace std;

class UnionFind {
private:
	vector<int> par, siz;
	int N, cnt;

public:
	UnionFind(int x=0) { init(x);}

	void init(int n) {
		par.assign(n, -1);
		siz.assign(n, 1);
		N = n;
		cnt = n;
	}

	int root(int v) {
		if (par[v] == -1) return v;
		return par[v] = root(par[v]);
	}

	bool merge(int u, int v) {
		int RootU = root(u);
		int RootV = root(v);
		if (RootU == RootV) return false;
		if (siz[RootU] < siz[RootV]) {
			par[RootU] = RootV;
			siz[RootV] = siz[RootU] + siz[RootV];
		} else {
			par[RootV] = RootU;
			siz[RootU] = siz[RootU] + siz[RootV];
		}
		cnt--;
		return true;
	}

	bool same(int u, int v) { return root(u) == root(v);}

	int size(int v) { return siz[root(v)];}

	int count() { return cnt;}

	vector<vector<int>> groups() {
		vector<vector<int>> res(cnt);
		vector<int> idx(N,-1);
		int now = 0;
		for (int i = 0; i < N; i++) {
			int RootI = root(i);
			if (idx[RootI] == -1) {
				idx[RootI] = now++;
			}
			res[idx[RootI]].push_back(i);
		}
		return res;
	}
};
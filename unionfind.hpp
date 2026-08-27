#include <vector>
using namespace std;

class UnionFind {
private:
	vector<int> par, siz;
	int N, cnt;

public:
	UnionFind(int n=0): N(n), cnt(n) {
		par = vector<int>(N, -1);
		siz = vector<int>(N, 1);
	}

	int leader(int v) {
		if (par[v] == -1) return v;
		return par[v] = leader(par[v]);
	}

	bool merge(int u, int v) {
		int RootU = leader(u);
		int RootV = leader(v);
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

	bool same(int u, int v) { return leader(u) == leader(v); }

	int size(int v) { return siz[leader(v)]; }

	int count() { return cnt; }

	vector<vector<int>> groups() {
		vector<vector<int>> res(cnt);
		vector<int> idx(N,-1);
		int now = 0;
		for (int i = 0; i < N; i++) {
			int RootI = leader(i);
			if (idx[RootI] == -1) {
				idx[RootI] = now++;
			}
			res[idx[RootI]].push_back(i);
		}
		return res;
	}
};
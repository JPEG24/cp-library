#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <numeric>
#include <limits>
#include <cassert>
#include <functional>
#include <utility>
using namespace std;

#include "lib/unionfind.hpp"

struct Edge {
	int to;
	long long cost;
	Edge(int to=0, long long cost=0) : to(to), cost(cost) {}

	bool operator==(const Edge& other) const {
		return to == other.to && cost == other.cost;
	}
	bool operator<(const Edge& other) const {
		if (cost != other.cost) return cost < other.cost;
		return to < other.to;
	}
};

struct Edge2 {
	int from, to;
	long long cost;
	Edge2(int from=0, int to=0, long long cost=0) : from(from), to(to), cost(cost) {}

	bool operator==(const Edge2& other) const {
		return from == other.from && to == other.to && cost == other.cost;
	}
	bool operator<(const Edge2& other) const {
		if (cost != other.cost) return cost < other.cost;
		if (from != other.from) return from < other.from;
		return to < other.to;
	}
};

class Graph {
	private:
	int n;
	
	public:
	vector<vector<Edge>> to;
	vector<vector<Edge>> rto;
	vector<Edge2> edges;

	Graph(int n=0) : n(n), to(n), rto(n) {}

	void add(int a, int b, long long c=0) {
		to[a].emplace_back(b,c);
		rto[b].emplace_back(a,c);
		edges.emplace_back(a,b,c);
	}

	vector<int> topological_sort() {
		vector<int> indeg(n);
		for (int v=0; v<n; v++) {
			for (const auto& e : to[v]) indeg[e.to]++;
		}
		queue<int> q;
		for (int v=0; v<n; v++) if (indeg[v] == 0) q.push(v);
		vector<int> res;
		while (!q.empty()) {
			int v = q.front(); q.pop();
			res.push_back(v);
			for (const auto& e : to[v]) {
				indeg[e.to]--;
				if (indeg[e.to] == 0) q.push(e.to);
			}
		}
		return res;
	}

	vector<int> bfs(int s=0) {
		vector<int> dist(n, -1);
		queue<int> q;
		dist[s] = 0;
		q.push(s);
		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (const auto& e : to[v]) {
				if (dist[e.to] == -1) {
					dist[e.to] = dist[v]+1;
					q.push(e.to);
				}
			}
		}
		return dist;
	}

	vector<int> bfs01(int s=0) {
		const int inf = 1e9;
		vector<int> dist(n, inf);
		deque<int> q;
		dist[s] = 0;
		q.push_back(s);
		while (!q.empty()) {
			int v = q.front(); q.pop_front();
			for (const auto& e : to[v]) {
				assert(e.cost == 0 || e.cost == 1);
				if (dist[e.to] > dist[v]+e.cost) {
					dist[e.to] = dist[v]+e.cost;
					if (e.cost == 0) q.push_front(e.to);
					else q.push_back(e.to);
				}
			}
		}
		for (int i = 0; i < n; i++) if (dist[i] == inf) dist[i] = -1;
		return dist;
	}

	vector<long long> dijkstra(int s=0) {
		const long long inf = numeric_limits<long long>::max()/2;
		vector<long long> dist(n, inf);
		using P = pair<long long,int>;
		priority_queue<P, vector<P>, greater<P>> pq;
		dist[s] = 0;
		pq.emplace(0,s);
		while (!pq.empty()) {
			auto [d,v] = pq.top(); pq.pop();
			if (dist[v] < d) continue;
			for (const auto& e : to[v]) {
			assert(e.cost >= 0);
				if (dist[e.to] > dist[v]+e.cost) {
					dist[e.to] = dist[v]+e.cost;
					pq.emplace(dist[e.to], e.to);
				}
			}
		}
		for (int i = 0; i < n; i++) if (dist[i] == inf) dist[i] = -1;
		return dist;
	}

	pair<bool, vector<long long>> bellman_ford(int s=0, int g=-1) {
		const long long inf = numeric_limits<long long>::max()/2;

		vector<bool> ok(n, true);

		if (g != -1) {
			vector<bool> reachableFromS(n, false);
			vector<bool> reachableFromG(n, false);

			auto dfs = [&](auto f, int v) -> void {
				reachableFromS[v] = true;
				for (const auto& e : to[v]) {
					if (!reachableFromS[e.to]) {
						f(f, e.to);
					}
				}
			};

			auto rdfs = [&](auto f, int v) -> void {
				reachableFromG[v] = true;
				for (const auto& e : rto[v]) {
					if (!reachableFromG[e.to]) {
						f(f, e.to);
					}
				}
			};

			dfs(dfs, s);
			rdfs(rdfs, g);

			for (int v=0; v<n; v++) {
				ok[v] = reachableFromS[v] && reachableFromG[v];
			}
		}

		vector<long long> dist(n, inf);
		dist[s] = 0;

		for (int iter=0; iter<n-1; iter++) {
			bool upd = false;

			for (const auto& e : edges) {
				if (!ok[e.from] || !ok[e.to]) continue;
				if (dist[e.from] == inf) continue;

				if (dist[e.to] > dist[e.from]+e.cost) {
					dist[e.to] = dist[e.from]+e.cost;
					upd = true;
				}
			}

			if (!upd) break;
		}

		for (const auto& e : edges) {
			if (!ok[e.from] || !ok[e.to]) continue;
			if (dist[e.from] == inf) continue;

			if (dist[e.to] > dist[e.from]+e.cost) {
				return {false, dist};
			}
		}
		for (int i = 0; i < n; i++) if (dist[i] == inf) dist[i] = -1;

		return {true, dist};
	}

	vector<vector<long long>> warshall_floyd() {
		const long long inf = numeric_limits<long long>::max()/2;
		vector<vector<long long>> dist(n, vector<long long>(n, inf));
		for (int v=0; v<n; v++) dist[v][v] = 0;
		for (int v=0; v<n; v++) {
			for (const auto& e : to[v]) {
				dist[v][e.to] = e.cost;
			}
		}
		for (int k=0; k<n; k++) {
			for (int i=0; i<n; i++) {
				for (int j=0; j<n; j++) {
					if (dist[i][k] == inf || dist[k][j] == inf) continue;
					dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
				}
			}
		}
		return dist;
	}

	pair<long long, vector<bool>> min_kruskal() {
		vector<bool> used(edges.size(), false);
		long long total_cost = 0;
		UnionFind uf(n);
		vector<int> idx(edges.size());
		iota(idx.begin(), idx.end(), 0);
		sort(idx.begin(), idx.end(), [&](int i, int j) {
			return edges[i].cost < edges[j].cost;
		});

		for (int i : idx) {
			const auto& e = edges[i];
			if (uf.same(e.from, e.to)) continue;
			uf.merge(e.from, e.to);
			used[i] = true;
			total_cost += e.cost;
		}
		return {total_cost, used};
	}

	pair<long long, vector<bool>> max_kruskal() {
		vector<bool> used(edges.size(), false);
		long long total_cost = 0;
		UnionFind uf(n);
		vector<int> idx(edges.size());
		iota(idx.begin(), idx.end(), 0);
		sort(idx.begin(), idx.end(), [&](int i, int j) {
			return edges[i].cost > edges[j].cost;
		});
		for (int i : idx) {
			const auto& e = edges[i];
			if (uf.same(e.from, e.to)) continue;
			uf.merge(e.from, e.to);
			used[i] = true;
			total_cost += e.cost;
		}
		return {total_cost, used};
	}
};
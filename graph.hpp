#include <vector>
using namespace std;

#include "lib/unionfind.hpp"

struct Edge {
	int from, to;
	long long cost;
	int id;
	Edge(int from=0, int to=0, long long cost=0, int id=0) : from(from), to(to), cost(cost), id(id) {}

	bool operator==(const Edge& other) const {
		return from == other.from && to == other.to && cost == other.cost && id == other.id;
	}
	bool operator<(const Edge& other) const {
		if (cost != other.cost) return cost < other.cost;
		if (from != other.from) return from < other.from;
		if (to != other.to) return to < other.to;
		return id < other.id;
	}
};

struct Graph {
	private:
	int n, m = 0;
	
	public:
	vector<vector<Edge>> to;
	vector<vector<Edge>> rto;
	vector<Edge> edges;

	Graph(int n=0) : n(n), to(n), rto(n) {}

	void add(int a, int b, long long c=0) {
		Edge e(a, b, c, edges.size());
		to[a].emplace_back(e);
		rto[b].emplace_back(e);
		edges.emplace_back(e);
		m++;
	}
};
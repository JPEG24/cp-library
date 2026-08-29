#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

#include "graph.hpp"
#include "union-find.hpp"

using ll = long long;

pair<ll, vector<int>> min_kruskal(const Graph& g) {
  UnionFind uf(g.N);
  vector<int> res;
  vector<Edge> edges = g.edges;
  sort(edges.begin(), edges.end());
  ll tot = 0;
  for (auto e : edges) {
    if (uf.same(e.from, e.to)) continue;
    uf.merge(e.from, e.to);
    res.push_back(e.id);
    tot += e.cost;
  }
  return {tot, res};
}

pair<ll, vector<int>> max_kruskal(const Graph& g) {
  UnionFind uf(g.N);
  vector<int> res;
  vector<Edge> edges = g.edges;
  sort(edges.rbegin(), edges.rend());
  ll tot = 0;
  for (auto e : edges) {
    if (uf.same(e.from, e.to)) continue;
    uf.merge(e.from, e.to);
    res.push_back(e.id);
    tot += e.cost;
  }
  return {tot, res};
}
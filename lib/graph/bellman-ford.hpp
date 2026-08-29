#include <vector>
using namespace std;

#include "graph.hpp"

using ll = long long;

pair<bool,vector<ll>> Bellman_Ford(const Graph& g, int s=0) {
  assert(0 <= s && s < g.N);
  vector<ll> dist(g.N, g.INF);
  dist[s] = 0;
  for (int i = 0; i < g.N; i++) {
    bool upd = false;
    for (auto e : g.edges) {
      if (dist[e.from] == g.INF) continue;
      ll nd = dist[e.from] + e.cost;
      if (dist[e.to] == g.INF || dist[e.to] > nd) {
        dist[e.to] = nd;
        upd = true;
      }
    }
    if (!upd) return {true,dist};
  }
  return {false,{}};
}

pair<bool, vector<ll>> Bellman_Ford(const Graph& g, const vector<int>& s) {
  Graph ng(g.N+1);
  for (auto e : g.edges) {
    ng.add(e.from, e.to, e.cost);
  }
  for (int ns : s) {
    assert(0 <= ns && ns < g.N);

    ng.add(g.N, ns, 0);
  }
  auto [ok, dist] = Bellman_Ford(ng, g.N);
  if (!ok) return {false, {}};
  dist.pop_back();
  return {true, dist};
}
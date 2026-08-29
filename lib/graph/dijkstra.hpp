#include <vector>
#include <queue>
#include <cassert>
using namespace std;

#include "graph.hpp"

using ll = long long;

vector<ll> Dijkstra(const Graph& g, const vector<int>& s) {
  vector<ll> dist(g.N, g.INF);
  priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
  for (int ns : s) {
    assert(0 <= ns && ns < g.N);
    dist[ns] = 0;
    pq.emplace(0, ns);
  }
  while (!pq.empty()) {
    auto [d,v] = pq.top(); pq.pop();
    if (dist[v] != d) continue;
    for (auto e : g.to[v]) {
      assert(e.cost >= 0);
      ll nd = d + e.cost;
      if (dist[e.to] > nd) {
        dist[e.to] = nd;
        pq.emplace(nd, e.to);
      }
    }
  }
  return dist;
}

vector<ll> Dijkstra(const Graph& g, int s=0) {
  return Dijkstra(g, vector<int>{s});
}
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

#include "graph.hpp"

vector<int> BFS(const Graph& g, const vector<int>& s={0}) {
  vector<int> dist(g.N, g.INT_INF);
  queue<int> q;
  for (int ns : s) {
    assert(0 <= ns && ns < g.N);
    dist[ns] = 0;
    q.push(ns);
  }
  while (!q.empty()) {
    int v = q.front(); q.pop();
    for (auto e : g.to[v]) {
      assert(e.cost == 1);
      if (dist[e.to] != g.INT_INF) continue;
      dist[e.to] = dist[v] + 1;
      q.push(e.to);
    }
  }
  return dist;
}

vector<int> BFS(const Graph& g, int s=0) {
  return BFS(g, vector<int>{s});
}
#include <vector>
#include <deque>
#include <cassert>
using namespace std;

#include "graph.hpp"

vector<int> BFS_01(const Graph& g, const vector<int>& s) {
  vector<int> dist(g.N, g.INT_INF);
  deque<int> dq;
  for (int ns : s) {
    assert(0 <= ns && ns < g.N);
    dist[ns] = 0;
    dq.push_back(ns);
  }
  while (!dq.empty()) {
    int v = dq.front(); dq.pop_front();
    for (auto e : g.to[v]) {
      assert(e.cost == 0 || e.cost == 1);
      if (dist[e.to] > dist[v] + e.cost) {
        dist[e.to] = dist[v] + e.cost;
        if (e.cost == 0) dq.push_front(e.to);
        else dq.push_back(e.to);
      }
    }
  }
  return dist;
}

vector<int> BFS_01(const Graph& g, int s=0) {
  return BFS_01(g, vector<int>{s});
}
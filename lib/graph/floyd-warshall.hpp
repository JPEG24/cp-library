#include <vector>
using namespace std;

#include "graph.hpp"

using ll = long long;

vector<vector<ll>> Floyd_Warshall(const Graph& g) {
  vector<vector<ll>> dist(g.N, vector<ll>(g.N, g.INF));
  for (int i = 0; i < g.N; i++) dist[i][i] = 0;
  for (auto e : g.edges) {
    if (dist[e.from][e.to] > e.cost) {
      dist[e.from][e.to] = e.cost;
    }
  }
  for (int k = 0; k < g.N; k++) {
    for (int i = 0; i < g.N; i++) {
      if (dist[i][k] == g.INF) continue;
      for (int j = 0; j < g.N; j++) {
        if (dist[k][j] == g.INF) continue;
        ll nd = dist[i][k] + dist[k][j];
        if (dist[i][j] > nd) {
          dist[i][j] = nd;
        }
      }
    }
  }
  return dist;
}
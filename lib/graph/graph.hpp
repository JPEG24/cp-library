#pragma once

#include <vector>
#include <cassert>
#include <queue>
using namespace std;

using ll = long long;

struct Edge {
  int from, to;
  ll cost;
  int id;
  pair<ll,int> tp;
  Edge(int from=0, int to=0, ll cost=0, int id=0): from(from), to(to), cost(cost), id(id) {
    tp = {cost, id};
  }

  bool operator==(const Edge& other) const { return tp == other.tp; }
  bool operator<(const Edge& other) const { return tp < other.tp; }
};

struct Graph {
  const ll INF = 2'000'000'000'000'000'000;
  const int INT_INF = 2'000'000'000;
  int N;
  
  vector<vector<Edge>> to;
  vector<vector<Edge>> rto;
  vector<Edge> edges;

  Graph(int n=0): N(n), to(n), rto(n) {}

  void add(int a, int b, long long c=1) {
    assert(0 <= a && a < N);
    assert(0 <= b && b < N);
    Edge e(a, b, c, edges.size());
    to[a].push_back(e);
    rto[b].push_back(e);
    edges.push_back(e);
  }

  void add_undirected(int a, int b, long long c=1) {
    assert(0 <= a && a < N);
    assert(0 <= b && b < N);
    Edge e1(a, b, c, edges.size());
    Edge e2(b, a, c, edges.size()+1);
    to[a].push_back(e1);
    to[b].push_back(e2);
    rto[b].push_back(e1);
    rto[a].push_back(e2);
    edges.push_back(e1);
  }
};


bool has_negative_cycle(const Graph& g) {
  vector<ll> dist(g.N, 0);
  for (int i = 0; i < g.N; i++) {
    bool upd = false;
    for (auto e : g.edges) {
      if (dist[e.from] == g.INF) continue;
      if (dist[e.to] > dist[e.from] + e.cost) {
        dist[e.to] = dist[e.from] + e.cost;
        upd = true;
      }
    }
    if (!upd) return false;
  }
  return true;
}

vector<int> topological_sort(const Graph& g) {
  vector<int> indeg(g.N);
  for (int i = 0; i < g.N; i++) {
    for (auto e : g.to[i]) indeg[e.to]++;
  }
  vector<int> res;
  queue<int> que;
  for (int i = 0; i < g.N; i++) if (indeg[i] == 0) que.push(i);
  while (!que.empty()) {
    int v = que.front(); que.pop();
    res.push_back(v);
    for (auto e : g.to[v]) {
      indeg[e.to]--;
      if (indeg[e.to] == 0) que.push(e.to);
    }
  }
  assert((int)res.size() == g.N);
  return res;
}
#include <vector>
#include <queue>
#include <cassert>
#include <algorithm>
using namespace std;

#include "unionfind.hpp"

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

vector<vector<ll>> Warshall_Floyd(const Graph& g) {
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

vector<int> topological_sort(const Graph& g) {
  vector<int> indeg(g.N);
  for (auto e : g.edges) indeg[e.to]++;
  queue<int> q;
  for (int i = 0; i < g.N; i++) if (indeg[i] == 0) q.push(i);
  vector<int> res;
  while (!q.empty()) {
    int v = q.front(); q.pop();
    res.emplace_back(v);
    for (auto e : g.to[v]) {
      indeg[e.to]--;
      if (indeg[e.to] == 0) q.push(e.to);
    }
  }
  assert(res.size() == g.N);
  return res;
}
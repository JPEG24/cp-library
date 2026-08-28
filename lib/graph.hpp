#include <vector>
using namespace std;
using ll = long long;

struct Edge {
  int from, to;
  ll cost;
  int id;
  tuple<ll,int,int,int> tp;
  Edge(int from=0, int to=0, ll cost=0, int id=0): from(from), to(to), cost(cost), id(id) {
    tp = make_tuple(cost, from, to, id);
  }

  bool operator==(const Edge& other) const { return tp == other.tp; }
  bool operator<(const Edge& other) const { return tp < other.tp; }
};

struct Graph {
  private:
  int N, M = 0;
  
  public:
  vector<vector<Edge>> to;
  vector<vector<Edge>> rto;
  vector<Edge> edges;

  Graph(int n=0): N(n), to(n), rto(n) {}

  void add(int a, int b, long long c=0) {
    Edge e(a, b, c, edges.size());
    to[a].emplace_back(e);
    rto[b].emplace_back(e);
    edges.emplace_back(e);
    M++;
  }
};
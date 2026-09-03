#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

struct Trie {
  struct Node {
    unordered_map<char,int> to;
    int cnt;
    Node(): to(26,-1), cnt(0) {}
  };
  vector<Node> d;
  Trie() : d(1) {}
  void add (const string &s) {
    int v = 0;
    for (char c : s) {
      int u = c - 'a';
      if (!d[v].to.count(u)) {
        d[v].to[u] = d.size();
        d.push_back(Node());
      }
      v = d[v].to[u];
      d[v].cnt++;
    }
  }
};
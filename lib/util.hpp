#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
using namespace std;

using ll = long long;
using ld = long double;
template<class T> using greater_queue = priority_queue<T,vector<T>,greater<T>>;
template<class T> using uset = unordered_set<T>;
template<class T,class U> using umap = unordered_map<T,U>;
#define rep(i,s,n) for (int i = (s); i < (n); i++)
#define rep1(i,s,n) for (int i = (s); i <= (n); i++)
#define REP(i,n,s) for (int i = (n)-1; i >= s; i--)
#define REP1(i,n,s) for (int i = (n); i >= s; i--)
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
template<class T> int sz(T a) { return a.size(); }
template<class T> bool chmax(T& a, const T& b) { return (a < b ? (a = b, true) : false); }
template<class T> bool chmin(T& a, const T& b) { return (a > b ? (a = b, true) : false); }
void YesNo(bool b) { cout << (b ? "Yes\n" : "No\n"); }
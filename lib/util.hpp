#include <queue>
#include <iostream>
using namespace std;

using ll = long long;
using ld = long double;
template<class T> using greater_queue = priority_queue<T,vector<T>,greater<T>>;
#define rep(i,s,n) for (int i = (s); i < (n); i++)
#define rep1(i,s,n) for (int i = (s); i <= (n); i++)
#define REP(i,n,s) for (int i = (n)-1; i >= s; i--)
#define REP1(i,n,s) for (int i = (n); i >= s; i--)
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
inline void YesNo(const bool& b) { cout << (b ? "Yes\n" : "No\n"); }
template<class T> constexpr int sz(const T& a) { return (int)a.size(); }
template<class T>
constexpr bool chmax(T& a, const T& b) {
	if (a >= b) return false;
	a = b;
	return true;
}
template<class T>
constexpr bool chmin(T& a, const T& b) {
	if (a <= b) return false;
	a = b;
	return true;
}
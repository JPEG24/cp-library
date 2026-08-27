#include <cmath>
#include <iostream>
using namespace std;
using ld = long double;

struct V {
	static constexpr ld eps = 1e-9;
  ld x, y;
  V(ld x=0, ld y=0): x(x), y(y) {}
  V& operator+=(const V& v) { x += v.x; y += v.y; return *this; }
  V operator+(const V& v) const { return V(*this) += v; }
  V& operator-=(const V& v) { x -= v.x; y -= v.y; return *this; }
  V operator-(const V& v) const { return V(*this) -= v; }
  V& operator*=(ld s) { x *= s; y *= s; return *this; }
  V operator*(ld s) const { return V(*this) *= s; }
  V& operator/=(ld s) { x /= s; y /= s; return *this; }
  V operator/(ld s) const { return V(*this) /= s; }
  ld dot(const V& v) const { return x*v.x + y*v.y; }
  ld cross(const V& v) const { return x*v.y - v.x*y; }
  ld norm2() const { return x*x + y*y; }
  ld norm() const { return sqrtl(norm2()); }
  V normalize() const {
    auto n = norm();
    if (fabsl(n) < eps) return V(0,0);
    return *this/norm();
  }
  V rotate90() const { return V(y, -x);}
  int ort() const { // orthant
    if (fabsl(x) < eps && fabsl(y) < eps) return 0;
    if (y > 0) return x>0 ? 1 : 2;
    else return x>0 ? 4 : 3;
  }
  bool operator<(const V& v) const {
    int o = ort(), vo = v.ort();
    if (o != vo) return o < vo;
    return cross(v) > 0;
  }
};
istream& operator>>(istream& is, V& v) {
  is >> v.x >> v.y; return is;
}
ostream& operator<<(ostream& os, const V& v) {
  os<<"("<<v.x<<","<<v.y<<")"; return os;
}
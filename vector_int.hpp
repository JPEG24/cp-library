#include <cmath>
#include <iostream>
using namespace std;

struct V {
  long long x, y;
  V(long long x=0, long long y=0): x(x), y(y) {}
  V& operator+=(const V& v) { x += v.x; y += v.y; return *this;}
  V operator+(const V& v) const { return V(*this) += v;}
  V& operator-=(const V& v) { x -= v.x; y -= v.y; return *this;}
  V operator-(const V& v) const { return V(*this) -= v;}
  V& operator*=(long long s) { x *= s; y *= s; return *this;}
  V operator*(long long s) const { return V(*this) *= s;}
  long long dot(const V& v) const { return x*v.x + y*v.y;}
  long long cross(const V& v) const { return x*v.y - v.x*y;}
  long long norm2() const { return x*x + y*y;}
  V rotate90() const { return V(y, -x);}
  int ort() const { // orthant
    if (x == 0 && y == 0) return 0;
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
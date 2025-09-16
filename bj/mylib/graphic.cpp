/*
2차원 그래픽 관련 알고리즘
1. vec2_cross: 벡터 외적
2. ccw: 점의 위치 관계 파악
3. line_intersect: 선분 교차 파악
*/

#include <iostream>

struct point {
  int x, y;
  auto operator<=>(const point&) const = default;
};
using vec2 = point;
std::ostream& operator<<(std::ostream& os, const point& p) {
  os << "(" << p.x << ", " << p.y << ")";
  return os;
}
vec2 operator-(const point& p1, const point& p2) {
  return vec2{p1.x - p2.x, p1.y - p2.y};
}
struct line {
  point p1, p2;
};
std::istream& operator>>(std::istream& is, line& l) {
  is >> l.p1.x >> l.p1.y >> l.p2.x >> l.p2.y;
  return is;
}
std::ostream& operator<<(std::ostream& os, const line& l) {
  os << "{" << l.p1 << ", " << l.p2 << "}";
  return os;
}

int vec2_cross(const vec2 v1, const vec2 v2) {
  return v1.x * v2.y - v1.y * v2.x;
}

int ccw(const point p1, const point p2, const point p3) {
  int v = vec2_cross(p1, p2) + vec2_cross(p2, p3) + vec2_cross(p3, p1);
  if (v > 0) {
    return 1;  // CCW
  } else if (v < 0) {
    return -1;  // CW
  } else
    return 0;  // PARELLEL
}

bool line_intersect(const line& l1, const line& l2) {
  vec2 p1 = l1.p1;
  vec2 p2 = l1.p2;
  vec2 p3 = l2.p1;
  vec2 p4 = l2.p2;

  int p1p2 = ccw(p1, p2, p3) * ccw(p1, p2, p4);
  int p3p4 = ccw(p3, p4, p1) * ccw(p3, p4, p2);

  if (p1p2 == 0 && p3p4 == 0) {
    // 일직선 상에 존재
    if (p2 < p1) std::swap(p1, p2);
    if (p4 < p3) std::swap(p3, p4);
    // 선분이 포개져 있는가? 그러면 교차한 것이다.
    return p3 <= p2 && p1 <= p4;
  }
  // 일직선 상에 존재하지 않음
  return p1p2 <= 0 && p3p4 <= 0;
}

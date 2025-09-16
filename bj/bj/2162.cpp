/*
bj2162 선분 그룹
n개의 선분이 주어질 때, 선분 그룹의 개수와
가장 큰 그룹에 속한 선분의 수를 구하여라.
두 선분이 서로 만나는 경우에, 두 선분은 같은 그룹에 속한다.
n<=3000

접근: disjoint set
1. 각 선분이 서로 겹치는지를 파악하여 인접 행렬을 만든다.
2. 인접 행렬을 이용해 disjoint set을 구한다.

*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <tuple>
#include <vector>

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

class disjoint_set {
 public:
  disjoint_set(int n) : data(n, -1) {}
  int find_root(int i) {
    if (data[i] < 0) return i;
    // compression
    data[i] = find_root(data[i]);
    return data[i];
  }
  bool in_same_group(int a, int b) { return find_root(a) == find_root(b); }
  bool merge(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    if (a == b) return false;

    // if (data[a] > data[b]) std::swap(a, b);
    data[a] += data[b];
    data[b] = a;
    return true;
  }
  std::tuple<int, int> solve() {
    int num = 0;
    int sz = 0;
    for (auto s : data) {
      if (s < 0) {
        ++num;
        sz = std::min(sz, s);
      }
    }
    return {num, -sz};
  }

 private:
  std::vector<int> data;
};

std::vector<line> lines;

int main(void) {
  int n;
  std::cin >> n;

  disjoint_set djs(n);

  for (int i = 0; i < n; ++i) {
    line temp;
    std::cin >> temp;
    if (temp.p1 > temp.p2) std::swap(temp.p1, temp.p2);
    lines.push_back(temp);
  }

  std::ranges::sort(
      lines, [](const line& l1, const line& l2) { return l1.p1 < l2.p1; });

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      // if (djs.in_same_group(i, j)) continue;
      if (lines[i].p2.x < lines[j].p1.x) break;
      if (line_intersect(lines[i], lines[j])) {
        djs.merge(i, j);
      }
    }
  }

  auto [num, sz] = djs.solve();

  std::cout << num << '\n' << sz;
}
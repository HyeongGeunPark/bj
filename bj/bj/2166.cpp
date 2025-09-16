#include <iomanip>
#include <iostream>

struct Point {
  long long x;
  long long y;
};

std::istream& operator>>(std::istream& is, Point& p) {
  is >> p.x >> p.y;
  return is;
}

Point operator-(const Point& a, const Point& b) {
  Point r{a.x - b.x, a.y - b.y};
  return r;
}

long long area_calculate(const Point a, const Point b) {
  return (a.x * b.y - a.y * b.x);
}

int main() {
  int n;
  long long area = 0;
  Point p1, p2, origin;

  std::cin >> n;

  std::cin >> p1;
  origin = p1;

  for (int i = 1; i < n; ++i) {
    std::cin >> p2;
    area += area_calculate(p1, p2);
    p1 = p2;
  }
  area += area_calculate(p1, origin);

  area = std::abs(area);
  std::cout << area / 2 << '.' << ((area % 2 == 1) ? '5' : '0') << '\n';
}
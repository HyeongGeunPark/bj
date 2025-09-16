/*
bj1708 볼록 껍질

편의상 모든 내각의 크기가 180도 미만인 경우를 볼록 다각형으로 한정한다.

2차원 평면에 N개의 점이 주어졌을 때, 이들 중 몇 개의 점을 골라 볼록
다각형을 만드는데, 나머지 모든 점을 내부에 포함하도록 할 수 있다.
이를 볼록 껍질(convex hull)이라 한다.

점의 집합이 주어졌을 때, 볼록 껍질을 이루는 점의 개수를 구하는 프로그램을
작성하시오.

입력:
점의 개수 N ( 3 <= N <+ 100'000 )
x좌표, y좌표 * N

주어지는 모든 점의 좌표는 다르다.
x좌표와 y좌표의 범위는 절대값 40'000을 넘지 않는다.
입력으로 주어지는 다각형의 모든 점이 일직선을 이루는 경우는 없다.

볼록 껍질의 변에 점이 여러 개 있는 경우에는 가장 양 끝 점만 개수에 포함한다.

접근: Graham's scan

1. 가장 작은 y좌표를 가진 점을 구한다.
  1-1. 여러 개 있다면 가장 작은 x좌표를 가진 점을 선택한다.
2. 선택한 점을 기준으로 나머지 점을 반시계 방향으로 정렬한다.
  부동소수점 각도(기울기, 코사인 등)를 계산하는 경우 오차에 의한 문제가 있다.
  ccw 알고리즘을 이용하고, 동일 직선상에 있는 경우(ccw result ==0)
  거리를 기준으로 짧은 것이 앞에 오도록 하거나,
  가장 먼 것만 포함되도록 하는 식으로 정렬해야 한다.
  L1 거리를 사용해도 된다.
3. 처음에 선택한 점을 스택에 넣는다.
4. 정렬된 점들에 대해 순차적으로 다음을 반복한다.
  4-0. 다음 점을 선택한다.
  4-1. 스택에 오직 한 개의 점만 있는 경우 현재 점을 스택에 넣는다.
  4-2. 그렇지 않은 경우
    스택의 마지막 두 점이 이루는 선분에 대해,
    현재 점이 그 선분의 오른쪽에 있으면( + 직선인 경우도 포함)
    스택의 마지막 점을 하나 제거하고 4-1로 돌아간다.
    현재 점이 그 선분의 왼쪽에 있으면 현재 점을 스택에 넣고
    4-0으로 돌아간다.
5. 마지막에 스택에 남아 있는 점들이 주어진 점들에 대한 convex hull을 이루는
  점들이다.

4의 계산을 위해 ccw 알고리즘을 사용한다.

주의.
1. 입력/출력이 많을 수 있으므로, 입출력 시간에 주의.
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

struct vec2 {
  long long x, y;
  friend vec2 operator-(const vec2& a, const vec2& b) {
    return vec2{a.x - b.x, a.y - b.y};
  }
};

long long dot_product(const vec2& a, const vec2& b) {
  return a.x * b.x + a.y * b.y;
}

long long cross_product(const vec2& a, const vec2& b) {
  return a.x * b.y - a.y * b.x;
}

int main() {
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);

  int n;
  std::cin >> n;

  std::vector<vec2> points;
  points.reserve(n + 1);
  vec2 first_point{.x = std::numeric_limits<long long>::max(),
                   .y = std::numeric_limits<long long>::max()};

  // input and find first point
  for (int i = 0; i < n; ++i) {
    long long x, y;
    std::cin >> x >> y;
    if (y < first_point.y) {
      first_point.x = x;
      first_point.y = y;
    } else if (y == first_point.y) {
      if (x < first_point.x) {
        first_point.x = x;
        first_point.y = y;
      }
    }
    points.emplace_back(x, y);
  }

  // sort other points
  std::ranges::sort(points, [&first_point](const vec2& a, const vec2& b) {
    // cross product
    vec2 aa = a - first_point;
    vec2 bb = b - first_point;
    long long ccw = cross_product(aa, bb);
    if (ccw == 0) {
      // compare with length from origin
      // use L1 distance (since they are on the same line)
      return (std::abs(aa.x) + std::abs(aa.y)) <
             (std::abs(bb.x) + std::abs(bb.y));
    } else {
      return ccw > 0;
    }
  });

  points.push_back(first_point);

  // Graham's Scan
  std::vector<vec2> hull;
  // hull.reserve(n/2);	// naive guess
  hull.push_back(first_point);

  for (int i = 1; i <= n; ++i) {
    const vec2& point = points[i];
    while (hull.size() != 1) {
      // get last 2 points from stack
      const vec2& back = hull[hull.size() - 1];
      const vec2& back_1 = hull[hull.size() - 2];

      // ccw algorithm
      if (cross_product(back - back_1, point - back) > 0) {
        // left -> break;
        break;
      } else {
        // right or parallel -> pop last point from stack
        hull.pop_back();
      }
    }
    hull.push_back(point);
  }

  std::cout << hull.size() - 1 << '\n';

  return 0;
}
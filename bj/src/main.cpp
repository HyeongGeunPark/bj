/*
bj14266 나는 가르친다 스위핑을

1사분면 정수 좌표계에 n개의 선분이 주어질 때,
원점을 지나는 직선 중 교차하는 선분이 최대가 되는 직선에 대해
그 선분들의 개수를 구하여라.

1 <= n <= 100'000

1<= x1, y21, x2, y2 <= 1'000'000'000

접근: 스위핑

1. 각 선분을 입력받으면서 선분의 두 끝점과 원점 사이의 기울기를 계산한다.
2. 두 점의 기울기가 다를 때 한 점은 겹치기 시작하는 기울기, 다른 점은 겹치지 않기 시작하는 기울기이다.
3. 두 점의 기울기가 같아도 임의로 위의 속성을 부여한다.
4. 모든 점을 정렬한다.
5. 순서대로 순회하며 결과를 계산한다.  

*/

#include <iostream>
#include <vector> 
#include <algorithm>

struct point {
  double tan;
  int count;
};


int main(void) {

  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);

  int n;
  std::cin >> n;

  std::vector<point> points;
  points.reserve(2 * n);

  for (int i = 0; i < n; ++i) {
    int x1, y1, x2, y2;

    std::cin >> x1 >> y1 >> x2 >> y2;

    double tan_min = (double)y1 / x1; // double 변환이 필요함에 주의
    double tan_max = (double)y2 / x2; 

    if (tan_min > tan_max) std::swap(tan_min, tan_max);


    points.push_back(point{tan_min, 1});
    points.push_back(point{tan_max, -1}); 
  }

  std::sort(points.begin(), points.end(), [](const point& a, const point& b) {
    if (a.tan == b.tan) {
      return a.count > b.count;
    }
    return a.tan < b.tan;
    }); 

  int result = 0;
  int count = 0;
  for (auto& p : points) {
    count += p.count;
    result = std::max(result, count);
  } 

  std::cout << result;

  return 0;
}

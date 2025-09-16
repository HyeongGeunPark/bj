/*

bj17387 선분 교차 2

2차원 좌표평면 위의 두 선분을 입력받아 두 선분이 교차하는지 확인한다.
한 선분의 끝 점이 다른 선분이나 끝 점 위에 있는 것도 교차하는 것이다.

접근법: CCW 알고리즘
      v3
      |
      |
v1-----------v2
      |
      v4
1. ccw 알고리즘을 이용해 v1, v2, v3과 v1, v2, v4의 방향성을 확인한다. (시계,
일직선, 반시계)
2. 마찬가지로 v3, v4, v1과 v3, v4, v2의 방향성도 확인한다.
3. 경우를 나눈다.
    i) 1에서 구한 두 방향성의 곱이 음수 && 2에서 구한 두 방향성의 곱이 음수 ->
교차함 ii) 방향성 곱 중 하나는 0, 다른 하나는 음수 -> 교차함(한 선분의 끝이 다른
선분 위에 존재) iii) 방향성 곱 두 개 모두 0 -> 네 점이 한 직선 위에 존재, 혹은
두 선분의 끝점들 중 하나가 일치치
        -> 각 선분에서 한 점씩 뽑은 쌍의 위치 관계가 어떻게 되는지 파악한다.
        v1, v2를 정렬, v3, v4를 정렬한다.
           v1--------v2
              v3 <----
            ----> v4
            위와 같이 되어야 교차한다. (v3<=v2 && v1<=v4);

*/

#include <iostream>
using ll = long long;

struct vec2 {
  ll x, y;
};

vec2 operator-(const vec2 a, const vec2 b) {
  return vec2{a.x - b.x, a.y - b.y};
}

bool operator>(const vec2 a, const vec2 b) {
  if (a.x > b.x)
    return true;
  else if (a.x == b.x)
    return a.y > b.y;
  else
    return false;
}

bool operator==(const vec2 a, const vec2 b) { return a.x == b.x && a.y == b.y; }

bool operator<=(const vec2 a, const vec2 b) { return !(a > b); }

ll cross(vec2 a, vec2 b) {
  ll result = a.x * b.y - a.y * b.x;
  return result;
}

ll dot(vec2 a, vec2 b) {
  ll result = a.x * b.x + a.y * b.y;
  return result;
}

int ccw(vec2 a, vec2 b, vec2 c) {
  ll x = cross(b - a, c - b);
  if (x > 0)
    return 1;
  else if (x == 0)
    return 0;
  else
    return -1;
}

int intersect(vec2 v1, vec2 v2, vec2 v3, vec2 v4) {
  int ccwp1 = ccw(v1, v2, v3) * ccw(v1, v2, v4);
  int ccwp2 = ccw(v3, v4, v1) * ccw(v3, v4, v2);

  if (ccwp1 == 0 && ccwp2 == 0) {
    if (v1 > v2) std::swap(v1, v2);
    if (v3 > v4) std::swap(v3, v4);
    if (v3 <= v2 && v1 <= v4)
      return 1;
    else
      return 0;
  } else if (ccwp1 <= 0 && ccwp2 <= 0) {
    return 1;
  } else
    return 0;
}

int main(void) {
  vec2 v[5];

  for (int i = 1; i <= 4; ++i) {
    std::cin >> v[i].x;
    std::cin >> v[i].y;
  }

  std::cout << intersect(v[1], v[2], v[3], v[4]);
}
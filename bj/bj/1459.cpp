/*
bj1459 걷기
무한히 큰 격자형 도로가 있는 도시에서,
(0, 0) -> (x, y)로 이동한다.
도로를 따라 한 칸 이동하는 시간은 w,
블록을 가로질러 대각선으로 이동하는 시간은 s.

최소 시간은?

접근법: 계산?
1. 대각선으로 가로지르는 것이 얼마나 효율적인지 판단한다.
2. 굉장히 효율적인 경우(s < w) 최대한 대각선으로만 간다.
  경우에 따라 마지막 한 번은 반드시 길을 따라 가야 할 수도 있다.
2. 적당히 효율적인 경우(s < 2*w) 되도록 대각선으로 가되,
  마지막에 수직/수평 경로가 남은 경우 길을 따라 간다.
3. 그렇지 않은 경우(s >= 2*w) 무조건 길을 따라 간다.
*/

#include <iostream>

int main() {
  unsigned long long x, y, w, s;
  std::cin >> x >> y >> w >> s;

  unsigned long long result = 0;
  if (s < w) {
    if (x > y) std::swap(x, y);
    y -= x;
    result += x * s;
    if (y & 1) {
      result += w;
      --y;
    }
    result += y * s;
  } else if (s < 2 * w) {
    if (x > y) std::swap(x, y);
    y -= x;
    result += x * s + y * w;
  } else {
    result += w * (x + y);
  }

  std::cout << result << std::endl;
}
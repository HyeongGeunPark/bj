/*
bj2012 등수 매기기

N명의 사람이 각각 한 개의 수를 제출한다.
N명의 사람에게 중복되지 않게 한 수를 배정한다.
제출한 수와 배정된 수의 차이(절대값)의 총합을 최소로 하려 한다.
그 값을 출력하라.

N < 500,000

접근법: 정렬? 그리디?
1. 입력을 정렬한다.
2. 정렬된 순서대로 1, 2,...의 수를 배정한다고 치고 입력과 배정된 수의 차이를
  전부 더한다.

주의
1. c++의 경우 입력 시간에 주의한다. (tie, sync_with_stdio)

개선?
1. 입력 범위가 메모리 안에 들어가므로 카운트 정렬을 시도할 수 있다.

*/

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;

  std::vector<int> rank(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> rank[i];
  }

  std::ranges::sort(rank);

  long long result = 0;
  for (int i = 0; i < n; ++i) {
    result += std::abs(i + 1 - rank[i]);
  }

  std::cout << result << std::endl;
}
/*
bj13334 철로
길이 d의 모든 철로 L에 대하여, 집과 사무실의 위치가 모두
L에 포함되는 사람들의 최대 수를 구하는 프로그램을 작성하시오.
집과 사무실은 직선 위에 위치한다.

사람 수 n <= 100'000
집과 사무실의 위치
-100'000'000 <= h, o <= 100'000'000
철로 길이 d <= 200'000'000

접근
1. 한 사람당 두 개의 위치는 정렬하여 저장한다.
2. 오른쪽 위치 기준으로 정렬한다.
3. 다음을 반복한다.
  1. 첫 번째 사람의 우측 위치(r)를 알아낸다.
  2. 첫 번째 사람의 왼쪽 위치를 우선순위 큐로 옮긴다.
    좌측, 우측 위치가 d보다 긴 사람은 고려하지 않아도 된다.
  3. 우선순위 큐에서 r-d보다 작은 모든 값을 제거한다.
  4. 우선순위 큐의 크기를 저장한다.

시간복잡도 = n * log(n)
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

int main(void) {
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);
  int n, d;
  std::cin >> n;
  std::vector<std::pair<int, int>> positions;
  // input
  positions.reserve(n);
  for (int i = 0; i < n; ++i) {
    int a, b;
    std::cin >> a >> b;
    if (a > b) std::swap(a, b);
    positions.push_back({a, b});
  }
  std::cin >> d;
  // sort
  std::ranges::sort(positions, {}, &std::pair<int, int>::second);
  // solve
  int result = 0;
  std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
  int idx = 0;
  while (idx != n) {
    auto [l, r] = positions[idx++];
    if ((r - l) > d) continue;
    pq.push(l);
    while (pq.size() && pq.top() < (r - d)) pq.pop();
    result = std::max(result, static_cast<int>(pq.size()));
  }

  std::cout << result;
}
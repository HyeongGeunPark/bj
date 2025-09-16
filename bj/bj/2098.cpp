/*

bj2098 외판원 순회

주어진 그래프에서 최소 비용의 순회를 구하는 문제.

입력: 인접 행렬로 나타낸 그래프 (2<= V <=16)
  비용이 0인 경우는 연결되지 않음.

접근법: 다이나믹 프로그래밍
 TSP 문제는 다이나믹 프로그래밍의 대표적인 응용이다.

0에서 시작해 0으로 돌아오는 최단 경로의 길이를 찾아야 한다.
1. 상태 정의
  DP[n][i]는, 현재 도시 n, 지금까지 방문한 도시의 비트마스크 i에 대해서,
    n에서 출발해 나머지 도시를 들러 0으로 돌아가는 최단 경로의 길이.

2. 기저 조건
  DP[n][1<<16-1] = e(n, 0)

3. 최적 구조
  DP[n][i] =
    min{ DP[next][i & (1<<n)] + e(n, next) }
      next는 지금까지 방문하지 않은 도시.


전체 문제의 해는 DP[0][1<<0]이다.
*/

#include <bit>
#include <iostream>
#include <vector>

int N;
constexpr int INF = 1'000'000'000;
int FULL;
std::vector<std::vector<int>> DP(16, std::vector<int>(1 << 16, -1));
int e[16][16];

int solve(int n, int bitmask) {
  // base case
  if (bitmask == FULL) {
    if (e[n][0] == 0) return INF;
    return e[n][0];
  }

  // memoization
  if (DP[n][bitmask] != -1) return DP[n][bitmask];

  // DP
  DP[n][bitmask] = INF;
  for (int i = 0; i < N; ++i) {
    if (bitmask & (1 << i)) continue;
    if (e[n][i] == 0) continue;
    int temp = solve(i, bitmask | (1 << i));
    if (temp == INF) continue;
    DP[n][bitmask] = std::min(DP[n][bitmask], temp + e[n][i]);
  }
  return DP[n][bitmask];
}

int main(void) {
  std::cin >> N;
  FULL = (1 << N) - 1;

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      std::cin >> e[i][j];
    }
  }

  std::cout << solve(0, 1);
}
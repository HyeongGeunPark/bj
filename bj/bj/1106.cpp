/*
bj1106 호텔

입력 인자 조건
c: 늘리고 싶은 최소 고객 수
n: 도시의 수
buf[i][0]: 도시 i의 1회 홍보 비용
buf[i][1]: 도시 i의 1회 홍보로 얻을 수 있는 고객 수

1 <= c <= 1000
1 <= n <= 20
1 <= buf[i][0], buf[i][1] <= 100

입력이 상당히 작으므로, 어떤 방법으로 풀어도 풀리기는 할 것이다.

dp를 사용한다.
1. c가 작은 편이므로, 고객 수를 인덱스로 하는 것이 좋아 보인다.
index = 고객 수
dp[i] = i명의 고객을 얻기 위한 최소 비용

2. 우선, 적당히 큰 값으로 dp를 초기화한다. (i=0, 1, ..., c + 100)

3. dp[0] = 0
dp[i] = min(dp[i], dp[i - buf[j][1]] + buf[j][0]) (j = 0, 1, ..., n-1)

4. index [c, c+100]에 대해서 dp[i]의 최솟값을 구한다.


*/

#include <functional>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main(void) {
  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);

  // input
  int c, n;

  std::cin >> c >> n;

  auto buf = new int[n][2];

  for (int i = 0; i < n; ++i) {
    std::cin >> buf[i][0] >> buf[i][1];
  }

  // process
  std::vector<int> dp(c + 101, 100 * 1000 + 1);

  dp[0] = 0;  // 0명의 고객을 얻기 위한 비용은 0
  for (int i = 1; i <= c + 100; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i - buf[j][1] < 0)  // index 범위를 벗어나는 경우
        continue;
      dp[i] = std::min(dp[i], dp[i - buf[j][1]] + buf[j][0]);
    }
  }

  int result =
      std::reduce(dp.begin() + c, dp.end(), std::numeric_limits<int>::max(),
                  [](int a, int b) { return std::min(a, b); });

  // output
  std::cout << result << '\n';

  // Delete allocated memory
  delete[] buf;
}
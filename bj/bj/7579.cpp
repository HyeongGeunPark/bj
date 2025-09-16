/*

bj7579 앱

일정 메모리 이상을 확보할 수 있는 조합 중 비활성화 비용이 최소인 것을 구한다.

접근법 : DP, 배낭 문제

상태: 앱 * 비용 -> 최대 100 * 10000

F(n, c) == 0~n번까지의 앱을 고려했을 때 비용 c까지 사용하여 확보할 수 있는 최대
메모리
*/

#include <cstring>
#include <iostream>
#include <vector>

struct proc {
  int cost, mem;
};

int dp[2][10001];

int main() {
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);

  int n, m;
  int minimum_cost = 0;
  std::cin >> n >> m;

  std::vector<proc> procs(n + 1);
  for (int i = 0; i < n; ++i) {
    std::cin >> procs[i].mem;
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> procs[i].cost;
    minimum_cost += procs[i].cost;
  }

  // dp

  auto prev = dp[0];
  auto current = dp[1];

  for (int i = 0; i < n; ++i) {
    std::memset(current, 0, sizeof(int) * (minimum_cost + 1));
    for (int j = 0; j < minimum_cost; ++j) {
      if (procs[i].cost <= j) {
        current[j] =
            std::max(current[j], prev[j - procs[i].cost] + procs[i].mem);
      }
      current[j] = std::max(current[j], prev[j]);
      if (current[j] >= m) {
        minimum_cost = std::min(minimum_cost, j);
      }
    }
    std::swap(current, prev);
  }

  std::cout << minimum_cost;
}
/*

bj1005 ACM Craft

접근법: dp

F(n)을 n번 건물을 짓는데 필요한 최소 시간이라고 하자.
n번 건물의 prerequisite p1, p2, ..., pk에 대해서,
F(n) = max(F(p1), F(p2), ..., F(pk)) + cost(n)이다.
메모이제이션을 사용하면서 재귀적으로 풀면 될 듯 하다.

*/

#include <iostream>
#include <vector>

int solve(int w, std::vector<std::vector<int>>& rule, std::vector<int>& cost) {
  int temp = 0;
  while (rule[w].size()) {
    temp = std::max(temp, solve(rule[w].back(), rule, cost));
    rule[w].pop_back();
  }
  cost[w] += temp;
  return cost[w];
}

int main(void) {
  // cpp simple fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);

  int t;
  std::cin >> t;
  for (int i = 0; i < t; ++i) {
    int n, k;
    std::cin >> n >> k;
    std::vector<std::vector<int>> rule(n + 1);
    std::vector<int> cost(n + 1);

    for (int j = 1; j <= n; ++j) {
      std::cin >> cost[j];
    }
    for (int j = 0; j < k; ++j) {
      int p, d;
      std::cin >> p >> d;
      rule[d].push_back(p);
    }

    int w;
    std::cin >> w;
    std::cout << solve(w, rule, cost) << '\n';
  }
}
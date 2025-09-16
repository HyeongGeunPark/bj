#include <algorithm>
#include <iostream>
#include <vector>

int main(void) {
  using ll = long long;
  int n;
  ll m;
  std::cin >> n >> m;

  std::vector<int> cost(n);
  for (int i = 0; i < n; ++i) std::cin >> cost[i];

  std::sort(cost.begin(), cost.end());

  std::vector<ll> sum(n + 1, 0);
  for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + cost[i - 1];

  ll l = 0, r = 1'000'000'001;
  ll mid;
  while (l < r) {
    mid = (l + r) / 2;

    ll total_subsidy = 0;
    auto xx = std::upper_bound(cost.begin(), cost.end(), mid);
    total_subsidy += sum[std::distance(cost.begin(), xx)];
    total_subsidy += mid * std::distance(xx, cost.end());

    if (total_subsidy > m)
      r = mid;
    else
      l = mid + 1;
  }
  if (r == 1'000'000'001)
    std::cout << "infinite";
  else
    std::cout << r - 1;
}
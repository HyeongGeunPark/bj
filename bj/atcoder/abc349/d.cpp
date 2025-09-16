#include <iostream>
#include <vector>

using ll = long long;

inline bool is_even(ll a) { return (a & 1) == 0; }
int main(void) {
  std::vector<ll> result_sq;

  ll l, r;
  std::cin >> l >> r;

  ll m = 0;

  ll cur = l;
  ll interval;
  while (true) {
    result_sq.push_back(cur);
    if (cur == r) break;
    interval = 1;
    ll temp = cur;
    while (true) {
      if (!is_even(temp)) break;
      temp >>= 1;
      interval <<= 1;
      if (cur + interval > r) {
        interval >>= 1;
        break;
      }
    }
    cur += interval;
  }

  std::cout << result_sq.size() - 1 << '\n';
  for (int i = 0; i < result_sq.size() - 1; ++i) {
    std::cout << result_sq[i] << ' ' << result_sq[i + 1] << '\n';
  }
}
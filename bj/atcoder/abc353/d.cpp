#include <iostream>
#include <vector>

using ll = unsigned long long;
constexpr ll MOD = 998244353;

int main(void) {
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);

  int n;
  std::cin >> n;

  ll result = 0;
  std::vector<ll> a(n);
  std::vector<ll> m(n + 1);
  m[0] = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    ll mm = 1;
    ll temp = a[i];
    while (temp) {
      temp /= 10;
      mm *= 10;
    }
    m[i + 1] = m[i] + mm;
  }

  for (int i = 0; i < n; ++i) {
    result += a[i] * ((m[n] - m[i + 1] + i) % MOD);
    result %= MOD;
  }

  std::cout << result;
}
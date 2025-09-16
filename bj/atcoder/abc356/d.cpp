#include <bit>
#include <iostream>

constexpr unsigned long long MOD = 998'244'353;

int main(void) {
  unsigned long long n, m;
  unsigned long long result = 0;
  unsigned long long one = 1;
  std::cin >> n >> m;
  result += std::popcount(n & m);
  unsigned long long upper_popcount = 0;
  for (int position = 59; position >= 0; --position) {
    unsigned long long mask = (one << position);
    if (n & mask) {
      result +=
          (unsigned long long)(std::popcount(m & ((one << position) - 1))) *
          (one << (position - 1));
      result %= MOD;
      result += upper_popcount * (one << position);
      result %= MOD;
      upper_popcount += std::popcount(m & mask);
    }
  }

  std::cout << result;
}
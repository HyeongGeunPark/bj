#include <iostream>
#include <unordered_map>

std::unordered_map<long long, int> memo;

constexpr int mod = 1'000'000'007;

int fib(long long n) {
  // fibonacci
  // F(2n+1) = F(n+1)^2 + F(n)^2
  // F(2n) = F(n) * ( F(n) + 2*F(n-1) )

  if (memo.count(n)) {
    // memo exists
    return memo[n];
  }

  int rval;

  if (n & 0x1) {
    // n is odd
    long long r1 = fib(n / 2 + 1);
    long long r2 = fib(n / 2);
    rval = static_cast<int>((r1 * r1 + r2 * r2) % mod);
  } else {
    // n is even
    long long r1 = fib(n / 2);
    long long r2 = fib(n / 2 - 1);
    rval = static_cast<int>((r1 * (r1 + 2 * r2)) % mod);
  }
  memo[n] = rval;
  return rval;
}

int main() {
  memo[0] = 0;
  memo[1] = 1;
  memo[2] = 1;
  memo[3] = 2;
  memo[4] = 3;
  memo[5] = 5;

  long long n;
  std::cin >> n;

  std::cout << fib(n) << '\n';
  return 0;
}

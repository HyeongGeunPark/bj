#include <iostream>
#include <vector>

void process(std::vector<unsigned int>& arr, unsigned int n) {
  unsigned int i = 0;
  while (n) {
    if (n & 1) {
      ++arr[i];
    }
    ++i;
    n >>= 1;
  }
}

int main(void) {
  unsigned int n;
  using ll = unsigned long long;
  std::cin >> n;
  std::vector<unsigned int> arr(n);
  std::vector<unsigned int> xored_sum(32, 0);
  std::vector<ll> result(32, 0);
  ll sum = 0;
  unsigned int temp = 0;
  for (unsigned int i = 0; i < n; ++i) {
    std::cin >> arr[i];
    temp ^= arr[i];
    process(xored_sum, temp);
    sum += arr[i];
  }
  for (unsigned int i = 0; i < 32; ++i) {
    result[i] += xored_sum[i];
  }
  for (unsigned int i = 0; i < n; ++i) {
    unsigned int nn = arr[i];
    unsigned int j = 0;
    while (nn) {
      if (nn & 1) {
        xored_sum[j] = n - xored_sum[j] + 1;
      }
      ++j;
      nn >>= 1;
    }
    for (unsigned int i = 0; i < 32; ++i) {
      result[i] += xored_sum[i];
    }
  }
  for (unsigned int i = 0; i < 32; ++i) {
    result[i] >>= 1;
  }
  ll total_result = 0;
  for (unsigned int i = 0; i < 32; ++i) {
    total_result += result[i] * ((ll)1 << i);
  }

  std::cout << total_result - sum;
}
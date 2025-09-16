#include <iostream>

int main(void) {
  int n, l, r;
  std::cin >> n >> l >> r;

  for (int i = 1; i < l; ++i) {
    std::cout << i << ' ';
  }
  for (int i = r; i >= l; --i) {
    std::cout << i << ' ';
  }
  for (int i = r + 1; i <= n; ++i) {
    std::cout << i << ' ';
  }
  return 0;
}
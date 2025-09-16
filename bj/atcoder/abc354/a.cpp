#include <iostream>

int main(void) {
  int l = 0;
  int h;
  std::cin >> h;
  for (int i = 1, inc = 1;; ++i, inc <<= 1) {
    l += inc;
    if (l > h) {
      std::cout << i;
      break;
    }
  }
}
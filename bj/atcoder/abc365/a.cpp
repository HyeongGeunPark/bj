#include <iostream>

int main(void) {
  int result = 365;
  int y;
  std::cin >> y;
  if (y % 4 == 0) result = 366;
  if (y % 100 == 0) result = 365;
  if (y % 400 == 0) result = 366;

  std::cout << result;
}
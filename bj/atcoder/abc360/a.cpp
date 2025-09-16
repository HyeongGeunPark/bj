#include <iostream>

int main(void) {
  std::string s;
  std::cin >> s;
  for (int i = 0; i < 3; ++i) {
    if (s[i] == 'R') {
      for (int j = i + 1; j < 3; ++j) {
        if (s[j] == 'M') {
          std::cout << "Yes";
          return 0;
        }
      }
    }
  }
  std::cout << "No";
  return 0;
}
#include <iostream>

int main(void) {
  std::string s;
  std::cin >> s;

  int l = 0;
  int r = s.size() - 1;
  while (l < r) {
    if (!std::isalpha(s[l])) {
      ++l;
      continue;
    }
    if (!std::isalpha(s[r])) {
      ++r;
      continue;
    }
    if (std::tolower(s[l]) != std::tolower(s[r])) {
      std::cout << "false\n";
      return 0;
    }
  }
  std::cout << "true\n";
  return 0;
}

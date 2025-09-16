#include <iostream>

int main(void) {
  std::string s, t;
  std::cin >> s;
  std::cin >> t;

  for (int w = 1; w < s.length(); ++w) {
    for (int c = 0; c < w; ++c) {
      std::string buf = "";
      for (int i = c; i < s.length(); i += w) {
        buf.push_back(s[i]);
      }
      if (buf == t) {
        std::cout << "Yes";
        return 0;
      }
    }
  }
  std::cout << "No";
  return 0;
}
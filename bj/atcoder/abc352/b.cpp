#include <iostream>

int main(void) {
  std::string s, t;
  std::cin >> s >> t;
  int s_index = 0;

  for (int t_index = 0; t_index < t.size(); ++t_index) {
    if (s[s_index] == t[t_index]) {
      s_index++;
      std::cout << t_index + 1 << ' ';
    }
  }
}
/*

bj9252 LCS
입력 길이 1000의 LCS 찾기

*/

#include <iostream>
#include <vector>

int mem[1001][1001];

int main() {
  std::vector<char> s1, s2;
  s1.reserve(1001);
  s2.reserve(1001);
  s1.push_back(0);
  s2.push_back(0);

  std::cin >> std::noskipws;
  for (char c; std::cin >> c;) {
    if (c == '\n') break;
    s1.emplace_back(c);
  }
  for (char c; std::cin >> c;) {
    if (c == '\n') break;
    s2.emplace_back(c);
  }

  // LCS finding
  for (int i = 1; i < s1.size(); ++i) {
    for (int j = 1; j < s2.size(); ++j) {
      if (s1[i] == s2[j])
        mem[i][j] = mem[i - 1][j - 1] + 1;
      else
        mem[i][j] = std::max(mem[i - 1][j], mem[i][j - 1]);
    }
  }

  std::vector<char> result;
  std::cout << mem[s1.size() - 1][s2.size() - 1] << '\n';

  // LCS string finding
  for (int i = s1.size() - 1, j = s2.size() - 1; mem[i][j] != 0;) {
    if (mem[i][j] == mem[i - 1][j]) {
      --i;
      continue;
    }
    if (mem[i][j] == mem[i][j - 1]) {
      --j;
      continue;
    }
    result.push_back(s1[i]);
    --i;
    --j;
  }

  for (auto i = result.rbegin(); i != result.rend(); ++i) {
    std::cout << *i;
  }
}
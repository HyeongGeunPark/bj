/*
bj30805 사전 순 최대 공통 부분 수열

사전순으로 가장 나중인 공통 부분 수열을 구하라.

다음을 반복한다.
1. 두 수열에 공통되는 원소 중 가장 큰 것을 구한다.
  1-1. 가장 큰 것이 여러 개 있다면, 가장 처음에 나오는 것을 고른다.
2. 그 원소 이후에 남은 수열에 대해 1을 반복한다.

*/

#include <iostream>
#include <vector>

int main(void) {
  int an, bn;
  std::cin >> an;
  std::vector<int> a(an);
  for (auto& i : a) std::cin >> i;
  std::cin >> bn;
  std::vector<int> b(bn);
  for (auto& i : b) std::cin >> i;

  std::vector<std::vector<int>> mem(an + 1, std::vector<int>(bn + 1));
  for (int i = an - 1; i >= 0; --i) {
    for (int j = bn - 1; j >= 0; --j) {
      mem[i][j] = std::max(mem[i + 1][j], mem[i][j + 1]);
      if (a[i] == b[j]) {
        mem[i][j] = std::max(mem[i][j], a[i]);
      }
    }
  }

  std::vector<int> result;
  int i = 0, j = 0;
  while (i < an && j < bn) {
    if (mem[i][j] == 0) break;
    result.push_back(mem[i][j]);
    while (a[i] != result.back()) ++i;
    while (b[j] != result.back()) ++j;
    ++i, ++j;
  }

  std::cout << result.size() << '\n';
  for (auto i : result) std::cout << i << ' ';
}
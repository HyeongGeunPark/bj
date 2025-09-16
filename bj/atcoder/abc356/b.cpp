#include <iostream>
#include <vector>

int main(void) {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> nut(m, 0);
  std::vector<int> goal(m, 0);
  for (int i = 0; i < m; ++i) {
    std::cin >> goal[i];
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int temp;
      std::cin >> temp;
      nut[j] += temp;
    }
  }
  for (int i = 0; i < m; ++i) {
    if (nut[i] < goal[i]) {
      std::cout << "No";
      return 0;
    }
  }
  std::cout << "Yes";
  return 0;
}
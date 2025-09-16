#include <bit>
#include <iostream>
#include <vector>

int main(void) {
  int n, m, k;
  std::cin >> n >> m >> k;
  int mask = (1 << n) - 1;
  std::vector<unsigned int> tests(m);
  std::vector<bool> test_result(m);

  for (int i = 0; i < m; ++i) {
    int c;
    std::cin >> c;
    unsigned int key_combination = 0;
    for (int j = 0; j < c; ++j) {
      int key_number;
      std::cin >> key_number;
      key_combination |= (1 << (key_number - 1));
    }
    char r;
    std::cin >> r;
    if (r == 'x') {
      test_result[i] = false;
    } else {
      test_result[i] = true;
    }
    tests[i] = key_combination;
  }

  int result = 0;
  for (int i = 0; i <= mask; ++i) {
    bool test_success = true;
    for (int j = 0; j < m; ++j) {
      if (((std::popcount((i & tests[j])) >= k)) != test_result[j]) {
        test_success = false;
        break;
      }
    }
    if (test_success == false) continue;
    ++result;
  }

  std::cout << result;

  return 0;
}
#include <algorithm>
#include <iostream>
#include <vector>

int main(void) {
  int n, m;
  std::cin >> n >> m;

  std::vector<int> a(n);
  std::vector<int> b(m);

  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }

  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());

  int ia = 0, ib = 0;
  int prev = -1, cur;
  while (ia != n && ib != m) {
    if (ia == n) {
      ++ib;
      cur = 0;
    } else if (ib == m) {
      ++ia;
      cur = 1;
    } else if (a[ia] < b[ib]) {
      ++ia;
      cur = 1;
    } else {
      ++ib;
      cur = 0;
    }

    if (prev == 1 && cur == 1) {
      std::cout << "Yes";
      return 0;
    }
    prev = cur;
  }
  std::cout << "No";
}
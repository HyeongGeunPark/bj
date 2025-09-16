#include <algorithm>
#include <iostream>
#include <vector>

int main(void) {
  int n;
  std::cin >> n;

  std::vector<int> arr(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }

  std::vector<int> arr2{arr};
  std::sort(arr.begin(), arr.end(), std::greater{});

  auto second = std::find(arr2.begin(), arr2.end(), arr[1]);

  std::cout << std::distance(arr2.begin(), second) + 1;
}
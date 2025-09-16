/*

c++ stl map/reduce -> transform, reduce (in <algorithm>)



*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

void transform_test(std::vector<int> S) {
  std::vector<int> Tr;
  std::cout << "map test\n";
  std::cout << "input arr, S: ";
  for (auto i : S) std::cout << i << ' ';
  std::cout << '\n';

  // std::transform (in <algorithm>)
  std::transform(S.begin(), S.end(), std::back_inserter(Tr),
                 [](int x) { return std::pow(x, 2.0); });

  std::cout << "std::transform(), Tr: ";
  for (auto i : Tr) std::cout << i << ' ';
  std::cout << '\n';

  // std::for_each (in <algorithm>)
  std::for_each(S.begin(), S.end(), [](int& x) { x = std::pow(x, 2.0); });

  std::cout << "std::for_each(), Tr: ";
  for (auto i : S) std::cout << i << ' ';
  std::cout << '\n';
}

void reduce_test(std::vector<int> S) {
  std::cout << "\n reduce test\n";
  std::cout << "input arr, S: ";
  for (auto i : S) std::cout << i << ' ';
  std::cout << '\n';

  // std::reduce()
  auto ans = std::reduce(S.begin(), S.end(), 0,
                         [](int acc, int x) { return acc + x; });
  std::cout << "std::reduce(), ans: " << ans << '\n';
}

int main(void) {
  std::vector<int> S{1, 10, 4, 7, 3, 5, 6, 9, 8, 2};

  transform_test(S);

  reduce_test(S);
}
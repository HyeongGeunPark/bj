#include <algorithm>
#include <compare>
#include <iostream>
#include <iterator>
#include <vector>

template <typename T>
std::vector<T>::iterator binary_search(T N, std::vector<T>& S) {
  auto first = S.begin();
  auto last = S.end();

  while (true) {
    auto range_length = (std::distance(first, last));
    auto mid_element_iter = first + range_length / 2;
    auto mid_element = *mid_element_iter;

    if (mid_element == N) {
      return mid_element_iter;
    } else if (mid_element > N) {
      last = mid_element_iter;
    } else if (mid_element < N) {
      first = mid_element_iter;
    }
    if (range_length == 1) {
      return S.end();
    }
  }
}

struct Student {
  std::pair<int, int> name;
  bool vaccinated;

  auto operator<=>(const Student& other) const { return name <=> other.name; }
  auto operator==(const Student& other) const { return name == other.name; }
};

int main(void) {
  std::vector<Student> data = {
      {{1, 1}, true}, {{1, 2}, false}, {{3, 2}, true}, {{2, 6}, false}};

  std::sort(data.begin(), data.end());

  while (true) {
    std::pair<int, int> query;
    std::cin >> query.first >> query.second;

    if (query == std::make_pair(0, 0)) break;

    auto iter = binary_search(Student{query, false}, data);
    if (iter == data.end() || iter->vaccinated == false) {
      std::cout << "접종 대상입니다\n";
    } else {
      std::cout << "접종 대상이 아닙니다\n";
    }
  }
}
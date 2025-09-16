/*
bj2568 전깃줄-2
전주 a, b에 전깃줄이 걸려 있다.
모든 전깃줄이 교차하지 않게 하기 위해 최소 갯수의 전깃줄을 없앤다고 할 때,
그 갯수와 없애야 하는 전깃줄 구하기.

접근: 가장 긴 증가하는 부분 수열
남아있는 전깃줄에 대해, A전주 위치로 정렬하면
B 전주 위치는 단조 증가해야 한다.
전깃줄의 갯수가 100'000개이므로, nlog(n)의 알고리즘을 사용해야 함.
*/

#include <algorithm>
#include <iostream>
#include <vector>

struct line {
  int a, b;
  auto operator<(const line& other) const { return a < other.a; }
};

#define cpp_fast_io() \
  std::cin.tie(0);    \
  std::ios_base::sync_with_stdio(false)

int main(void) {
  cpp_fast_io();
  int n;
  std::cin >> n;
  std::vector<line> lines(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> lines[i].a >> lines[i].b;
  }
  std::sort(lines.begin(), lines.end());
  std::vector<int> mem, idx;
  mem.push_back(lines[0].b);
  idx.push_back(0);
  for (int i = 1; i < n; ++i) {
    if (mem.back() < lines[i].b) {
      idx.push_back(mem.size());
      mem.push_back(lines[i].b);
    } else {
      auto iter = std::lower_bound(mem.begin(), mem.end(), lines[i].b);
      int len = std::distance(mem.begin(), iter);
      *iter = lines[i].b;
      idx.push_back(len);
    }
  }

  std::cout << n - mem.size() << '\n';

  int j = mem.size() - 1;
  std::vector<int> erase;
  for (int i = n - 1; i >= 0; --i) {
    if (idx[i] == j) {
      --j;
    } else {
      erase.push_back(lines[i].a);
    }
  }
  for (auto iter = erase.rbegin(); iter != erase.rend(); ++iter) {
    std::cout << *iter << '\n';
  }
}
/*
bj14003 가장 긴 증가하는 부분 수열 5

수열 A가 주어졌을 때, 가장 긴 증가하는 부분 수열을 구하는 프로그램을 작성하시오.
n <= 1'000'000.
가장 긴 증가하는 부분 수열의 길이와 원소를 출력한다.

접근법: nlog(n) LIS 알고리즘.
특이 사항은 없다.
*/

#include <algorithm>
#include <iostream>
#include <vector>

int main(void) {
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);
  int n;
  std::cin >> n;
  std::vector<int> seq(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> seq[i];
  }

  std::vector<int> mem{seq[0]};
  std::vector<int> idx{0};

  for (int i = 1; i < n; ++i) {
    if (mem.back() < seq[i]) {
      idx.push_back(mem.size());
      mem.push_back(seq[i]);
    } else {
      int ii = std::lower_bound(mem.begin(), mem.end(), seq[i]) - mem.begin();
      mem[ii] = std::min(mem[ii], seq[i]);
      idx.push_back(ii);
    }
  }

  std::vector<int> ans;
  int j = mem.size() - 1;
  for (int i = n - 1; i >= 0; --i) {
    if (j == idx[i]) {
      ans.push_back(seq[i]);
      --j;
    }
  }

  std::cout << ans.size() << '\n';
  for (auto iter = ans.rbegin(); iter != ans.rend(); ++iter) {
    std::cout << *iter << ' ';
  }
}
/*

bj12015 가장 긴 증가하는 부분 수열 2

수열의 크기가 1'000'000으로 늘어났다.
기존의 n^2 알고리즘으로는 불가능하다.

접근법: 이분탐색

1. 입력을 하나씩 받는다.
2. 새로 받은 입력이 vector의 마지막 원소보다 같거나 작은 경우,
  지금까지 받은 입력 중 새로 받은 입력보다 같거나 큰 것 중 가장 작은 것(lower
bound)을 새로 받은 입력으로 대체한다.
3. 그렇지 않을 경우 벡터 마지막에 새로 받은 입력을 추가한다.
4. 마지막 입력까지 반복한다.

vector[i] = 길이 i의 증가하는 부분 수열이 가질 수 있는 가장 작은 마지막 원소의
값



*/

#include <algorithm>
#include <iostream>
#include <vector>

int main(void) {
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);

  int n, temp;
  std::cin >> n;
  std::vector<int> lis;
  std::cin >> temp;
  lis.push_back(temp);
  for (int i = 1; i < n; ++i) {
    std::cin >> temp;

    if (temp <= lis.back()) {
      *std::lower_bound(lis.begin(), lis.end(), temp) = temp;
    } else {
      lis.push_back(temp);
    }
  }

  std::cout << lis.size();
}
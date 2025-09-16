/*
bj5585 거스름돈

1000엔 미만의 물건을 1000엔을 주고 샀을 때,
가장 적은 수의 동전으로 거스름돈을 받는다.
500엔, 100엔, 10엔, 5엔, 1엔이 충분히 많이 있을 때,
동전의 개수는?

접근법: 그리디
거슬러 줄 돈을 넘지 않는 선에서, 가장 큰 동전부터 선택하여
금액을 채우면 된다.
*/

#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;

  n = 1000 - n;

  std::vector<int> coin_values = {500, 100, 50, 10, 5, 1};
  int count = 0;
  for (unsigned int i = 0; i < coin_values.size(); ++i) {
    while (n >= coin_values[i]) {
      ++count;
      n -= coin_values[i];
    }
  }
  std::cout << count << std::endl;
}
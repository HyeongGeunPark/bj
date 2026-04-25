/*
bj19709 lunchbox

n개의 런치박스가 있다.
m개의 학교가 있고, i번째 학교는 k_i개의 런치박스를 주문한다.

가장 많은 학교에 런치박스를 주려고 한다.
하지만 각 학교에는 주문한 모든 런치박스를 주거나, 하나도 주지 않거나
둘 중 하나만 해야 한다.

런치박스를 받을 수 있는 학교의 최대 수를 구하는 프로그램을 만들어라.


입력
N:런치박스 수:[?,?]
M:학교 수:[?,?]
k_i:각 학교가 주문한 런치박스 수:[?,?]

접근: 그리디
가장 적은 런치박스를 주문한 학교부터 선택해 나가면 된다.


*/

#include <iostream>
#include <algorithm>
#include <vector>

int main(void) {
  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);

  using ull = unsigned long long;

  ull n, m;
  std::cin >> n >> m;

  std::vector<ull> k(m);

  for (int i = 0;i < m;++i) {
    std::cin >> k[i];
  }


  std::sort(k.begin(), k.end());

  int count = -1;
  for (int i = 0;i < m;i++) {
    if (n >= k[i]) {
      n -= k[i];
    }
    else {
      count = i;
      break;
    }
  }
  if (count == -1) {
    std::cout << m;
  }
  else {
    std::cout << count;
  }

  return 0;

}
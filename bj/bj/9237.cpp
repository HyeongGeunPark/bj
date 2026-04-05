/*
9237 이장님 초대

하루에 묘목 1개를 심을 수 있다.
묘목이 언제 다 자라는지 알고 있다.
묘목이 다 자란 다음 날 이장님을 부른다.
묘목을 심는 순서를 잘 조절하여 이장님을 최대한 빨리 부르려고 한다.
이장님을 며칠에 초대할 수 있을까?

접근: 그리디
자라는 데 오래 걸리는 나무부터 심는다.

*/

#include <iostream>
#include <vector>
#include <algorithm>
//#include <ranges>

int main(void) {
  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);

  // input
  int n;
  std::cin >> n;
  std::vector<int> time;

  time.reserve(n);
  for(int i=0;i<n;++i){
    int temp;
    std::cin >> temp;
    time.push_back(temp);
  }

  std::sort(time.begin(), time.end(), std::greater<int>());

  // test
  /*
  for (auto i : time) {
    std::cout << i << ' ';
  }
  */

  int current_day = 1;
  int finish_day = 0;
  for (auto t : time) {
    finish_day = std::max(finish_day, current_day + t);
    ++current_day;
  }


  std::cout << finish_day + 1 << '\n';
  return 0;
}
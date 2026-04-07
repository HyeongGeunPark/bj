/*
bj10431 줄세우기

20명의 아이를 키 순으로 줄세운다.
아이들의 키는 모두 다르다.

각 테스트 케이스마다
아이들을 '삽입정렬'했을 때, 위치 변경이 몇 번 발생하느냐를 구한다.

1 <= P <= 1000 (테스트 케이스의 수)


접근 1: 시뮬레이션
직접 삽입정렬을 하여 몇 번 위치 변경이 일어나느냐를 구한다.

접근 2: '순서 바꾸기 수' 계산
임의의 원소에 대해, 그 원소는 그 원소 앞에 있는 원소들 중
그 원소보다 큰 원소의 갯수만큼 '순서 바꾸기'를 한다.
set을 사용해 시간복잡도를 줄일 수 있으나 n=20이라 안 하는게 낫다.

*/

#include <iostream>
#include <vector>
#include <algorithm>


int main(void) {
  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);

  int p;
  std::cin >> p;

  for (int i = 0; i < p; ++i) {
    int n;
    std::cin >> n;

    std::vector<int> v(20);
    for(int j=0;j<20;++j){
      std::cin >> v[j];
    }

    int count = 0;
    for(int j=0;j<20;++j){
      for(int k=j+1; k<20; ++k){
        if(v[j] > v[k]){
          ++count;
        }
      }
    }

    std::cout << n << ' ' << count << '\n';
  }
  return 0;
}

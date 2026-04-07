/*
bj8979 올림픽

각국의 금, 은, 동메달 수를 입력받아 어느 국가가 몇 등을 했는지 알아보자.

다음 규칙에 따라 어느 나라가 더 잘했는지 결정한다.
1. 금메달이 더 많은 국가
2. 금메달 수가 같다면, 은메달 수가 더 많은 나라
3. 금, 은메달 수가 모두 같으면, 동메달 수가 더 많은 나라

한 국가의 등수는 (자신보다 더 잘한 나라 수) + 1로 정의된다.
즉, 동일한 메달을 가진 국가는 등수가 서로 같다.


N: 국가 수: [1,1000]
K: 등수를 알고 싶은 국가: [1,N]

전체 메달 수의 총합은 1'000'000 이하이다.

접근: 숫자 세기

일단 모두 입력을 받는다.
국가 k보다 좋은 성적을 받은 국가의 수를 센다.

단, 비교를 할 때 약간 구현이 귀찮은데,
전체 메달 수의 총합이 1'000'000 ( < 2^20 ) 이하라는 것을 이용하여 회피할 수 있다.
금메달 갯수에 <<40, 은메달 갯수에 <<20, 동메달 갯수는 <<0하여 그냥 세 수를 더해
64비트 정수형으로 만들면 된다.
*/

#include <iostream>
#include <vector>

int main(void){
  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);

  int n, k;
  std::cin >> n >> k;

  std::vector<unsigned long long> v(n);
  unsigned long long target = -1;
  for(int i=0;i<n;++i){
    int kk;
    std::cin >> kk;
    unsigned long long point = 0;
    for(int j=0;j<3;++j){
      unsigned long long temp;
      std::cin >> temp;
      point <<= 20;
      point += temp;
    }
    v[i] = point;
    if(kk == k){
      target = point;
    }
  }

  int count = 0;
  for(auto x : v){
    if(x > target) ++count;
  }

  std::cout << count + 1;
  return 0;
}


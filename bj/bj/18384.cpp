/*
bj18384 prim

5개 정수를 받는다.
각 정수마다, 그 정수보다 작지 않은 가장 작은 소수를 구하여라.

그 소수들을 더해서 출력하라.

l: 원소 : (0,1000'000)
n: test case의 수? : (0,1000'000)

접근: 소수 찾기 + 이진 탐색

1. 일단 1~1010'000 범위에서 모든 소수를 찾는다.
2. 이진 탐색으로 각 원소보다 작지 않은 가장 작은 소수를 찾는다.


*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int main(void){
  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);

  // test case number
  int n;
  std::cin>>n;

  // find all primes

  std::vector<int> primes;
  std::vector<bool> is_prime(1010000, true);

  is_prime[0] = false;
  is_prime[1] = false;
  int square_root = static_cast<int>(std::ceil(std::sqrt(1010000.0L)));

  primes.push_back(2);
  for(int i=4; i<101000; i+=2){
    is_prime[i] = false;
  }
  for(int i=3; i<square_root; i+=2){
    if(is_prime[i] == false){
      continue;
    }
    for(int j=i*2; j<101000; j+=i){
      is_prime[j] = false;
    }
  }
  for(int i=2; i<101000; ++i){
    if(is_prime[i]){
      primes.push_back(i);
    }
  }

  while(n--){
    int sum = 0;
    for(int i=0; i<5; ++i){
      // input
      int temp;
      std::cin>>temp;

      // binary search
      auto it = std::lower_bound(primes.begin(), primes.end(), temp);

      sum += *it;
    }
    std::cout<<sum<<'\n';
  }

  return 0;
}

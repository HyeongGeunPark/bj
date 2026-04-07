/*

bj20922 겹치는 건 싫어

주어진 수열에서, 같은 원소가 K개 이하 들어 있는 최장 연속 부분 수열의
길이를 구하라.

N: 수열 길이: [1, 200'000]
K: 용납 가능한 같은 원소의 수: [1,100]
a_n: 수열의 원소: [1, 100'000];

접근: 슬라이딩 윈도우

첫 원소부터 시작해서 원소의 숫자를 세면서 우측 포인터를 이동한다.
어떤 원소가 k개 상이 되는 순간, 그 원소가 나올 때 까지 왼쪽 포인터를 이동한다.
*/

#include <iostream>
#include <vector>

int main(void) {
  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);

  // input
  int n, k;
  std::cin >> n >> k;
  std::vector<int> v(n);
  for(int i=0;i<n;++i){
    std::cin >> v[i];
  }

// sliding window
  int max_len = 0;
  int left = 0, right = 0;

  std::vector<int> counts(100001, 0);

  while(true){
    if(right == n) break;

    if(counts[v[right]] < k){
      ++counts[v[right]];
      ++right;
    }
    else{
      while(true){
        --counts[v[left]];
        ++left;
        if(counts[v[right]] < k) break;
      }
    }
    max_len = std::max(max_len, right - left);
  }

  std::cout << max_len;
}

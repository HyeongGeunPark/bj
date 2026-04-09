/*
bj11722 가장 긴 감소하는 부분 수열


수열 A가 주어졌을떄 가장 긴 감소하는 부분 수열을 구하는 프로그램을
작성하시오.

e.g.)
  A = {10, 30, 10, 20, 10}
  ->       30      20  10
  길이는 3

N:수열의 길이:[1,1000]
A_i:수열의 원소:[1,1000]

가장 긴 감소하는 부분 수열의 길이만 출력하면 된다.

접근 : DP
mem[i-1] = 길이 (i)의 감소하는 부분 수열이 가질 수 있는 마지막값 중 제일 큰 것

수열을 첫 번째 원소부터 훑으면서 mem을 업데이트해 나간다.

어떤 원소를 훑을 때,
1) 그 원소가 mem의 가장 마지막 원소보다 작은 경우
mem의 정의에 의해, mem의 가장 마지막 원소는 현재까지 고려한 수열의 부분에서
가장 긴 감소하는 부분 수열의 가장 마지막 값이다.
그런 경우, 그 원소를 mem의 마지막에 덧붙이면 된다.
(새로운 '가장 긴 감소하는 부분수열' 찾음)

2) 아닌 경우
mem을 이용해서, 이 원소를 덧붙일 수 있는 가장 긴 길이의
'감소하는 부분 수열'을 찾는다.

예) mem = {40, 30, 20, 10}일 때, 새로 훑는 원소가 25인 경우
  이 원소는 길이 2의 30으로 끝나는 '감소하는 부분 수열'의 뒤에 붙여서
  길이 3의 25로 끝나는 '감소하는 부분 수열'을 만들 수 있다.
  따라서 mem = {40, 30, 25, 10}으로 업데이트한다.

mem이 항상 강한 단조 감소한다는 것을 이용해 lower_bound (binary search)를
사용할 수 있다.




*/

#include <iostream>
#include <vector>
#include <algorithm>

int main(void) {
  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);


  // input
  int n;
  std::cin >> n;

  std::vector<int> a(n);

  for (int i = 0;i < n;++i) {
    std::cin>>a[i];
  }


  std::vector<int> mem;

  mem.push_back(a[0]);
  int len = 0;
  for (int i = 1;i < n;++i) {
    if (a[i] < mem.back()) {
      mem.push_back(a[i]);
    }
    else {
      auto it = std::lower_bound(mem.begin(), mem.end(), a[i], std::greater<int>());
      *it = a[i];
    }
  }



  std::cout << mem.size();


  return 0;
}




/*
bj 31247 - 2024는 무엇이 특별할까?

t_o(n) = n의 약수이면서 홀수인 양의 정수의 갯수
t_e(n) = n의 약수이면서 짝수인 양의 정수의 갯수

t_e(x) = K * t_o(x)인 경우,
양의 정수 x는 K-특별한 수라고 정의한다.

양의 정수 N과 음이 아닌 정수 K가 주어진다.

각 테스트 케이스마다
N 이하의 양의 정수 중 K-특별한 수의 개수를 출력하라.

1<=T<=100'000
1<=N<=1'000'000'000'000'000'000
1<=K<=1'000'000'000'000'000'000

접근 : 약수의 갯수 구하기
1. n을 2로 계속 나눈다. 이를 통해 소인수 2의 차수를 구한다.
2. 짝수 약수는 2의 배수이다.
3. 따라서 K는 2의 차수와 같다.
  예) 2024 = 2^3 * 11 * 23, K=3
        1 11  23  253 <- 홀수 약수
        2 22  46  506   <- 짝수 약수들
        4 44  92  1012
        8 88  184 2024
4. N 이하의 양의 정수 중 K-특별한 수를 찾으려면 반대로 생각하면 된다.
5. N 이하의 양의 정수 중 소인수 2를 K개 가지는 수를 찾으면 된다.
6. 그러면 N을 2^N으로 나눈 뒤, N을 2^(N+1)로 나눈 값을 빼면 된다.
7. (우측 시프트 연산을 사용하는 경우) legit한 rhs 범위는 0 <= rhs < (lhs type의 bit width) 이다.
  그렇지 않은 경우 UB이니 적절히 처리할 것.
https://en.cppreference.com/w/cpp/language/operator_arithmetic.html#:~:text=If%20the%20value%20of%20rhs%20is%20negative%20or%20is%20not%20less%20than%20the%20number%20of%20bits%20in%20lhs%2C%20the%20behavior%20is%20undefined.

*/

#include <iostream>

int main(void) {
  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);

  int t;
  std::cin >> t;

  for (int i = 0; i < t; ++i) {
    long long n, k;
    std::cin >> n >> k;
    if(k > 64) k = 63;
    n >>= k;
    n -= (n>>1);

    std::cout << n << '\n';
  }
  return 0;
}


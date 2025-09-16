/*
bj1160 Random Number Generator

1. 일반항을 구한다.

X(n) = (a^n) * X(0) + c * (1 + a + a^2 + ... a^(n-1))  (mod m)

2. a^n을 빠르게 구하는 방법은 어렵지 않다.

3. 등비수열의 합을 빠르게 구하는 방법

3-1. 행렬을 이용한 방법
[1 0]   [1 0]    [1   0  ]
[1 a] * [1 a] == [1+a a^2]
즉,
[1 0]			[1					0  ]
[1 a] ^ n == 	[1+a+...+a^(n-1)	a^n]
이 경우 행렬 곱셈의 교환이 성립한다.

3-2. 다른 방법
S(n) = 1 + a^1 + ... + a^(n-1)이라 하자.
그러면 0 <= k <= n-1인 k에 대해
S(n) = ( 1 + a^1 + ... + a^(k-1) ) + (a^k) * (1 + ... + a^(n-k-1))
  = S(k) + (a^k) * S(n-k)
bottom-up으로 생각해 보면,
S(1), S(2), S(4), ...는 차례로 빠르게 구할 수 있다. (a^1, a^2, a^4, ...와 함께)
S(1) = 1, a^1 = a
S(2) = S(1) + a^1*S(1), a^2 = a^1 * a^1
S(4) = S(2) + a^2*S(2), a^4 = a^2 * a^2
...
그럼 빠르게 제곱을 구하는 방법과 유사하게 다음과 같은 알고리즘을 사용하면 된다.
func (a, n)
  result = [0 1]
  temp = [1 a]
  while(n)
    if(n%2==1)
      result[0] = temp[0] + temp[1] * result[0]
      result[1] *= temp[1]
    temp[0] = temp[0] + temp[1] * temp[0]
    temp[1] *= temp[1]
  return result

result[0] = S(n), result[1] = a^n
본질적으로는 3-1의 방법과 다를 것이 없다.

4. 오버플로우 해결
max<unsigned long long> ~ 18 * 10^18
mod < 10^18 이므로
모듈로 연산 중 덧셈에서는 오버플로우가 나지 않을 것이 보장된다.
곱셈에서는 항상 오버플로우가 날 수 있다.
오버플로우가 나지 않게 곱셈을 바르게 할 방법을 찾아야 한다.
그러면서도 시간복잡도에 큰 손해를 보지 않는 방법이 필요하다.

4-1. 비트 자릿수를 나누어서 계산
x * y는 다음과 같이 나타낼 수 있다.
x = 1010, y = 1100이라 하면
x * y =

y
1*	1010		4단계
1*	 1010		3단계
0*	  1010		2단계
0*	   1010 	1단계
------------
이 때 각 단계마다 x에 2씩 곱해지는데, 이 때마다 mod를 하면 오버플로우가 나지
않는다.

4-2. 무한 자리수 정수 자료형을 제공하는 언어/라이브러리 사용.
python을 쓰면 된다. python의 경우 pow 함수가 기본적으로 모듈로 연산 기능도 하며
분할 정복 방식으로 이미 구현되어 있다.
*/

#include <iostream>

using ull = unsigned long long;

/**
 * @brief modular multiply, without overflow, slower
 *
 * @tparam T integral type
 * @param x T integer 1
 * @param y T integer 2
 * @param mod T modular, should be smaller than std::numeric_limits<T>::max / 2
 * @return (x*y)%mod, but without overflow
 */
template <typename T>
  requires std::is_integral_v<T>
T multiply_mod(T x, T y, T mod) {
  x %= mod;
  y %= mod;
  T result = 0;
  while (y) {
    if (y & 1) {
      result += x;
      result %= mod;
    }
    x *= 2;
    x %= mod;
    y >>= 1;
  }
  return result;
}

/**
 * @brief modpow - calculate modular power of integer
 *
 * @details Time Complexity: O(n) = log(power)
 *
 * @param base base
 * @param power power (should be an integer)
 * @param mod mod
 * @return [1+base+...+base^(power-1), base^power]
 */
template <typename T>
  requires std::is_integral_v<T>
std::pair<T, T> modpow(T base, T power, T mod) {
  std::pair<T, T> result{0, 1};
  std::pair<T, T> temp{1, base % mod};

  while (power) {
    if (power & 1) {
      result.first = temp.first + multiply_mod(temp.second, result.first, mod);
      result.first %= mod;
      result.second = multiply_mod(result.second, temp.second, mod);
    }
    power >>= 1;
    temp.first = multiply_mod(temp.first, temp.second + 1, mod);
    temp.first %= mod;
    temp.second = multiply_mod(temp.second, temp.second, mod);
  }

  return result;
}

int main(void) {
  ull m, a, c, x0, n, g;
  std::cin >> m >> a >> c >> x0 >> n >> g;
  x0 %= m;
  a %= m;
  c %= m;

  auto [s_n, a_n] = modpow(a, n, m);
  auto x_n = multiply_mod(a_n, x0, m) + multiply_mod(c, s_n, m);
  x_n %= m;

  std::cout << x_n % g << '\n';
}
/*
bj1160 Random Number Generator

일반항을 구하면 결국 거듭제곱을 빨리 구하는 방법으로 귀결된다.

X(n) = (a^n) * X(0) + (a^n - 1)/(a-1)  (mod m)

a^n을 효율적으로 계산하면 된다.

*/

#include<iostream>

using ull = unsigned long long;

/**
 * @brief modpow - calculate modular power of integer
 *
 * @details Time Complexity: O(n) = log(power)
 *
 * @param base base
 * @param power power (should be an integer)
 * @param mod mod 
 * @return (base ^ power) % mod
 */
template<typename T>
T modpow(T base, T power, T mod)
{
	T result = 1;
	T temp = base;

	while (power) {
		if (power & 1) {
			result *= temp;
			result %= mod;
		}
		power >>= 1;
		temp *= base;
	}

	return result;
}

int main(void) {
	ull m, a, c, x0, n, g;
	std::cin >> m >> a >> c >> x0 >> n >> g;

	ull a_n = modpow(a, n, m);
	ull x_n = (a_n * x0 + (a_n - 1) / (a - 1)) % m;

	std::cout << x_n % g << '\n';
}
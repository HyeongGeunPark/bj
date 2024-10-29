/*
bj11689 GCD(n,k) = 1

자연수 n이 주어졌을 때, GCD(n,k)=1을 만족하는 자연수
1 <= k <= n의 개수를 구하는 프로그램을 작성하시오.

즉, n 이하의, n과 서로소(pairwise prime)인 수의 개수를 구하면 된다.

(단, 1 <= n <= 10^12)

접근법: 오일러 피 함수
phi(n) = n 이하 자연수 중 n과 서로소인 자연수의 개수.

1. 오일러 피 함수에 대해 다음 성질이 성립한다.
a, b가 서로소일때,
phi(a * b) = phi(a) * phi(b)

2. 임의의 소수 p에 대해
phi(p) = p-1.

3. 임의의 소수 p, 자연수 k에 대해
phi(p^k) = p^(k-1) * (p-1)

4. 따라서, n을 소인수분해 한 다음 위의 성질을 이용해
	답을 계산 가능하다.

5. n <= 10^12이므로 O(n) = n^(1/2)의 복잡도를 가지는
	에라토스테네스의 체 알고리즘을 사용하면 된다.

주의.
1. 1에 대한 답은 1이다.
*/


#include<iostream>
#include<vector>
#include<unordered_map>
#include<cmath>

long long mypow(long long base, int power) {
	long long result = 1;
	long long temp = base;
	while (power) {
		if (power & 1) {
			result *= temp;
		}
		power >>= 1;
		temp *= temp;
	}
	return result;
}

long long solve(long long n)
{
	if (n == 1) return 1ll;
	// prime factorization
	std::unordered_map<long long, int> primes;

	while (n % 2 == 0) {
		++primes[2];
		n /= 2;
	}
	while (n % 3 == 0) {
		++primes[3];
		n /= 3;
	}

	if(n!=1){
		long long d = 5;
		while (d*d <= n)
		{
			if (n % d != 0) {
				d += 2;
			}
			else {
				++primes[d];
				n /= d;
			}
		}
		++primes[n];
	}

	// calculate final result from factored primes
	long long result = 1;
	for (auto [prime, count] : primes) {
		//phi(p^k) = p^(k-1) * (p-1)
		result *= mypow(prime, count-1) * (prime - 1);
	}

	return result;
}

int main() {

	/*
	// test
	std::vector<long long> test_input{ 1,5,10,45,99 };
	for (auto n : test_input) {
		std::cout << solve(n) << '\n';
	}
	*/

	// submit
	long long n;

	std::cin >> n;

	std::cout << solve(n) << '\n';

	return 0;
}
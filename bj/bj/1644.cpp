/*

bj1644 소수의 연속합

자연수 n을 연속된 소수의 합으로 나타낼 수 있는 경우의 수를 출력한다.
1<=n<=4'000'000

접근법

1. n을 입력받는다.
2. 에라토스테네스의 체 이용, [1, n]까지의 소수 수열을 구한다.
3. moving window 사용, 조건을 만족하는 경우의 수의 개수를 구한다.

*/

#include<iostream>
#include<vector>
#include<cmath>

constexpr int NMAX = 4'000'000;
bool is_not_prime[NMAX + 1];
std::vector<int> primes;

int main() {
	int n;
	std::cin >> n;

	// find primes
	is_not_prime[1] = true;
	int sqrtn = static_cast<int>(std::sqrt(n)) + 1;
	for (int i = 2; i <= sqrtn; ++i) {
		if (is_not_prime[i]) continue;
		for (int j = i*2; j <= n; j+=i) {
			is_not_prime[j] = true;
		} 
	}
	for (int i = 1; i <= n; ++i) {
		if (!is_not_prime[i])
			primes.emplace_back(i);
	}

	// moving window
	int lp = 0, rp = 0;
	int partial_sum = 0;
	int result = 0;
	while (true) {
		if (partial_sum < n) {
			if (rp == primes.size()) break;
			partial_sum += primes[rp++];
			continue;
		}
		if (partial_sum > n) {
			partial_sum -= primes[lp++];
			continue;
		}
		++result;
		if (rp == primes.size()) break;
		partial_sum += primes[rp++];
	}

	std::cout << result;
}
/*

bj1644 �Ҽ��� ������

�ڿ��� n�� ���ӵ� �Ҽ��� ������ ��Ÿ�� �� �ִ� ����� ���� ����Ѵ�.
1<=n<=4'000'000

���ٹ�

1. n�� �Է¹޴´�.
2. �����佺�׳׽��� ü �̿�, [1, n]������ �Ҽ� ������ ���Ѵ�.
3. moving window ���, ������ �����ϴ� ����� ���� ������ ���Ѵ�.

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
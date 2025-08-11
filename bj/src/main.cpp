/*
bj10482 Goldbach's Conjecture

주어진 짝수를 두 소수의 합으로 나타낼 수 있는 모든 경우의 수를 찾아라.

입력:
N: 테스트 케이스의 수 (1<=n<=100)
다음 줄부터 1개의 짝수가 주어진다. (4<=x<=32000)

출력:
예시)
26 has 3 representation(s)
3+23
7+19
13+13

100 has 6 representation(s)
3+97
11+89
...
*/

#include<iostream>
#include<vector>


int main(void) {
	int n;
	std::cin >> n;

	std::vector<bool> is_prime(32001, true);

	is_prime[0] = false;
	is_prime[1] = false;
	for (int i = 2; i < 200; ++i) {
		if (is_prime[i] == true) {
			for (int j = i * 2; j < 32001; j += i) {
				is_prime[j] = false;
			}
		}
	}

 
	for (int i = 0; i < n; ++i) {
		int x;
		std::vector<std::pair<int, int>> results;
		std::cin >> x;

		for (int j = 2; j <= x - j; ++j) {
			if (is_prime[j] && is_prime[x - j]) {
				results.push_back(std::move(std::pair{ j, x - j }));
			}
		} 

		std::cout << x << " has " << results.size() << " representation(s)\n";
		for (auto [a, b] : results) {
			std::cout << a << '+' << b << '\n';
		} 
		std::cout << '\n';
	}

	return 0;
}
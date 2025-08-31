/*
bj1019 책 페이지

전체 페이지 수가 N인 책이 있다.
첫 페이지는 1페이지이고, 마지막 페이지는 N페이지이다.

각 숫자(0, 1, ..., 8, 9)가 전체 페이지 번호에서 모두 몇 번 나오는지 구해라.

1 <= N <= 1'000'000'000

접근: 계산?

예시: 5243

0. 처음
N = 5243

1. 1의 자리
(524) * 3번, 0, 1, 2한번씩. -> 5240 - 5242

2. 10의 자리
(52) * 40번, (0123) 10번씩,  (0,1,2,3,4,5,6,7,8,9) 4번 -> 5200 - 5239

3. 100의 자리
(5) * 200번, (01) 100번씩, (00, 01, ..., 99) 2번씩(각각 20 * 2번) -> 5000 - 5199

4. 1000의 자리
(), (01234) 1000번씩, (000, 001, 002, ..., 999) 5번씩(각각 300 * 5번) -> 0000 - 4999

5. prefix zero 개수
4자리수이므로,
10^0 + 10^1 + 10^2 + 10^3.

11

1의 자리
(1) * 1번, 0 한번 -> 10
10의 자리
(), (0) 10번씩, (0-9) 1번 -> 0 - 9


주의.
1. 오버플로우.

*/

#include<iostream>
#include<array>

int main() {
	long long n;
	std::cin >> n;

	std::array<long long, 10> result = { 0 };

	std::array<int, 20> digits = { 0 };

	int m = 0;
	while (n) {
		digits[m] = n % 10;
		n /= 10;
		++m;
	}

	int exp = 1;
	for (int i = 0;i < m;++i) {
		++result[digits[i]];

		int& num = digits[i];
		for (int j = i + 1;j < m;++j) {
			result[digits[j]] += exp * num;
		}

		for (int j = 0; j < num; ++j) {
			result[j] += exp;
		}

		for (int j = 0;j < 10;++j) {
			result[j] += (exp / 10) * i * num;
		}

		result[0] -= exp;

		exp *= 10;
	}

	for(auto i : result){
		std::cout << i << ' ';
	}
	std::cout << '\n';

	return 0;

}
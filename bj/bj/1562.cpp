/*

bj1562 계단 수

인접한 모든 자리의 차이가 1인 수를 계단수라 한다.
N이 주어질 때, 길이가 N이면서 0부터 9까지 숫자가 모두 등장하는
계단 수가 총 몇 개 있는지 구하는 프로그램.
0으로 시작하는 수는 계단수가 아니다.

입력: N, (1<= N <= 100)
출력: 정답을 1'000'000'000으로 나눈 나머지.

접근법: 다이나믹 프로그래밍 - 타뷸레이션

1. 상태 정의
	F(N, i, a, b) = 길이가 N이면서, 맨 마지막 수가 i인 계단수의 총 갯수.
					[a, b] 범위의 숫자들을 사용함.

2. 기저 조건
	F(1, 0, 0, 0) = 1;
	F(1, 1, 1, 1) = 1;
	...
	F(1, 9, 9, 9) = 1;

3. 점화식
	F(N, i, a, b) =
		F(N-1, i-1, a, b) 
		+ F(N-1, i+1, a, b)
		--------------------
		+ F(N-1, i-1, a, b-1) if i==b
		------------------------
		+ F(N-1, i+1, a+1, b) if i==a

4. 최종 정답
	sum( F(N, i, a, b) ) for i=1,..,9, a=0, b=10;

더 간단한 방법.
캐시 용량이 크게 줄어든다.
1. 상태 정의
	F_a_b(N,i) = 길이가 N이면서, 맨 마지막 수가 i인 계단수의 총 갯수.
					[a,b] 범위의 숫자들을 자유롭게 사용함.
2. 기저 조건
	a <= i <= b.
	F_a_b(1, i) = 0 (i==0 || i<a || i>b)
					1(i!=0 and a<=i<=b) 
3. 점화식

	F_a_b(N, i) = 
		F_a_b(N-1, i-1) + F_a_b(N-1, i+1)
		for i-1, i+1 in range [a,b]

4. 최종 정답
	F_0_9(N) - F_0_8(N) - F_1_9(N) + F_1_8(N) 

*/

#include<iostream>
#include<vector>

constexpr int MOD = 1'000'000'000;
int f(int n, int a, int b) {
	++a;
	++b;
	int DP[2][12] = { 0 };

	for (int i = a; i <= b; ++i) {
		DP[0][i] = (i == 1 ? 0 : 1);
	}

	for (int i = 1; i < n; ++i) {
		auto& cur = DP[i % 2];
		auto& prev = DP[(i + 1) % 2];

		for (int j = a; j <= b; ++j) {
			cur[j] = (prev[j - 1] + prev[j + 1]) % MOD;
		} 
	} 
	long long result = 0;
	for (int i = a; i <= b; ++i) {
		result += DP[(n - 1)%2][i];
	}
	return result % MOD;
}

int main(void) {
	int n;
	std::cin >> n;
	long long ans = f(n, 0, 9) - f(n, 0, 8) - f(n, 1, 9) + f(n, 1, 8);
	ans %= MOD;
	std::cout << (ans < 0 ? ans + MOD : ans);
}

// version 1
/*
	long long DP[100][10][10][10] = { 0, };
	for (int i = 1; i < 10; ++i) {
		DP[0][i][i][i] = 1;
	}
	int N;
	std::cin >> N;
	for (int n = 1; n < N; ++n) {
		for (int i = 0; i < 10; ++i) {
			for (int a = 0; a < 10; ++a) {
				for (int b = a; b < 10; ++b) {
					if (a == b) continue;
					if (i<a || i>b) continue;
					long long& cur = DP[n][i][a][b];
					cur = 0;
					if (i + 1 < 10) {
						cur += DP[n - 1][i + 1][a][b];
						if (i == a) {
							cur += DP[n - 1][i + 1][a + 1][b];
						}
					}
					if (i - 1 >= 0) {
						cur += DP[n - 1][i - 1][a][b];
						if (i == b) {
							cur += DP[n - 1][i - 1][a][b - 1];
						}
					}
					cur %= 1'000'000'000;
				}
			}
		} 
	}
	long long result = 0;
	for (int i = 0; i < 10; ++i) {
		result += DP[N - 1][i][0][9];
	}
	std::cout << result % 1'000'000'000; 
*/


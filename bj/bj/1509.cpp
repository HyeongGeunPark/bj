/*

bj1509 팰린드롬 분할

길이 2500 알파벳 대문자 문자열을 팰린드롬으로 분할한다.
최소 개수로 분할할 경우, 분할된 팰린드롬의 개수를 구하는 문제.

접근법: 다이나믹 프로그래밍

1. 주어진 범위가 팰린드롬인지 구한다.
	1. 상태 표현
		P[i][j] = 
			[i, j)의 범위가 팰린드롬인지?
	2. 기저 조건 
		P[i][j] = true, if i+1 == j or i==j
	3. 반복 구조
		P[i][j] = (s[i]==s[j-1]) && P[i+1][j-1] 

2. 해를 구한다.
	1. 상태 표현
		F[n] =
			[0, n)의 범위를 최소 분할한 개수
	2. 기저 조건
		F[0] = 0, F[1] = 1
	3. 반복 구조
		F[n] = min(F[k] + 1) for k which k in [0, n) and P[k][n] == true
*/

#include<iostream>
#include<cstdlib>

char palin[2501][2501];
int sol[2501];
constexpr int INF = 1 << 20;

std::string s;
constexpr char UNKNOWN = -1;
bool is_palin(int i, int j) {
	// memoization
	if (palin[i][j] != UNKNOWN) return palin[i][j];
	// base case
	if (i == j || i + 1 == j) {
		palin[i][j] = true;
		return true;
	}

	if (s[i] != s[j - 1]) {
		palin[i][j] = false;
	}
	else {
		palin[i][j] = is_palin(i + 1, j - 1); 
	}

	return palin[i][j]; 
}
int solve(int n) {
	// dp - tabulation

	sol[0] = 0;
	sol[1] = 1;

	for (int i = 2; i <= n; ++i) {
		sol[i] = sol[i - 1] + 1;
		for (int k = 0; k < i; ++k) {
			if (is_palin(k, i))
				sol[i] = std::min(sol[i], sol[k] + 1);
		}
	}

	return sol[n]; 
} 

int main(void) {
	std::cin >> s;

	std::memset(palin, UNKNOWN, 2501 * 2501);
	sol[0] = 0;


	std::cout << solve(s.size());
}



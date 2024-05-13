/*

bj1509 �Ӹ���� ����

���� 2500 ���ĺ� �빮�� ���ڿ��� �Ӹ�������� �����Ѵ�.
�ּ� ������ ������ ���, ���ҵ� �Ӹ������ ������ ���ϴ� ����.

���ٹ�: ���̳��� ���α׷���

1. �־��� ������ �Ӹ�������� ���Ѵ�.
	1. ���� ǥ��
		P[i][j] = 
			[i, j)�� ������ �Ӹ��������?
	2. ���� ���� 
		P[i][j] = true, if i+1 == j or i==j
	3. �ݺ� ����
		P[i][j] = (s[i]==s[j-1]) && P[i+1][j-1] 

2. �ظ� ���Ѵ�.
	1. ���� ǥ��
		F[n] =
			[0, n)�� ������ �ּ� ������ ����
	2. ���� ����
		F[0] = 0, F[1] = 1
	3. �ݺ� ����
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



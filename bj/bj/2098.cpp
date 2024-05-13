/*

bj2098 ���ǿ� ��ȸ

�־��� �׷������� �ּ� ����� ��ȸ�� ���ϴ� ����.

�Է�: ���� ��ķ� ��Ÿ�� �׷��� (2<= V <=16)
	����� 0�� ���� ������� ����.

���ٹ�: ���̳��� ���α׷���
 TSP ������ ���̳��� ���α׷����� ��ǥ���� �����̴�.

0���� ������ 0���� ���ƿ��� �ִ� ����� ���̸� ã�ƾ� �Ѵ�.
1. ���� ����
	DP[n][i]��, ���� ���� n, ���ݱ��� �湮�� ������ ��Ʈ����ũ i�� ���ؼ�,
		n���� ����� ������ ���ø� �鷯 0���� ���ư��� �ִ� ����� ����.

2. ���� ����
	DP[n][1<<16-1] = e(n, 0)

3. ���� ����
	DP[n][i] = 
		min{ DP[next][i & (1<<n)] + e(n, next) }
			next�� ���ݱ��� �湮���� ���� ����.


��ü ������ �ش� DP[0][1<<0]�̴�.
*/

#include<iostream>
#include<bit>
#include<vector> 

int N;
constexpr int INF = 1'000'000'000;
int FULL;
std::vector<std::vector<int>> DP(16, std::vector<int>(1 << 16, -1));
int e[16][16];

int solve(int n, int bitmask) {
	// base case
	if (bitmask == FULL) {
		if (e[n][0] == 0) return INF;
		return e[n][0];
	}

	// memoization
	if (DP[n][bitmask] != -1) return DP[n][bitmask];

	// DP
	DP[n][bitmask] = INF;
	for (int i = 0; i < N; ++i) {
		if (bitmask & (1 << i)) continue;
		if (e[n][i] == 0) continue;
		int temp = solve(i, bitmask | (1 << i));
		if (temp == INF) continue;
		DP[n][bitmask] = std::min(DP[n][bitmask], temp + e[n][i]);
	} 
	return DP[n][bitmask];
}


int main(void) {
	std::cin >> N;
	FULL = (1 << N) - 1;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cin >> e[i][j];
		}
	}

	std::cout << solve(0, 1);

	

}
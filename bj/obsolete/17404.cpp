/*
bj17404 rgb�Ÿ�

���̳��� ���α׷��� �̿�.
���� ���ǻ� �ʱ� ������ �����Ͽ� dp�� �� �� �����ϰ�,
���ǿ� �����ϴ� ����鸸 ����Ѵ�.

ù��° ���� ������ ���� -> ù��° ���� ������ �̿��� ����� MAX�� �Ͽ� ������ ����
-> dp ���� �� ������ ���� ���������� ĥ���� ���� ��쿡�� �� ����� ����Ͽ� ���� ��� ����

-> ù��° ���� �ٸ� ���� ������ ��쵵 ���� ���
-> ���� ��� ���.

*/

#include<cstdio>
#include<iostream>
#include<limits>

int mem[1000][3];
int cost[1000][3];

constexpr int MAX = 1000 * 1000 + 1;

int main() {

	int n;
	int result = MAX;

	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 3; ++j) {
			scanf("%d", &cost[i][j]);
		} 
	}

	for (int s = 0; s < 3; ++s) {
		// initial color select
		for (int i = 0; i < 3; ++i) {
			if (i == s)
				mem[0][i] = cost[0][i];
			else
				mem[0][i] = MAX;
		}
		// dp
		for (int i = 1; i < n; ++i) {
			mem[i][0] = cost[i][0] + std::min(mem[i - 1][1], mem[i - 1][2]);
			mem[i][1] = cost[i][1] + std::min(mem[i - 1][0], mem[i - 1][2]);
			mem[i][2] = cost[i][2] + std::min(mem[i - 1][0], mem[i - 1][1]);
		}
		// result select
		for (int i = 0; i < 3; ++i) {
			if (i == s)//invalid 
				continue;
			result = std::min(result, mem[n - 1][i]);
		} 
	}

	printf("%d\n", result); 
}
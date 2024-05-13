/*

bj1799 ���

���簢�� ü������ �� ĭ�� ����� ���� ���� �� ���� ��ġ�� ��ġ�Ѵ�.
�ִ� �� ���� ����� ��ġ�� �� �ִ°�?

�Է�:
ü������ ũ�� N
ü������ ���� (1 = �� ĭ, 0 = ����� ���� ���ϴ� ĭ)

���ٹ�: ����Ž��, ��Ʈ��ŷ

dfs�� ��� ��츦 Ž���Ѵ�.
�� �̻� ����� ��ġ���� ���ϰ� �Ǿ��� �� ������� ���� ����� ������ �����Ѵ�.

�� �밢���� �ϳ��� ��� �� �� �ִٴ� ���� �̿��Ѵ�.

��� ĭ�� ���� ����� ���� ��� ĭ���� ������ ��ġ��,
������ ĭ�� ���� ����� ���� ������ ĭ���� ������ ��ġ�Ƿ�
������ ��� ĭ�� ������ ĭ�� ���� ���� Ǯ ���� �ִ�.
*/


#include<iostream>
#include<limits> 

int n;
bool diag1[20];
bool diag2[20];

/*	
	0	1	2	3	4	5	6 -> diag1[2n-1]
	/	/	/	/	/	/	/
	0	0	0	0 /   /   /
	0	0	0	0/ /   /
	0	0	0	0/  /
	0	0	0	0/
	\	\	\	\	\	\	\
	0	1	2	3	4	5	6 -> diag2[2n-1]

	x = index of diag1 = i + j
	y = index of diag2 = -i + j + n - 1
 
*/

int map[10][10];

int result = 0;
void DFS(int depth, int num) {
	if (depth >= (2 * n - 1)) {
		result = std::max(result, num);
		return;
	} 

	bool flag = true;
	for (int i = 0; i < n; ++i) {
		int j = depth - i;
		if (j < 0 || j >= n) continue; // out of range

		if (map[i][j] == 1 && !diag2[-i + j + n - 1]) {
			flag = false;
			diag2[-i + j + n - 1] = true;
			DFS(depth + 2, num + 1);
			diag2[-i + j + n - 1] = false;
		}
	} 
	if (flag) {
		DFS(depth + 2, num);
	} 
}

int solve() {
	DFS(0, 0);
	int ans = result;
	result = 0;
	DFS(1, 0);
	ans += result;
	return ans; 
}


int main(void) {
	std::cin >> n; 

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			std::cin >> map[i][j];
		}
	}

	std::cout << solve(); 
}

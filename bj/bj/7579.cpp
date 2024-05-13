/*

bj7579 ��

���� �޸� �̻��� Ȯ���� �� �ִ� ���� �� ��Ȱ��ȭ ����� �ּ��� ���� ���Ѵ�.

���ٹ� : DP, �賶 ����

����: �� * ��� -> �ִ� 100 * 10000

F(n, c) == 0~n�������� ���� ������� �� ��� c���� ����Ͽ� Ȯ���� �� �ִ� �ִ� �޸�
*/

#include<iostream>
#include<vector>
#include<cstring>

struct proc {
	int cost, mem;
};

int dp[2][10001];

 
int main() {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0); 

	int n, m;
	int minimum_cost = 0;
	std::cin >> n >> m;

	std::vector<proc> procs(n+1);
	for (int i = 0; i < n; ++i) {
		std::cin >> procs[i].mem;
	}
	for (int i = 0; i < n; ++i) {
		std::cin >> procs[i].cost;
		minimum_cost += procs[i].cost;
	}
 
	// dp

	auto prev = dp[0];
	auto current = dp[1];

	for (int i = 0; i < n; ++i) {
		std::memset(current, 0, sizeof(int) * (minimum_cost + 1));
		for (int j = 0; j < minimum_cost; ++j) {
			if (procs[i].cost <= j) {
				current[j] = std::max(current[j], prev[j - procs[i].cost] + procs[i].mem);
			}
			current[j] = std::max(current[j], prev[j]);
			if (current[j] >= m) {
				minimum_cost = std::min(minimum_cost, j);
			}
		}
		std::swap(current, prev); 
	}

	std::cout << minimum_cost; 
}
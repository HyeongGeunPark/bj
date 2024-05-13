/*

bj1005 ACM Craft

���ٹ�: dp

F(n)�� n�� �ǹ��� ���µ� �ʿ��� �ּ� �ð��̶�� ����.
n�� �ǹ��� prerequisite p1, p2, ..., pk�� ���ؼ�,
F(n) = max(F(p1), F(p2), ..., F(pk)) + cost(n)�̴�.
�޸������̼��� ����ϸ鼭 ��������� Ǯ�� �� �� �ϴ�.  

*/

#include<iostream>
#include<vector>

int solve(int w, std::vector<std::vector<int>>& rule, std::vector<int>& cost) {
	int temp = 0;
	while (rule[w].size()) {
		temp = std::max(temp, solve(rule[w].back(), rule, cost));
		rule[w].pop_back();
	}
	cost[w] += temp;
	return cost[w]; 
}


int main(void) {

	// cpp simple fast io
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i) {
		int n, k;
		std::cin >> n >> k;
		std::vector<std::vector<int>> rule(n+1);
		std::vector<int> cost(n + 1);

		for (int j = 1; j <= n; ++j) {
			std::cin >> cost[j];
		}
		for (int j = 0; j < k; ++j) {
			int p, d;
			std::cin >> p >> d;
			rule[d].push_back(p);
		}

		int w;
		std::cin >> w;
		std::cout << solve(w, rule, cost) << '\n'; 
	} 
}
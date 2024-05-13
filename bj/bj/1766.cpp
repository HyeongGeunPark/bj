/*

bj1766 ������

���ٹ�: ���� ����, Kahn's algorithm

1. ���� ����Ʈ�� �����Ѵ�.
2. ���ÿ� ���������� ���Ѵ�.
3. kahn's algorithm
	3-1. ���������� 0�� ��带 ť�� �ִ´�.
	3-2. ť���� ��带 �ϳ��� �����鼭 �� ��忡 ����� ����� ���������� �ϳ��� ���δ�.
		���� ����Ʈ�� �̿��ϵ� ���� �����ؾ� �Ѵ�.
		�� �� ���������� 0�� �� ���� ť�� �ִ´�.
	3-3. ť�� ������ �� ������ �ݺ��Ѵ�.
	(3-4. ť�� ���� ���� ����� ���� ��ü ����� ������ ������ cycle�� ����.)

	�켱���� ť�� �̿��ϸ� ������ ����(���� �������� Ǯ��)�� ������ �� �ִ�.

ť���� ���� ������� �״�� ����ϸ� �ȴ�.

*/

#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

std::vector<std::vector<int>> adj; 
std::vector<int> degree;
std::priority_queue<int, std::vector<int>, std::greater<int>> q;

int main(void) {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	int n, m;
	std::cin >> n >> m;

	adj.resize(n + 1);
	degree.resize(n + 1, 0);

	for (int i = 0; i < m; ++i) {
		int s, d;
		std::cin >> s >> d;
		adj[s].push_back(d);
		++degree[d];
	}

	// kahn's algorithm
	for (int i = 1; i <= n; ++i) {
		if (degree[i] == 0) q.push(i);
	}
	while (!q.empty()) {
		int cur = q.top();
		q.pop();
		auto& pred = adj[cur];
		std::sort(pred.begin(), pred.end());
		for (int p : pred) {
			--degree[p];
			if (degree[p] == 0) q.push(p);
		} 
		std::cout << cur << ' ';
	} 

}
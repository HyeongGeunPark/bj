/*

bj2623 �������α׷�

������ ��: �ִ� 1000
���� pd�� ��: �ִ� 100

���ٹ�(���� ����)

1. �Է��� �̿��� ���� ����Ʈ�� ���İ��踦 �����Ѵ�.

2. Kahn�� �˰��� ����.


*/

#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<queue>


int main(void) {
	int n, m;

	std::cin >> n >> m;
	std::cin >> std::ws;

	std::vector<std::vector<int>> adj;
	std::vector<int> degree;
	adj.resize(static_cast<size_t>(n) + 1);
	degree.resize(static_cast<size_t>(n) + 1, 0);


	// input
	for (int i = 0; i < m; ++i) {
		int nn;
		std::cin >> nn;
		if (!nn) continue; 

		int prev, next;
		std::cin >> prev; 

		for (int j = 1; j < nn; ++j) {
			std::cin >> next;
			adj[prev].push_back(next);
			++degree[next];
			prev = next;
		}
	}

	// Kahn's algorithm
	std::vector<int> obuf;
	std::queue<int> q;

	for (int i = 1; i <= n; ++i) {
		if (degree[i] == 0) q.push(i);
	}

	while (!q.empty()) {
		int prev = q.front();
		obuf.push_back(prev);
		q.pop();

		for (int next : adj[prev]) {
			--degree[next];
			if (degree[next] == 0) {
				q.push(next);
			}
		}
	}

	if (obuf.size() != n) {
		std::cout << '0';
	}
	else {
		for (int i : obuf) {
			std::cout << i << '\n';
		}
	}

}
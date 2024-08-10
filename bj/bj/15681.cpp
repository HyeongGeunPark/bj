/*
bj15681 트리와 쿼리
간선에 가중치와 방향성이 없는 임의의 루트 있는 트리가 주어졌을 때,
정점 U를 루트로 하는 서브트리에 속한 정점 수를 답하는
쿼리를 반복한다.

정점 수<=10^5
쿼리 수<=10^5 
*/
#include<iostream>
#include<vector>

std::vector<int> parent;
std::vector<int> subtree_nodes;
std::vector<std::vector<int>> adj_list;

void make_tree(int node) {
	for (auto adj_node : adj_list[node]) {
		if (adj_node != parent[node]) { 
			parent[adj_node] = node;
			make_tree(adj_node);
			subtree_nodes[node] += subtree_nodes[adj_node];
		}
	}
}

int main(void) {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);
	int n, r, q;
	std::cin >> n >> r >> q;

	parent.resize(n + 1, 0);
	subtree_nodes.resize(n + 1, 1);
	adj_list.resize(n + 1, std::vector<int>(0));

	for (int i = 0; i < n - 1; ++i) {
		int s, d;
		std::cin >> s >> d;
		adj_list[s].push_back(d);
		adj_list[d].push_back(s);
	}
	make_tree(r);

	for (int i = 0; i < q; ++i) {
		int q;
		std::cin >> q;
		std::cout << subtree_nodes[q] << '\n';
	}  
}

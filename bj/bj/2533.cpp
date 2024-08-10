/*
bj2533 사회망 서비스(SNS)

1. 사회 관계망 그래프에서, 이웃한 모든 사람이 얼리 어댑터이면
	새로운 아이디어를 수용한다.
2. 트리 형상의 사회 관계망 그래프만을 고려한다.
3. 모든 사람이 새로운 아이디어를 받아들이기 위한
	최소 얼리 어댑터의 수는?

접근법: 재귀적 풀이
각 노드는 얼리 어댑터이거나 아니거나 둘 중 하나이다.
트리 형상이므로, 임의의 노드를 root로 생각할 수 있다.

임의의 노드 번호 i에 대해
ans[i][0] = 노드 i가 얼리 어댑터일 경우, i의 subtree 전체가
			새 아이디어를 받아들이게 하는 최소 얼리 어댑터 수
ans[i][1] = 노드 i가 얼리 어댑터가 아닌 경우, i의 subtree 전체가
			새 아이디어를 받아들이게 하는 최소 얼리 어댑터 수

base case는 i가 leaf인 경우이며,
ans[i][0] = 1
ans[i][1] = 0

재귀식은 다음과 같다.
부모 노드가 얼리 어댑터인 경우, 자식이 얼리어댑터인지는 관계 없음.
ans[i][0] = 1 + sum( min(ans[childs][0], ans[childs][1] ) 
부모 노드가 얼리 어댑터가 아닌 경우, 모든 자식이 얼리어댑터여야 함. 따라서
ans[i][1] = sum(ans[childs][0])

*/

#include<iostream>
#include<vector>
#include<array>

std::vector<std::vector<int>> graph;
std::vector<bool> visited;
std::vector<std::array<int, 2>> ans;

void solve(int i) {
	visited[i] = true;
	ans[i][0] = 1;
	ans[i][1] = 0;
	for (int child : graph[i]) {
		if (visited[child]) continue;
		solve(child);
		ans[i][0] += std::min(ans[child][0], ans[child][1]);
		ans[i][1] += ans[child][0];
	} 
}

int main(void) {
	std::cin.tie(0);
	std::cout.tie(0);
	std::ios_base::sync_with_stdio(0);

	int n;
	std::cin >> n;
	graph.resize(n + 1);
	visited.resize(n + 1);
	ans.resize(n + 1);

	for (int i = 0; i < n - 1; ++i) {
		int s, d;
		std::cin >> s >> d;
		graph[s].push_back(d);
		graph[d].push_back(s);
	}

	solve(1);

	std::cout << std::min(ans[1][0], ans[1][1]); 
}
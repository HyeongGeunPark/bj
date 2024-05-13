/*

bj9466 텀 프로젝트

접근법(dfs) 

1. 경로를 따라가며 방문하지 않은 노드에 색을 칠한다.
2. 다음에 칠할 노드에 현재 칠하고 있는 색이 칠해져 있다면,
	다음에 칠할 노드가 다시 나올 때까지 경로를 따라가면서 갯수를 센다.
3. 다음에 칠할 노드에 색이 칠해져 있지 않다면 현재 칠하고 있는 색을 칠한다.

4. 색칠되지 않은 다음 노드를 골라 새로운 색깔로 위 작업을 반복한다.

*/

#include<iostream>

int result;
int preference[100001];
int visited[100001];

void dfs(int i, int color) {
	visited[i] = color;
	if (visited[preference[i]] == color) {
		// cycle detected
		int cur = preference[i];
		do {
			--result;
			cur = preference[cur];
		} while (cur != preference[i]);
	}
	else if (!visited[preference[i]]) dfs(preference[i], color); 
}

int main(void) {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	int t, n;
	std::cin >> t;
	while (t--) {
		std::cin >> n;
		result = n;
		for (int i = 1; i <= n; ++i) {
			std::cin >> preference[i];
		}
		std::memset(visited, 0, sizeof(int) * (n + 1));

		for (int i = 1, color = 1; i <= n; ++i) if(!visited[i]) dfs(i, color++);

		std::cout << result << '\n';
	} 
}
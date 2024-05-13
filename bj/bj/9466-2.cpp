/*

bj9466 �� ������Ʈ

���ٹ�(dfs) 

1. ��θ� ���󰡸� �湮���� ���� ��忡 ���� ĥ�Ѵ�.
2. ������ ĥ�� ��忡 ���� ĥ�ϰ� �ִ� ���� ĥ���� �ִٸ�,
	������ ĥ�� ��尡 �ٽ� ���� ������ ��θ� ���󰡸鼭 ������ ����.
3. ������ ĥ�� ��忡 ���� ĥ���� ���� �ʴٸ� ���� ĥ�ϰ� �ִ� ���� ĥ�Ѵ�.

4. ��ĥ���� ���� ���� ��带 ��� ���ο� ����� �� �۾��� �ݺ��Ѵ�.

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
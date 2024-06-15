/*

bj16724 피리 부는 사나이

사이클마다 한 개의 safe zone이 존재하면 된다.


접근법(dfs)
bj9466 참고.
혹은, 사이클에 속한 원소 수를 알 필요가 없으므로 disjoint set을 이용한다.

*/

#include<iostream>


enum direction {
	U = 0, D, L, R
};

struct vec2 {
	int x, y;
};

vec2 move[4] = {
	{-1, 0},
	{1, 0},
	{0, -1},
	{0, 1}
};

vec2 operator+(const vec2& v1, const vec2& v2) {
	return { v1.x + v2.x, v1.y + v2.y };
}

int visited[1000][1000];
direction map[1000][1000];
int cnt;

void dfs(vec2 cur, int color) {
	visited[cur.x][cur.y] = color;
	vec2 next = cur + move[map[cur.x][cur.y]];
	if (!visited[next.x][next.y]) dfs(next, color);
	else if (visited[next.x][next.y] == color) {
		// cycle detected
		++cnt;
	} 
	// else: current path is connected to a cycle. no need to count.
}

int main(void) {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	int n, m;
	std::cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			char temp;
			std::cin >> temp;
			switch (temp) {
			case 'U':
				map[i][j] = U;
				break;
			case 'D':
				map[i][j] = D;
				break;
			case 'L':
				map[i][j] = L;
				break;
			case 'R':
				map[i][j] = R;
				break;
			} 
		}
	}

	int current_color = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (!visited[i][j]) dfs(vec2{i,j}, ++current_color);
		}
	}

	std::cout << cnt; 
}
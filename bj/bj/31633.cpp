/*

bj31633 첨단 가지 농장
 
 위상정렬
*/

#include<iostream>
#include<vector>
#include<queue>

struct vec2 {
	int x, y;
};

vec2 operator+(const vec2& a, const vec2& b) {
	return vec2{ a.x + b.x, a.y + b.y };
}


/* 
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
*/
vec2 dd[4] = { {-1,0}, {1,0}, {0,-1}, {0,1} };

// test print
void test_print(const std::vector<std::vector<int>>& vec2d) {
	for (auto& v : vec2d) {
		for (int i : v) {
			std::cout << i << ' ';
		}
		std::cout << '\n';
	}
}

inline bool in_range(const vec2& v, int n, int m) {
	return (v.x >= 0 && v.x < n && v.y >= 0 && v.y < m);
}

int main(void) {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);
	int n, m, nodenum;

	std::cin >> n >> m;

	std::vector<std::vector<int>> s(n, std::vector(m,0));
	std::vector<std::vector<int>> h(n, std::vector(m,0));

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			std::cin >> s[i][j];
		}
	}

	// 인접그래프
	std::vector<std::vector<int>> mat2g(n, std::vector<int>(m, 0));

	nodenum = -1;
	std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			// bfs
			std::queue<vec2> q;
			if (!visited[i][j]) {
				q.push(vec2{ i,j });
				visited[i][j] = true;
				++nodenum;
			}
			while (q.size()) {
				vec2 cur = q.front(); q.pop();
				mat2g[cur.x][cur.y] = nodenum;
				for (int i = 0; i < 4; ++i) {
					const vec2& next = cur + dd[i];
					if (in_range(next, n, m) && !visited[next.x][next.y]) {
						if (s[cur.x][cur.y] == s[next.x][next.y]) {
							visited[next.x][next.y] = true;
							q.push(next);
						} 
					}
				}
			}
		}
	}
	++nodenum;
	std::vector<int> d(nodenum);
	std::vector<std::vector<int>> adj(nodenum);

	//test_print(mat2g);

	
	// 진입차수, 인접그래프
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (i > 0)
				if (s[i][j] > s[i - 1][j]) ++d[mat2g[i][j]], adj[mat2g[i - 1][j]].push_back(mat2g[i][j]);
			if (i < n - 1)
				if (s[i][j] > s[i + 1][j]) ++d[mat2g[i][j]], adj[mat2g[i + 1][j]].push_back(mat2g[i][j]);
			if (j > 0)
				if (s[i][j] > s[i][j - 1]) ++d[mat2g[i][j]], adj[mat2g[i][j - 1]].push_back(mat2g[i][j]);
			if (j < m - 1)
				if (s[i][j] > s[i][j + 1]) ++d[mat2g[i][j]], adj[mat2g[i][j + 1]].push_back(mat2g[i][j]);
		}
	} 

	// root 찾기
	std::queue<int> q;
	for (int i = 0; i < nodenum; ++i) {
		if (d[i] == 0) q.push(i);
	}

	// 위상정렬
	int depth_n = 0;
	std::vector<int> depth(nodenum);

	while (int n = q.size()) { 
		while (n--) {
			int cur = q.front(); q.pop();
			depth[cur] = depth_n;
			for (int i : adj[cur]) {
				--d[i];
				if (d[i] == 0) {
					q.push(i);
				}
			}
		}
		++depth_n;
	}

	// graph to mat
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			h[i][j] = depth[mat2g[i][j]];
		}
	}

	test_print(h);



}

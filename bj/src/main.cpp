/*
bj1761 정점들의 거리

N(2 <= N <= 40'000)개의 정점으로 이루어진 트리가 주어지고,
M(1 <= M <= 10'000)개의 두 노드 쌍을 입력받을 때,
두 노드 사이의 거리를 출력하라.

접근법: 최소 공통 조상 찾기(이분 탐색으로 개선됨)

1. 임의의 한 점을 루트로 잡는다.
2. 루트로부터 모든 점의 거리를 계산한다. (트리이므로 시간복잡도 N)
	2-1. 최소 공통 조상을 빠르게 찾기 위해 다음을 저장한다.
		- 각 점의 루트로부터의 깊이
		- 각 점의 2^k번째 조상

3. 각 쿼리에 대해 다음 작업을 한다.
	1. 최소 공통 조상을 찾는다.
		1. 두 점의 깊이를 각각 d1, d2라 하자.
		2. d1, d2 중 더 깊은 것을 더 얕은 것까지 올린다.
			2에서 저장해 놓은 2^k번째 조상을 이용한다.
		3. 깊이가 같아지면, 마찬가지로 2^k번째 조상을 이용해
			최소 공통 조상을 찾는다.
			1. 둘의 2^k번째 조상 중 서로 같지 않은 가장 먼 조상을 찾는다.
			2. 그만큼 올리고 위 과정을 다시 반복한다.
			3. 결국에는 둘의 부모가 같아진다. 그 부모가 최소 공통 조상이다.
	2. 다음의 계산으로 두 점 사이의 거리를 구한다.
	(root-점1 거리) + (root-점2 거리) - 2*(root-공통조상 거리)

개선.
parent[][]의 방향 설정으로 캐시 히트 비율을 높일 수 있다.
*/

//#include<iostream>
#include<vector>
#include<cmath>

struct edge {
	int dest, len;
};

// some global variables
std::vector<std::vector<edge>> adj;
std::vector<long long> distance_from_root;
std::vector<int> depth_from_root;
int parent[18][40001];
int h;
int n;

void dfs(int cur_node, int parent_node, int depth)
{
	depth_from_root[cur_node] = depth;
	for (auto [next, len] : adj[cur_node]) {
		if (next != parent_node) {
			distance_from_root[next] = distance_from_root[cur_node] + len;
			dfs(next, cur_node, depth + 1);
			parent[0][next] = cur_node;
		}
	}

}

void fill_parents()
{
	for (int i = 1;i <= h;++i) {
		for (int j = 1;j <= n;++j) {
			parent[i][j] = parent[i-1][parent[i-1][j]];
		}
	}
}

int find_common_ancestor(int a, int b)
{
	if (depth_from_root[a] < depth_from_root[b]) {
		std::swap(a, b);
	}

	// make same depth
	for (int i = h; i >= 0; --i) {
		if ((1 << i) <= (depth_from_root[a] - depth_from_root[b]))
			a = parent[i][a];
	}

	if (a == b) return a;

	for (int i = h;i >= 0;--i) {
		if (parent[i][a] != parent[i][b]) {
			a = parent[i][a];
			b = parent[i][b];
		}
	}

	return parent[0][a];
}

// fast io things, linux only
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

namespace FastIO {
	constexpr int writeBufSz = 10000 * 30;
	char* readBuf;
	char* readCursor;
	char writeBuf[writeBufSz];
	char* writeCursor = writeBuf;
	struct stat st;

	void init() {
		fstat(0, &st);
		readBuf = (char*)mmap(0, st.st_size, PROT_READ, MAP_SHARED, 0, 0);
		readCursor = readBuf;
	}
	void deinit() {
		munmap(readBuf, st.st_size);
	}

	bool is_blank(char c) { return c == ' ' || c == '\n' }
	bool is_end(char c) { return c == '\0' }
	bool is_digit(char c) { return c >= '0' && c <= '9'; }
	char read_char() {
		while (is_blank(*readCursor)) ++readCursor;
		return *readCursor++;
	}
	template<typename T>
	// requires std::is_integral_v<T>
	T read_int() {
		T result = 0;
		char current = read_char();
		bool flag = false;
		if (cur == '-') {
			flag = true;
			current = read_char();
		}
		result += curent - '0';
		while (!is_digit(*readCursor)) {
			result = result * 10 + (read_char() - '0');
		}
		return flag ? -result : result;
	}

	void write_char(char c) {
		*writeCursor++ = c;
	}

	template<typename T>
	// requires std::is_integral_v<T>
	void write_int(T n) {
		char buf[30];
		char* bufCursor
		if (n < 0) {
			*writeCursor++ = '-';
			n = -n;
		}
		do {
			*bufCursor++ = (n % 10) - '0';
			n /= 10;
		}
		while (n);
		do {
			*writeCursor++ = *(--bufCursor);
		} while (bufCursor != buf);
	}

	void flush() {
		write(1, writeBuf, writeCursor - writeBuf);
		writeCursor = writeBuf;
	}


}



int main()
{
	//std::cin.tie(0);
	//std::ios_base::sync_with_stdio(0);

	// tree input and store in adjacent list
	//std::cin >> n;
	adj.resize(n + 1);
	for (int i = 0;i < n-1;++i) {
		int s, d, l;
		std::cin >> s >> d >> l;
		adj[s].push_back(edge{ d,l });
		adj[d].push_back(edge{ s,l });
	}

	// depth first search
	depth_from_root.resize(n + 1);
	distance_from_root.resize(n + 1, 0);
	dfs(1, 0, 0);
	h = (int)std::ceil(std::log2(n));
	fill_parents();

	// query input
	int m;
	std::cin >> m;

	for (int i = 0;i < m;++i) {
		int a, b;
		std::cin >> a >> b;
		int common_ancestor = find_common_ancestor(a, b);
		std::cout <<
			distance_from_root[a] + distance_from_root[b]
			- 2 * distance_from_root[common_ancestor] << '\n';
	}
	return 0;
}

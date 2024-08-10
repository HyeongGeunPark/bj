/*
bj2887 행성 터널
최대 100'000개의 3차원 좌표가 주어진다.
MST의 변의 총합을 구하여라.
단, 좌표 사이의 거리는 min(|x1-x2|, |y1-y2|, |z1-z2|)이다.

접근법:
어떤 mst 알고리즘을 사용하던 변의 개수가 너무 많아 문제가 된다.
따라서, 가망 없는 변은 처음부터 걸러내고 시작하여야 한다.

행성을 각각 x, y, z로 정렬하여
이웃한 행성 사이에만 mst에 속할 수 있는 변이 존재한다는 것을 이용한다.
이웃하지 않은 행성 사이의 경로는 mst로 선택될 가능성이 없는데,
행성이 정렬 후 A-B-C로 나열되었을 때,
len(A,C) = len(A,B) + len(B,C)이기 때문에,
경로 (A,C)가 선택되기 전에 경로 (A,B), (B,C)가 선택되어
경로 (A,C)를 선택할 수 없기 때문이다(A, C가 이미 연결되었기 때문).

이후 크루스칼 알고리즘을 적용하면 된다.
*/

#include<iostream>
#include<vector>
#include<algorithm> 

struct edge {
	int l, s, d;
	auto operator<(const edge& other) const {
		return l < other.l;
	}
};

class disjoint_set {
public:
	disjoint_set(int n) : root(n, -1) {}
	int find_root(int v) {
		if (root[v] < 0) return v;
		else return root[v] = find_root(root[v]); 
	}
	bool merge(int v1, int v2) {
		v1 = find_root(v1);
		v2 = find_root(v2);
		if (v1 == v2) return false;
		root[v2] = v1;
		return true;
	}
private:
	std::vector<int> root;
};

int main(void) {

	std::cin.tie(0);
	std::ios_base::sync_with_stdio(false);
	int n;
	std::cin >> n;
	std::vector<std::pair<int, int>> x, y, z;
	for (int i = 0; i < n; ++i) {
		int xx, yy, zz;
		std::cin >> xx >> yy >> zz;
		x.push_back({ xx, i });
		y.push_back({ yy, i });
		z.push_back({ zz, i });
	}
	std::ranges::sort(x);
	std::ranges::sort(y);
	std::ranges::sort(z);


	std::vector<edge> edges; 
	for (int i = 0; i < n - 1; ++i) {
		edges.push_back({ x[i + 1].first - x[i].first, x[i].second, x[i + 1].second });
		edges.push_back({ y[i + 1].first - y[i].first, y[i].second, y[i + 1].second });
		edges.push_back({ z[i + 1].first - z[i].first, z[i].second, z[i + 1].second });
	}

	std::sort(edges.begin(), edges.end(), [](const edge& a, const edge& b) {return a.l < b.l; });

	disjoint_set djs(n);

	// kruskal's algorithm
	int v = 0;
	int i = 0;
	long long weight = 0;
	while (v != (n - 1)) {
		edge& e = edges[i++];
		if (djs.merge(e.s, e.d)) {
			weight += e.l;
			++v;
		}
	}

	std::cout << weight; 
}
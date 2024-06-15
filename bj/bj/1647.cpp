/*

bj1647
MST를 구한 후 가장 비싼 도로 하나를 없애면 된다.
혹은, 크루스칼 알고리즘에서 경로 하나를 남기고 종료하면 된다.

*/

#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>

class disjoint_set {
public:
	disjoint_set(int v);
	~disjoint_set(void);
	int find_root(int v);
	bool union_merge(int v1, int v2);
private:
	int* root;
};

disjoint_set::disjoint_set(int v) {
	root = new int[v + 1];
	std::memset(root, 0xFF, (v+1)*sizeof(int)); // windows compatible sizeof array
}
disjoint_set::~disjoint_set(void) {
	delete[] root;
}
int disjoint_set::find_root(int v) {
	if (root[v] < 0) return v;
	// path compression
	root[v] = find_root(root[v]);
	return root[v];

}
bool disjoint_set::union_merge(int v1, int v2) {
	v1 = find_root(v1);
	v2 = find_root(v2);
	if (v1 == v2) return false;
	// rank by size. root[v1] means -(# of vertice) of the tree, if v1 is root
	if (root[v1] > root[v2]) std::swap(v1, v2); // then v1 is the root of bigger tree
	root[v1] += root[v2];
	root[v2] = v1;
	return true; 
}

struct edge {
	int s, d, w;
};

bool edge_compare(const edge& a, const edge& b) {
	return a.w < b.w;
}

int main() {

	// cpp little fast io
	std::cin.tie(0);
    std::cout.tie(0);
	std::ios_base::sync_with_stdio(0);

	int n, m;
	std::cin >> n >> m;

	disjoint_set djs(n);
	std::vector<edge> edges;
	edges.reserve(m);

	for (int i = 0; i < m; ++i) {
		int s, d, w;
		std::cin >> s >> d >> w;
		edges.emplace_back(edge{ s,d,w });
	}
	std::sort(edges.begin(), edges.end(), edge_compare);

	int n_count = 0;
	long long total_cost = 0;
	for (int i = 0; n_count < (n - 2); ++i) {
		edge& ee = edges[i];
		if (djs.union_merge(ee.s, ee.d)) {
			++n_count;
			total_cost += ee.w;
		}
	}

	std::cout << total_cost; 
}

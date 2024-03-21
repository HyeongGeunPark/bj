// sum of weights of mst
// kruskal's algorithm

#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

constexpr int vmax = 10000;

struct edge {
	int s, d, w;
};

std::vector<edge> edges;

bool edge_sort(const edge& a, const edge& b) {
	return a.w < b.w;
}

class disjoint_set {
public:
	disjoint_set(int v);
	~disjoint_set();
	int find_root(int v);
	bool union_merge(int v1, int v2);

private:
	int* root;
	int* rank; 
};

disjoint_set::disjoint_set(int v) {
	root = new int[v + 1];
	rank = new int[v + 1];
	for (int i = 0; i < v + 1; ++i) {
		root[i] = i;
	}
	std::memset(rank, 0xFF, (static_cast<unsigned long long>(v) + 1) * sizeof(int));
}

disjoint_set::~disjoint_set() {
	delete[] root;
	delete[] rank;
}

int disjoint_set::find_root(int v) {
	/*
	if (v == root[v]) return v;

	// path compression
	root[v] = find_root(root[v]);
	return root[v]; 
	*/
	if (root[v] < 0) return v;
	else return find_root(root[v]);
}

bool disjoint_set::union_merge(int v1, int v2) {
	v1 = find_root(v1);
	v2 = find_root(v2);
	if (v1 == v2) return false;

	/*
	// rank by size
	if (rank[v1] > rank[v2]) {
		std::swap(v1, v2);
	}
	rank[v1] += rank[v2];
	root[v2] = v1;
	return true; 
	*/

	if (root[v1] > root[v2]) {
		std::swap(v1, v2);
	}
	root[v1] += root[v2]; root[v2] = v1;
	return true;
}



int main() {

	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0); 


	int v, e;
	std::cin >> v >> e; 

	edges.reserve(e);
	disjoint_set djs(v);

	for (int i = 0; i < e; ++i) {
		int s, d, w;
		std::cin >> s >> d >> w;
		edges.emplace_back(edge{ s,d,w }); 
	}

	// kruskal's algorithm
	long long total_weight = 0;
	std::sort(edges.begin(), edges.end(), edge_sort);
	for (int i = 0, e_count = 0; e_count < (v-1); ++i) { 
		edge& ee = edges[i]; // lvalue reference == alias of existing object
		if (djs.union_merge(ee.d, ee.s)) {
			total_weight += ee.w;
			++e_count;
		}
	}

	std::cout << total_weight; 
}
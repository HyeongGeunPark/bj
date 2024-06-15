#include<iostream>
#include<vector>
#include<algorithm>

class disjointset {
public:
	disjointset(int n) : data(n + 1, -1) {}
	int is_root(int a) {
		return data[a] < 0;
	}
	int rank(int a) {
		return -data[a];
	}
	int root(int a) {
		if (is_root(a)) {
			return a; 
		}
		data[a] = root(data[a]);
		return data[a];
	}
	bool join(int a, int b) {
		a = root(a);
		b = root(b);
		if (a == b) {
			return false;
		}
		if (rank(a) < rank(b)) {
			std::swap(a, b);
		}
		data[a] += data[b];
		data[b] = a;
		return true;
	}
	disjointset& operator=(disjointset& other) {
		data = other.data;
		return *this;
	}

private:
	std::vector<int> data;
};

struct edge {
	int src, dst;
};

int main(void) {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);
	int n, q;
	std::cin >> n >> q;

	std::vector<std::vector<edge>> edges(11);

	int mst = 0;
	for (int i = 1; i < n; ++i) {
		int s, d, w;
		std::cin >> s >> d >> w;
		edges[w].emplace_back(edge{ s,d });
		mst += w;
	} 

	std::vector<disjointset> state(11, disjointset(n+1));


	for (int w = 1; w <= 10; ++w) {
		state[w] = state[w - 1];
		for (edge& e : edges[w]) {
			state[w].join(e.src, e.dst);
		}
	}

	for (int i = 0; i < q; ++i) {
		int u, v, w;
		std::cin >> u >> v >> w;

		for (int j = w; j <= 10; ++j) {
			if (state[j].join(u, v)) {
				--mst;
			}
		}
		std::cout << mst << '\n';
	} 
}
#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>

// mst finding
// prim's algorithm


constexpr int vmax = 10000;

struct edge {
	int dst, weight;
};


class edge_compare {
public:
	bool operator()(const edge& a, const edge& b) {
		return a.weight > b.weight;
	}
};

std::unordered_map<int, int> graph[vmax + 1];
std::priority_queue<edge, std::vector<edge>, edge_compare> edges;
bool v_check[10001];



int main() {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	int v, e;

	std::cin >> v >> e;

	for (int i = 0; i < e; ++i) {
		int src, dst, weight;
		std::cin >> src >> dst >> weight;

		if (!graph[src].count(dst)) {
			graph[src][dst] = weight;
			graph[dst][src] = weight;
		}
		else {
			graph[src][dst] = std::min(weight, graph[src][dst]);
			graph[dst][src] = std::min(weight, graph[dst][src]);
		} 
	}

	// finding minimum spanning tree
	int current_v = 1;
	v_check[1] = 1;
	int num_v = 1;
	long long total_weight = 0;
	while (num_v < v) {
		for (auto& ee : graph[current_v]) {
			if(!v_check[ee.first])
				edges.emplace(edge{ ee.first, ee.second });
		}


		while (v_check[edges.top().dst]) {
			edges.pop();
		}

		current_v = edges.top().dst;
		total_weight += edges.top().weight;
		v_check[current_v] = 1;
		++num_v;

		edges.pop();
	}

	std::cout << total_weight; 
}
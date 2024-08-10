#include<iostream>
#include<vector>
#include<algorithm>

struct item {
    int boxnum, weight;
};

struct box {
	int itemnum;
	std::vector<int> items;
};
 
int main(void) {
    int n;

    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    std::cin >> n;

	std::vector<item> items(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> items[i].boxnum;
	}
	for (int i = 0; i < n; ++i) {
		std::cin >> items[i].weight;
	}

	std::vector<std::vector<int>> boxes(n, std::vector<int>(0));
	for (int i = 0; i < n; ++i) {
		boxes[items[i].boxnum-1].push_back(items[i].weight);
	}
	long long cost = 0;
	for (int i = 0; i < n; ++i) {
		if (boxes[i].size() >= 2) {
			std::sort(boxes[i].begin(), boxes[i].end());
			for (int j = 0; j < boxes[i].size() - 1; ++j) {
				cost += boxes[i][j];
			} 
		}
	}
	std::cout << cost;
 }
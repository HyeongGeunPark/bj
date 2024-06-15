#include<iostream>
#include<vector>
#include<algorithm>

struct card {
	int num, str, cost;
	friend std::ostream& operator<<(std::ostream& os, const card& c) {
		std::cout << c.num << ' ' << c.str << ' ' << c.cost;
		return os;
	}
};

int main(void) {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);
	int n;
	std::cin >> n;

	std::vector<card> cards;
	std::vector<int> results;

	for (int i = 1; i <= n ; ++i) {
		int str, cost;
		std::cin >> str >> cost;
		cards.emplace_back(card{ i,str,cost });
	}

	std::sort(cards.begin(), cards.end(),
		[](const card& a, const card& b) {
			return a.str > b.str;
		});

	int cur_cost = 1e9 + 100;
	for (auto e : cards) {
		if (e.cost > cur_cost) continue;
		cur_cost = e.cost;
		results.push_back(e.num);
	}

	std::sort(results.begin(), results.end());
	std::cout << results.size() << '\n';
	for (auto i : results) {
		std::cout << i << ' ';
	}
}
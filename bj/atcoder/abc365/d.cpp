#include<iostream>
#include<vector>
#include<algorithm>

enum janken {
	rock = 0, scissors, paper
};

int main(void) {
	int n;
	std::cin >> n;
	std::vector<char> aoki(n);
	for (int i = 0; i < n; ++i)
		std::cin >> aoki[i];

	std::vector<int> prev(3, 0), next(3);

	for (int i = 0; i < n; ++i) {
		next[0] = std::max(prev[1], prev[2]);
		next[1] = std::max(prev[2], prev[0]);
		next[2] = std::max(prev[0], prev[1]);

		if (aoki[i] == 'R') {
			next[1] = 0;
			++next[2];
		}
		else if (aoki[i] == 'S') {
			next[2] = 0;
			++next[0];
		}
		else {
			next[0] = 0;
			++next[1];
		} 
		prev = next;
	}

	std::cout << *std::max_element(prev.begin(), prev.end());

}

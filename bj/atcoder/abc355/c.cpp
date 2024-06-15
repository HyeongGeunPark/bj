#include<iostream>
#include<vector>

int n, t;

struct vec2 {
	int i, j;
};

inline vec2 value2vec(int a) {
	return vec2{ a / n, a % n};
}

// 0 = top left -> bottom right, 1 = top right -> bottom left
// 2 = not diag
 
int main(void) {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);
	std::cin >> n >> t;

	std::vector<int> rowbingo(n, 0);
	std::vector<int> colbingo(n, 0);
	std::vector<int> diagbingo(2, 0);

	for (int i = 1; i <= t; ++i) {
		int a;
		std::cin >> a;
		vec2 v = value2vec(a-1);

		rowbingo[v.i]++;
		if (rowbingo[v.i] == n) {
			std::cout << i; return 0;
		}
		colbingo[v.j]++;
		if (colbingo[v.j] == n) {
			std::cout << i; return 0;
		}

		if (v.i == v.j) {
			if (++diagbingo[0] == n) {
				std::cout << i; return 0;
			}
		}
		if ((v.i + v.j) == (n - 1)) {
			if (++diagbingo[1] == n) {
				std::cout << i; return 0;
			}
		}
	} 
	std::cout << -1;
	return 0;
}
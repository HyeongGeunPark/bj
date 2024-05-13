#include<iostream>

int main(void) {
	int n, k; 
	std::cin >> n >> k;
	int cnt = 0;
	int empty_seats = k;
	for (int i = 0; i < n; ++i) {
		int temp;
		std::cin >> temp;
		if (empty_seats >= temp) {
			empty_seats -= temp;
		}
		else {
			++cnt;
			empty_seats = k - temp;
		}
	}
	if (empty_seats != k) {
		++cnt;
	}

	std::cout << cnt;
}
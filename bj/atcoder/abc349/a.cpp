#include<iostream>

int main(void) {
	int n;
	int score_sum = 0;
	std::cin >> n;

	for (int i = 0; i < n - 1; ++i) {
		int temp;
		std::cin >> temp;
		score_sum += temp;
	}

	std::cout << -score_sum; 

}
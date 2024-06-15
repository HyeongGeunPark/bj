#include<iostream>
#include<vector>
#include<algorithm>

int main(void) {
	int n;
	std::cin >> n;
	constexpr int amax = 1'000'000;
	std::vector<int> count(amax + 1, 0);
	for (int i = 0; i < n; ++i) {
		int temp;
		std::cin >> temp;
		++count[temp];
	} 
	for (int i = 0; i < amax; ++i) {
		count[i + 1] += count[i];
	}
	unsigned long long result = 0;

	for (int i = 1; i <= amax; ++i) {
		long long c = count[i] - count[i - 1];
		if (c == 0) continue;
		for (int j = 2; (j-1)*i-1 <= amax; ++j) {
			result += (long long)(j-1) * c * (count[std::min(j * i - 1, amax)] - count[(j-1)*i - 1]);
		}
		if (c > 1) {
			result -= (c * (c - 1)) / 2;
		}
	}

	std::cout << result - n; 
}
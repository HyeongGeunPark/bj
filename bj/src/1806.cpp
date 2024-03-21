/*

bj1806 부분합

양쪽에서 더 작은걸 없애나가면 되나?

*/

#include<iostream>
#include<vector>

int main() {
	int n, s;
	std::cin >> n >> s;

	std::vector<int> arr;
	arr.reserve(n);

	int partial_sum = 0;
	for (int i = 0; i < n; ++i) {
		int temp;
		std::cin >> temp;
		arr.push_back(temp);
		partial_sum += temp;
	}
	auto p1 = arr.cbegin();
	auto p2 = arr.cend() - 1;

	while (p1 < p2) {
		auto& smaller = (*p1 < *p2) ? p1 : p2;

	}



}


/*
bj30804 과일 탕후루
moving window.
*/
#include<iostream>
#include<vector>
 
int main(void) {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	int n;
	std::cin >> n;
	std::vector<int> arr(n);
	for (auto& i : arr)
		std::cin >> i;

	std::vector<int> fruits(10, 0);
	int fruits_used = 0;
	int max_length = 0;
	auto left = arr.begin();

	for (auto right = left; right != arr.end(); ++right) {
		fruits[*right]++;
		if (fruits[*right] == 1)
			fruits_used++;
		while (fruits_used > 2) {
			fruits[*left]--;
			if (fruits[*left] == 0)
				fruits_used--;
			left++;
		}
		max_length = std::max(max_length, static_cast<int>(right - left + 1));
	}
	std::cout << max_length;
}
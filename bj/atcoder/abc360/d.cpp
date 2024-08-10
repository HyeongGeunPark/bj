#include<iostream>
#include<vector>
#include<algorithm>

// s[i]=='0' -> moving toward negative(left)
// s[i]=='1' -> moving toward positive(right)

int main(void) {
	long long n, t;
	std::string s;
	std::cin >> n >> t >> s;
	std::vector<long long> left_ants;
	std::vector<long long> right_ants;
	for (long long i = 0; i < n; ++i) {
		long long temp;
		std::cin >> temp;
		if (s[i] == '0') {
			left_ants.push_back(temp);
		}
		else {
			right_ants.push_back(temp);
		}
	}
	std::sort(left_ants.begin(), left_ants.end());
	long long result = 0;
	for (auto init_position : right_ants) {
		auto l = std::lower_bound(left_ants.begin(), left_ants.end(), init_position);
		auto r = std::upper_bound(left_ants.begin(), left_ants.end(), init_position + 2*t);
		result += std::distance(l, r);
	}

	std::cout << result; 
}
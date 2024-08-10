#include<iostream>
#include<vector>
#include<cmath>

int main(void) {
	int n, t, p;
	std::cin >> n;
	std::vector<double> shirts(6);
	for (auto& d : shirts)
		std::cin >> d;
	std::cin >> t >> p;
	int shirts_bundle = 0;
	for (auto d : shirts) {
		shirts_bundle += static_cast<int>(std::ceil(d / t));
	}
	std::cout << shirts_bundle << '\n';
	std::cout << n / p << ' ' << n % p << '\n';
}
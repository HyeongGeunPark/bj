#include<iostream>
#include<vector>
#include<algorithm>

using ll = unsigned long long;

constexpr ll MOD = 100'000'000;

int main(void) {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	int n;
	std::cin >> n;
	ll result = 0;

	std::vector<ll> a(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
		result += a[i];
	}
	result *= (n - 1);

	std::sort(a.begin(), a.end());
	for (int i = 0; i < n; ++i) {
		int r = MOD - a[i]; 
		auto iter = std::lower_bound(a.begin() + i, a.end(), r);
		int mul = (int)(a.end() - iter);
		if (iter <= (a.begin() + i)) {
			mul = (n - i - 1);
		}
		result -= mul * MOD;
	}

	std::cout << result; 
}
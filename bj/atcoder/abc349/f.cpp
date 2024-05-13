#include<iostream>
#include<vector>
#include<numeric>
#include<bit>

using ll = long long;
constexpr ll MOD = 998244353;

ll modpow2(int n, ll mod) {
	ll result = 1;
	ll temp = 2;
	while (n) {
		if (n & 1) {
			result *= temp;
			result %= mod;
		}
		temp *= temp;
		temp %= mod;
		n >>= 1; 
	} 

	return result;
}

void factor(std::vector<ll>& result, ll n) {
	// basic trial-division
	result.clear();

	for (ll i = 2; i*i <= n; ++i) {
		ll s = 1;
		while (n % i == 0) {
			n /= i;
			s *= i; 
		}
		if(s!=1)
			result.push_back(s); 
	}
	if (n != 1)
		result.push_back(n);
}

int main(void) {

	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	std::vector<ll> factors;
	ll n, m;

	std::cin >> n >> m;

	factor(factors, m);
	std::vector<int> cnt(1 << factors.size(), 0);

	for (int i = 0; i < n; ++i) {
		ll temp;
		std::cin >> temp;

		if ((m % temp) != 0) continue;

		int mask = 0;
		for (int j = 0; j < factors.size(); ++j) {
			if (temp % factors[j] == 0)
				mask |= (1 << j); 
		} 
		++cnt[mask];
	}

	ll ans = m==1?-1:0;

	for (unsigned int mask = 0; mask < cnt.size(); ++mask) {
		int sign = (factors.size() - std::popcount(mask)) % 2? -1 : 1;
		int x = 0;
		for (int subset = 0; subset < cnt.size(); ++subset) {
			if ((mask & subset) == subset)
				x += cnt[subset];
		}
		ans += sign * modpow2(x, MOD); 
		ans %= MOD;
	}
	if (ans < 0) ans += MOD;

	std::cout << ans; 
}

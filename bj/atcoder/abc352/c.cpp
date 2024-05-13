#include<iostream>
#include<vector>
#include<algorithm>

int main(void) {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);
	using ll = long long;
	int n;
	std::cin >> n;
	ll total_s = 0;
	std::vector<ll> h_s(n);
	for(int i=0;i<n;++i){
		ll a, b;
		std::cin >> a >> b;
		total_s += a;
		h_s[i] = (b - a);
	}

	std::sort(h_s.begin(), h_s.end());
	std::cout << total_s + h_s.back(); 
}
#include<iostream>

int main(void) {
	long long a, b, c, d;
	long long result = 0;
	std::cin >> a >> b >> c >> d;
	long long h = d - b;
	long long w = c - a;
	long long w4 = w - w % 4;
	result += h * w4; 

	long long h_table[4] = { 3, 3, 1, 1 };
	long long piece_table[4][2] = {
		{2, 1}, {1, 2}, {0, 1}, {1, 0}
	};

	for (long long k = a + w4; k < c; ++k) {
		long long kk = k % 4;
		kk = (kk < 0 ? kk + 4 : kk);
		long long h2 = h - h % 2;
		result += h_table[kk] * (h2 / 2);
		if (h2 != h) {
			long long ll = (b + h2) % 2;
			ll = (ll < 0 ? ll + 2 : ll);
			result += piece_table[kk][ll]; 
		}
	}
	std::cout << result;
}
/*
bj14609 구분구적법(Large)

일단 문제를 풀려면 실제 적분값을 구해야 한다.

1. 실제 적분값
다항식이므로, 원시함수를 쉽게 구할 수 있으며 이를 이용해 계산한다.

그 후 epsilon 값을 바이너리 서치로 주어진 범위 안에서 찾으면 된다.

다항식이며, 모두 양의 계수를 가지고, 적분 범위 [a, b)에서 a, b는 양수이므로
이 구간에서 단조 증가하는 함수이므로, 구분구적법으로 구한 값은 epsilon에 대해
단조 증가하는 함수라는 것을 이용한다.
 */

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

double polynomial_value(double x, const std::vector<double>& coeffs) {
	double result = 0.0l;
	int i = 0;
	double x_n = 1;
	while (i < coeffs.size()) {
		result += x_n * coeffs[i];
		x_n *= x;
		++i;
	}
	return result;
}

double approx_integral(double a, double b, double epsilon, int n, const std::vector<double>& coeffs)
{
	double result = 0.0l;
	double delta_x = (b - a) / n;
	for (int i = 0; i < n; ++i) {
		result += polynomial_value(a + i * delta_x + epsilon, coeffs) * delta_x;
	}
	return result; 
}

int main(void) {
	int k;
	std::cin >> k;

	std::vector<double> coeff(k+1, 0);
	// 최고차항부터 내림차순으로
	for (int i = k; i >= 0; --i) {
		std::cin >> coeff[i];
	}

	double a, b, n;
	std::cin >> a >> b >> n;

	// 원시함수 구해서 실제 적분값 구하기
	// 문제에 나와 있는 식을 그대로 사용한다.
	double exact_value = 0;

	{ 
		double a_i = a;
		double b_i = b;
		for (int i = 0; i <= k; ++i) {
			exact_value += coeff[i] * (b_i - a_i) / (i + 1);
			a_i *= a;
			b_i *= b;
		}
	}

	// binary search
	// 0 <= epsilon <= (b-a)/n
	// 단조증가라서 epsilon 값이 존재하지 않는 경우는 없을 것 같다.
	// 만일을 위해 확인한다.  
	assert(approx_integral(a, b, 0, n, coeff) <= exact_value);
	assert(approx_integral(a, b, (b - a) / n, n, coeff) >= exact_value);

	double mid;
	//int iteration = 0;
	{
		double l = 0;
		double r = (b - a) / n;
		while (true) {
			mid = (r + l) / 2;
			double approx_value = approx_integral(a, b, mid, n, coeff);
			if (std::abs(exact_value - approx_value) <= 0.0001) {
				break;
			} 
			else if (exact_value > approx_value) {
				l = mid;
			}
			else if (exact_value < approx_value) {
				r = mid;
			}
			//++iteration;
		} 
	}

	std::cout << mid << '\n';

	return 0;

}
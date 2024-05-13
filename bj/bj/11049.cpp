/*

bj11049 Çà·Ä °ö¼À ¼ø¼­

Á¢±Ù¹ý(dp)

F(0, n) =
	min(
		dim(0)*dim(1)*dim(n) + F(0,1) + F(1,n),
		dim(0)*dim(2)*dim(n) + F(0,2) + F(2,n),
		...
		dim(0)*dim(n-1)*dim(n) + F(0,n-1) + F(n-1,n)
	)

F(i, j) = 0 (j-i < 2)

*/


#include<iostream>
#include<limits>

unsigned int dim[501];

unsigned int mem[501][501];

unsigned int foo(int i, int j) {
	if (j - i < 2) return 0;
	if (mem[i][j]) return mem[i][j];

	unsigned int result = std::numeric_limits<unsigned int>::max();
	for (int k = i + 1; k < j; ++k) {
		result = std::min(
			result,
			dim[i] * dim[k] * dim[j] + foo(i, k) + foo(k, j)
		);
	}
	mem[i][j] = result;
	return result; 
}

int main(void) {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	int n;
	std::cin >> n;
	for (int i = 2; i <= n; ++i) {
		mem[i - 2][i] = dim[i - 2] * dim[i - 1] * dim[i];
	}
	for (int i = 0; i < n; ++i) {
		std::cin >> dim[i];
		std::cin >> dim[i + 1]; 
	}

	std::cout << foo(0, n);

}


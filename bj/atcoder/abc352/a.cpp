#include<iostream>

int main(void) {
	int n, x, y, z;
	std::cin >> n >> x >> y >> z;
	if (x > y) {
		std::swap(x, y);
	}
	if (x < z && z < y) {
		std::cout << "Yes";
	}
	else {
		std::cout << "No";
	}
}
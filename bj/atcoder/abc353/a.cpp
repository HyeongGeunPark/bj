#include<iostream> 

int main(void) {

	int n;
	std::cin >> n;
	int first_one;
	std::cin >> first_one;
	int result = -1;


	for (int i = 2; i <= n; ++i) {
		int temp;
		std::cin >> temp;
		if (temp > first_one) {
			result = i;
			break;
		}
	}

	std::cout << result; 
}
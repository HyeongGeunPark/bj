/*
bj28702
연속으로 주는 세 문자열 중 하나는 반드시 숫자이다.  
*/
#include<iostream>
#include<sstream>
#include<vector>

void fizzbuzzout(int n) {
	if (n % 3 == 0) {
		std::cout << "Fizz";
	}
	if (n % 5 == 0) {
		std::cout << "Buzz";
	}
	if (n % 3 != 0 && n % 5 != 0) {
		std::cout << n;
	}
	std::cout << '\n';
}


int main(void) {
	std::vector<std::string> buf(3);
	for (auto& b : buf)
		std::cin >> b;
	int next_number = 0;
	for (int i = 0; i < 3; ++i) {
		std::stringstream ss{ buf[i] };
		if (std::isdigit(ss.peek())) {
			ss >> next_number;
			next_number += (3 - i);
			break;
		}
		
	} 
	fizzbuzzout(next_number);
}
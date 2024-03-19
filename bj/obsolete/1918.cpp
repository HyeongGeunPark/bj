#include<iostream>
#include<vector>
#include<unordered_map>

std::vector<char> operators;
std::unordered_map<char, char> precedence = {
	{'*', 0}, {'/', 0}, {'+', 1}, {'-', 1}, {'(', 2}
};

int main() {
	operators.reserve(100);
	std::cin >> std::noskipws;
	for (char input = 0; std::cin >> input;) {
		if (input == '\n') break;
		if (isspace(input)) continue;
		switch (input)
		{
		case '(':
			operators.push_back(input);
			break;
		case ')':
			while (!operators.empty() && operators.back() != '(') {
				std::cout << operators.back();
				operators.pop_back(); 
			}
			operators.pop_back();
			break;
		case '+': case '-': case '*': case '/':
			while (!operators.empty() && precedence[operators.back()] <= precedence[input]) {
				std::cout << operators.back();
				operators.pop_back();
			}
			operators.push_back(input);
			break;
		default:
			std::cout << input;
			break;
		}
	}
	while (!operators.empty()) {
		std::cout << operators.back();
		operators.pop_back();
	}
}

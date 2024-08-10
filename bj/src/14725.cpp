/*
bj14725 개미굴

접근 : 트라이
입력으로 트라이를 구축하면 된다.
단, 문자열을 키로 한다.
*/

#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<string>

struct Trie {
	std::map<std::string, Trie> child;

	void insert(std::vector<std::string>::iterator b, std::vector<std::string>::iterator e) { 
		if (b == e) return;
		child[*b].insert(b + 1, e); 
	}

	void print(int depth = 0) {
		for (auto [key, subtrie] : child) {
			for (int i = 0; i < depth; ++i) {
				std::cout << "--";
			}
			std::cout << key << '\n';
			subtrie.print(depth + 1);
		}
	}
};

int main(void) {
	int n;
	std::cin >> n;
	Trie head;
	for (int i = 0; i < n; ++i) {
		std::vector<std::string> input;
		int depth;
		std::cin >> depth;
		for (int j = 0; j < depth; ++j) {
			std::string s;
			std::cin >> s;
			input.push_back(s); 
		}
		head.insert(input.begin(), input.end());
	}
	head.print();
}
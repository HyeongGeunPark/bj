#include<iostream>

int main(void) {
	std::string s, t;
	std::cin >> s >> t;

	for (int i = 0; i < 3; ++i) {
		t[i] = std::tolower(t[i]);
	}

	int search_len=3;
	if (t[2] == 'x') search_len = 2;

	int idx = 0;
	for (char c : s) {
		if (c == t[idx]) {
			++idx;
			if (idx == search_len) {
				std::cout << "Yes";
				return 0 ;
			}
		} 
	}
	std::cout << "No";
	return 0;
}
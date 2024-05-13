/*

bj31628 가지 한 두름 주세요 
 
*/
#include<iostream>
#include<string>

std::string map[10][10];
int main(void) {
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			std::cin >> map[i][j];
		}
	}

	int answer = 0;

	// row
	for (int i = 0; i < 10; ++i) {
		answer = 1;
		for (int j = 0; j < 9; ++j) {
			if (map[i][j] != map[i][j + 1]) {
				answer = 0; break;
			}
		}
		if (answer == 1) goto print;
	}
	//column
	for (int i = 0; i < 10; ++i) {
		answer = 1;
		for (int j = 0; j < 9; ++j) {
			if (map[j][i] != map[j + 1][i]) {
				answer = 0; break;
			}
		}
		if (answer == 1) goto print;
	}

print:
	std::cout << answer;
}
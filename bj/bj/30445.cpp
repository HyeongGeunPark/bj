/*
bj30445 행복 점수

문자열 처리

입력
1행의 문자열. 알파벳 대문자로만 이루어져 있음.

출력
행복 지수를 계산하여 출력.
(행복 지수) = P_H / (P_H + P_G)
			= 0.5 (P_H == 0 && P_G == 0)
P_H = (H, A, P, Y의 갯수)
P_G = (S, A, D의 갯수)

*반올림 문제*
실수 오차에 의한 반올림 문제가 있으므로, 정수 연산을 사용한다.

*/

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

int main(void) {
	std::string input;
	std::getline(std::cin, input);

	int ph_arr[26] = { 0, };
	int pg_arr[26] = { 0, };

	ph_arr['H' - 'A'] = 1;
	ph_arr['A' - 'A'] = 1;
	ph_arr['P' - 'A'] = 1;
	ph_arr['Y' - 'A'] = 1;

	pg_arr['S' - 'A'] = 1;
	pg_arr['A' - 'A'] = 1;
	pg_arr['D' - 'A'] = 1;

	int ph = 0;
	int pg = 0;
	for (char c : input) {
		if (c == ' ') continue;
		ph += ph_arr[c - 'A'];
		pg += pg_arr[c - 'A'];
	}

	if ((ph + pg) == 0) {
		std::cout << "50.00" << '\n';
	}
	else {
		int happiness_index = (ph * 100000) / (ph + pg);

		if (happiness_index % 10 >= 5) {
			happiness_index /= 10;
			happiness_index += 1;
		}
		else {
			happiness_index /= 10;
		}

		int divisor = 1000;
		int result[4];
		for (int i = 0; i < 4; ++i) {
			result[i] = happiness_index / divisor;
			happiness_index %= divisor;
			divisor /= 10;
		}

		if (result[0] != 0) {
			std::cout << result[0];
		}
		std::cout << result[1] << '.' << result[2] << result[3] << '\n'; 
	}

	return 0;
}
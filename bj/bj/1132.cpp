/*
bj1132 합

n개 수가 주어진다. 각 자리수는 A-J의 알파벳으로 주어지며 각 알파벳은 0-9의 수에 대응한다.
주어진 수들의 합의 최대값을 구하여라.

접근법(그리디)
1. 각 알파벳의 '가중치'를 구한다.
2. 가중치 = (자릿수 * 등장 횟수)의 총합
3. 동시에 0이 될 수 없는 알파벳도 체크한다. -> 0이 될 수 있는 알파벳으로 변환.
4. 가중치가 높은 순서부터 9, 8, 7... 순서로 할당한다.
5. 할당하기 전에 0이 될 수 있는 알파벳이 하나밖에 남지 않았는지 체크하고,
	그런 경우 우선적으로 그 알파벳에 0을 할당한다.

주의점
1. 0으로 시작하는 수는 없다.
2. 가중치와 최종 결과는 10^12 범위를 넘어갈 수 있다. -> long long(최소 64bit 사용)
*/

#include <iostream>
#include <vector>
#include <bitset>
#include <bit>
#include <ranges>
#include <algorithm>

int main() {

	std::vector<long long> weight(10, 0);

	std::bitset<10> can_be_zero;
	can_be_zero.set();

	int n;
	std::cin >> n;

	for(int i=0;i<n;++i){
		std::string str;
		std::cin >> str;
		int j = 0;
		long long position = 1;
		while (j != str.size()) {
			int c = str[str.size() - 1 - j] - 'A';
			weight[c] += position;
			position *= 10;
			++j;
		}
		can_be_zero.reset(str.front() - 'A');
	}

	std::vector<std::pair<long long, int>> weight_char_pair(10);
	for(int i=0;i<10;++i){
		weight_char_pair[i] = { weight[i], i };
	}

	std::ranges::sort(weight_char_pair);



	std::vector<int> char_to_digit(10, -1);


	int current = 9;
	auto it = weight_char_pair.rbegin();
	while (it != weight_char_pair.rend())
	{
		auto [weight, c] = *it;

		if (can_be_zero.count() == 1) {
			int cc = std::countr_zero(can_be_zero.to_ulong());
			char_to_digit[cc] = 0;
			can_be_zero.reset(cc);
		}

		if(char_to_digit[c] == -1) {
			char_to_digit[c] = current--;
			can_be_zero.reset(c);
		}
		++it;
	}

	long long result = 0;
	for (auto [weight, c] : weight_char_pair) {
		result += char_to_digit[c] * weight;
	}

	std::cout << result << std::endl;
}
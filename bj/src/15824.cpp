/*
bj15824 너 봄에는 캡사이신이 맛있단다

음식점의 모든 메뉴의 조합에 따른 "주헌고통지수"의 합을 구한다.
주헌고통지수란, 메뉴에 포함된 가장 매운 음식과 맵지 않은 음식의
스코빌 지수 차이를 말한다.

메뉴 개수 n <= 3000
답을 1'000'000'007로 나눈 나머지를 출력한다.

접근법: DP?

메뉴을 매운 순으로 정리한다.

mem[n]을 n번째 메뉴가 가장 매운 메뉴로 포함된 메뉴 조합의 "주헌고통지수" 합이라 정의한다.

mem[0] = 0
mem[n] = (2^n-1) * (menu[n]-menu[n-1]) + mem[0] + ... + mem[n-1]

답은
mem[0] + mem[1] + ... mem[n-1].  
*/ 

#include<iostream>
#include<vector>
#include<algorithm>

constexpr int MOD = 1'000'000'007; 

int main(void) {
	int n;
	std::cin >> n;
	std::vector<int> menu;
	for (int i = 0; i < n; ++i) {
		int temp;
		std::cin >> temp;
		menu.push_back(temp); 
	}

	std::ranges::sort(menu);
	std::vector<int> mem{ 0 };
	std::vector<int> sum{ 0 };
	long long pow = 2;

	for (int i = 1; i < n; ++i) {
		value %= MOD;
		value += sum[i - 1];
		value %= MOD;
		mem.push_back(value);
		value += sum[i - 1];
		value %= MOD;
		sum.push_back(value); 
		pow <<= 1;
		pow %= MOD;
	} 
	std::cout << sum[n-1]; 
}


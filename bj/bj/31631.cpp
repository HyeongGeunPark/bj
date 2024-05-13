/*

bj31631 :rightplant:

�� �����غ��� ������ �����ϴ� ���¸� �׳� ���� �� �ִ�.

*/

#include<iostream>
#include<vector>

constexpr int TO_RP = 0;
constexpr int TO_LP = 1;

int main(void) {
	int n;
	std::cin >> n;
	std::vector<int> answer(n);
	int lp = 0, rp = n - 1;
	int current = TO_RP;
	int cnt = 1;
	while (n) {
		while (cnt && n) {
			if (current == TO_RP) {
				answer[rp--] = n--;
				--cnt;
			}
			else {
				answer[lp++] = n--;
				--cnt;
			}
		}
		current ^= 1;
		cnt = 2; 
	}

	for (int i : answer) {
		std::cout << i << ' ';
	}

}
/*

bj10775 ����

���ٹ�: �׸���

i��° ������ 1~gi�� ����Ʈ�� ��ŷ�� �� �ִ�.
�ִ��� ū ��ȣ�� ����Ʈ�� ��ŷ�Ѵ�.  

�ӵ� ����� ���� ��� ������ �ʿ��ϴ�.

���Ͽ� ���ε带 ����� ���� �ִ�. (�ڵ� ������ �ٸ� ���̴�.)

*/

#include<iostream>

int next_available[100001];
inline int find_next(int i) {
	if (next_available[i] == i) {
		--next_available[i];
		return i;
	}
	// ��� ����
	next_available[i] = find_next(next_available[i]);
	return next_available[i]; 
}

int main(void) {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	int g, p;
	int cnt = 0;
	std::cin >> g >> p;
	for (int i = 0; i <= g; ++i) {
		next_available[i] = i;
	}



	for (int i = 0; i < p; ++i) {
		int gg;
		std::cin >> gg;
		if (find_next(gg) == 0) break;
		++cnt;
	}

	std::cout << cnt; 
}
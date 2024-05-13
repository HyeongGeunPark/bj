/*

bj9527 1�� ���� ����

���ٹ�: ��Ģ�� ã�� ���.

��������� ������ ���� �ִ�.


*/

#include<iostream>

using ll = long long;
constexpr int MAX_OFFSET = 55;

ll one_count(ll n) {
	ll offset = MAX_OFFSET;
	ll result = 0;
	ll cnt = 0;
	while (offset--) {
		ll mask = (((ll)1) << offset);
		if (n & mask) {
			result += offset * (mask >> 1) + cnt * mask; 
			cnt++;
		} 
	}
	result += cnt;
	return result; 
}

int main(void) {
	ll a, b;
	std::cin >> a >> b;
	std::cout << one_count(b) - one_count(a-1) << '\n';
}

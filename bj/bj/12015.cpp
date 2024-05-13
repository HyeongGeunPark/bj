/*

bj12015 ���� �� �����ϴ� �κ� ���� 2

������ ũ�Ⱑ 1'000'000���� �þ��.
������ n^2 �˰������δ� �Ұ����ϴ�.

���ٹ�: �̺�Ž��

1. �Է��� �ϳ��� �޴´�.
2. ���� ���� �Է��� vector�� ������ ���Һ��� ���ų� ���� ���,
	���ݱ��� ���� �Է� �� ���� ���� �Էº��� ���ų� ū �� �� ���� ���� ��(lower bound)��
	���� ���� �Է����� ��ü�Ѵ�.  
3. �׷��� ���� ��� ���� �������� ���� ���� �Է��� �߰��Ѵ�.
4. ������ �Է±��� �ݺ��Ѵ�.

vector[i] = ���� i�� �����ϴ� �κ� ������ ���� �� �ִ� ���� ���� ������ ������ ��



*/

#include<iostream>
#include<vector>
#include<algorithm>

int main(void) {

	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	int n, temp;
	std::cin >> n;
	std::vector<int> lis;
	std::cin >> temp;
	lis.push_back(temp);
	for (int i = 1; i < n; ++i) {
		std::cin >> temp;

		if (temp <= lis.back()) {
			*std::lower_bound(lis.begin(), lis.end(), temp) = temp;
		} 
		else {
			lis.push_back(temp);
		}
	}

	std::cout << lis.size();
}
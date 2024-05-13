/*

bj2252 �� �����

���ٹ�(���� ����- ����, DFS)
1. Ű �� �����͸� �Է¹޴´�. (�� �л����� �ڽź��� Ű�� ���� �л��� �������� ��� �ð��� �� �� �ֵ���)
2. �л����� ��ȣ�� �ϳ��ϳ� ����Ѵ�.
	�� ����ϱ� ���� �ڽź��� Ű�� ���� �л��� ���� ����Ѵ�.(����� ����)

�ٸ� ���ٹ�(���� ����- ť, Kahn �˰���)
1. Ű �� �����͸� ���� �׷����� �����Ѵ�.
2. �����ϸ鼭 Ű�� ū �л��� 'degree'�� �ϳ��� �ø���.
3. ��������� degree�� �ڽź��� ��������� ���� �л��� ���� �����Ѵ�.
4. degree�� 0�� �л��� �켱 queue�� ��´�.
5. ť���� �� �л��� ���� ����Ѵ�.
6. �� �л����� ��������� Ű�� ū �л��� degree�� �ϳ��� ���δ�.
7. ���� degree�� 0�� �Ǿ��ٸ� �� �л��� queue�� ��´�.
8. queue�� �� ������ 5-7 �ݺ�.

*/

#include<iostream>
#include<vector>

std::vector<std::vector<int>> comparision;
std::vector<bool> printed;

void print(int n) {
	if (printed[n]) return;
	while (comparision[n].size()) {
		int s = comparision[n].back();
		print(s);
		comparision[n].pop_back(); 
	}
	std::cout << n << ' ';
	printed[n] = true; 
}


int main() {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	int n, m;
	std::cin >> n >> m;
	comparision.resize(n + 1);
	printed.resize(n + 1, false);

	for (int i = 0; i < m; ++i) {
		int smaller, taller;
		std::cin >> smaller >> taller;
		comparision[taller].push_back(smaller);
	}

	for (int i = 1; i <= n; ++i) {
		print(i);
	}
}
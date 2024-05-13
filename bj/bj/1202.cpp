/*

bj1202 ���� ����

���ٹ�: �׸���

���� ���� ������� ä�� ������.
�ش� ���濡 ���� �� �ִ� ���� ���� ������ ��´�.

1. ������ �����Ѵ�.
2. ������ ���Լ����� �����Ѵ�.
3. �켱���� ť�� �غ��Ѵ�. �� ť�� ���� ��ġ�� ���ĵȴ�.

4. ������ ���� �ͺ��� ä�� ������.
	4-1. �켱���� ť�� �� ���濡 ���� �� �ִ� ������ ��� ��´�.
	4-2. �켱���� ť���� ���� ��ġ�ִ� ������ ������. �� ������ ��ġ�� ����� ���Ѵ�.
	4-3. ��� ���濡 ���� ���� �ݺ��Ѵ�.

����/���� �ִ밪�� 300'000, ���� ��ġ�� �ִ밪�� 100'000'000�̹Ƿ�
�����÷ο쿡 �����Ѵ�.

*/

#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

struct gem {
	int m, v;
};

bool gem_compare(const gem& g1, const gem& g2){
	return g1.m < g2.m;
} 

struct pq_compare {
	bool operator()(const gem& g1, const gem& g2) {
		return g1.v < g2.v;
	}
};

int main(void) {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	int n, k;
	std::cin >> n >> k;

	std::vector<gem> gems;
	for (int i = 0; i < n; ++i) {
		int mm, vv;
		std::cin >> mm >> vv;
		gems.emplace_back(gem{ mm,vv });
	}

	std::vector<int> bags;
	for (int i = 0; i < k; ++i) {
		int temp;
		std::cin >> temp;
		bags.push_back(temp);
	}

	std::sort(gems.begin(), gems.end(), gem_compare);
	std::sort(bags.begin(), bags.end());

	std::priority_queue<gem, std::vector<gem>, pq_compare> p;

	int gem_index = 0;
	long long result = 0;
	for (int i = 0; i < k; ++i) {
		while (gem_index < n) {
			if (gems[gem_index].m > bags[i]) break;
			p.push(gems[gem_index++]);
		}
		if (!p.empty()) {
			result += p.top().v;
			p.pop();
		} 
	}

	std::cout << result; 
}
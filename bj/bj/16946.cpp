/*

bj16946 �� �μ��� �̵��ϱ� 4

��� ���� ���� ������ ����Ѵ�.

1. ������ ���� �μ���.
2. �� ��ġ���� �̵� ������ ĭ�� ������ ���� ����.

�� ũ��: 1000*1000 

���ٹ�:
1. �ʿ� �����ϴ� ������ 0 �׷�鿡 ���� ��ȣ�� �ű�� �׷��� ũ�⸦ ���Ѵ�. (DFS)
2. �ʿ� �����ϴ� ��� ���� ���� ���� ������ �׷��� ��ȣ�� �˾Ƴ���.
3. �� �׷��� ũ�⸦ ���Ѵ�. �ڱ� �ڽŵ� ��ĭ�� �ǹǷ� 1�� �߰��� ���Ѵ�.
*/

#include<iostream>
#include<vector>
#include<algorithm>
 
constexpr int NMAX = 1000;
int map[NMAX][NMAX];

inline bool is_in_range(int i, int j, int n, int m) {
	return 0 <= i && i < n && 0 <= j && j < m;
}

int main(void) {

	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	int n, m;

	// �� �Է�
	std::cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			char c;
			std::cin >> c;
			map[i][j] = c - '0';
		}
	}

	int direction[4][2] = {
		{-1,0}, {1,0}, {0,-1}, {0,1}
	};

	// 0 �׷� Ž�� �� ũ�� ���ϱ�
	int group_index = 2;
	std::vector<int> zero_group_size(group_index);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (map[i][j] != 0) continue;
			std::vector<std::pair<int,int>> s;
			s.push_back(std::make_pair(i, j));
			map[i][j] = group_index;
			int size = 0;
			while (!s.empty()) {
				++size;
				std::pair<int, int> cur = s.back();
				s.pop_back();
				for (int d = 0; d < 4; ++d) {
					int ii = cur.first + direction[d][0];
					int jj = cur.second + direction[d][1];
					if (is_in_range(ii, jj, n, m) && map[ii][jj] == 0) {
						map[ii][jj] = group_index;
						s.push_back(std::make_pair(ii, jj));
					}
				}
			}
			zero_group_size.push_back(size);
			++group_index;
		}
	}


	// ��� �� ���
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (map[i][j] != 1) {
				std::cout << 0;
			}
			else {
				std::vector<int> adjacent_groups;
				for (int d = 0; d < 4; ++d) {
					int ii = direction[d][0] + i;
					int jj = direction[d][1] + j;
					if (is_in_range(ii, jj, n, m)){
						if(map[ii][jj] > 1) {
						if (std::find(adjacent_groups.begin(), adjacent_groups.end(), map[ii][jj]) == adjacent_groups.end())
							adjacent_groups.push_back(map[ii][jj]);
						}
					}
				}
				int size = 1;
				for (auto i : adjacent_groups) {
					size += zero_group_size[i];
				}
				std::cout << (size%10); 
			} 
		}
		std::cout << '\n';
	}



	

}
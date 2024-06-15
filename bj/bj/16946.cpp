/*

bj16946 벽 부수고 이동하기 4

모든 벽에 대해 다음을 계산한다.

1. 선택한 벽을 부순다.
2. 그 위치에서 이동 가능한 칸의 개수를 세어 본다.

맵 크기: 1000*1000 

접근법:
1. 맵에 존재하는 인접한 0 그룹들에 대해 번호를 매기고 그룹의 크기를 구한다. (DFS)
2. 맵에 존재하는 모든 벽에 대해 벽과 인접한 그룹의 번호를 알아낸다.
3. 각 그룹의 크기를 더한다. 자기 자신도 빈칸이 되므로 1을 추가로 더한다.
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

	// 맵 입력
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

	// 0 그룹 탐색 및 크기 구하기
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


	// 계산 및 출력
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
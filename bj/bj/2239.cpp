/*

bj2239 스도쿠

전수탐색 + 백트래킹
BFS, DFS 무엇이든 가능
DFS로 구현

시간 줄이기: 스도쿠 풀이 요령 적용(https://ko.wikihow.com/스도쿠-푸는-법)
1. 기본적인 후보 추리기
가로, 세로, 3*3 사각형 내부에는 한 숫자가 한 번만 등장함
2. 논리적인 후보 추리기
각 체크 단위 안에서 다른 빈칸 중 어느곳에도 들어갈 수 없는 수를 찾는다.
	1. 3*3 빈칸에서 공통적으로 사용하지 못하는 수를 찾는다.
	2. 가로줄 빈칸에서 공통적으로 사용하지 못하는 수를 찾는다.
	3. 세로줄 빈칸에서 공통적으로 사용하지 못하는 수를 찾는다.

3. 이후에 dfs로 나머지 칸을 채운다. (사람이 풀 수 있다면, 즉 답이 유일하면 2에서 끝난다.)
	

*/

#include<iostream>
#include<bit>

unsigned int map[9][9];	// map state: n-th bit is 1

/*
n-th bit is 1, for possible n
[0][n] for row, [1][n] for col, [2][n] for 3x3 square
-------
|0|1|2|
|3|4|5|
|6|7|8|
-------
*/
unsigned int flag[3][9];
constexpr unsigned int flag_bitmask = 0b11'1111'1110;

inline int square(int x, int y) {
	return 3 * (x / 3) + y / 3;
}
 
inline void set_flag(int x, int y) {
	flag[0][x] ^= map[x][y];
	flag[1][y] ^= map[x][y];
	flag[2][square(x, y)] ^= map[x][y];
} 

inline unsigned int get_flag(int x, int y) {
	return flag[0][x] | flag[1][y] | flag[2][square(x, y)];
}

inline unsigned int get_candidate(int x, int y) {
	unsigned int c = (~get_flag(x,y)) & flag_bitmask;
	if (std::has_single_bit(c)) return c;
	unsigned int f = c;
 
	// 3x3
	int x_base = (x / 3) * 3;
	int y_base = (y / 3) * 3;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if ((x_base + i != x || y_base + j != y) && map[x_base + i][y_base + j] == 1) {
				f &= get_flag(x_base + i, y_base + j);
			}
		}
	} 
	if (f) {
		if (std::has_single_bit(f)) return f;
		c = f;
	}
	else f = c;

	// 세로
	for (int i = 0; i < 9; ++i) {
		if (i!=x && map[i][y] == 1) {
			f &= get_flag(i, y);
		}
	}
	if (f) {
		if (std::has_single_bit(f)) return f;
		c = f;
	}
	else f = c;

	// 가로
	for (int i = 0; i < 9; ++i) {
		if (i!=y && map[x][i] == 1) {
			f &= get_flag(x, i);
		}
	}
	if (f) {
		if (std::has_single_bit(f)) return f;
		c = f;
	}
	else f = c;

	return c; 
}

inline bool check_n_set_unique() {
	bool r = false;
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			if (map[i][j] != 1) continue;
			unsigned int c = get_candidate(i, j);
			if (std::has_single_bit(c)) {
				map[i][j] = c;
				set_flag(i, j);
				r = true;
			} 
		} 
	}
	return r;
}

bool solve(int i) {
	if (i == 81) return true;
	int x = i / 9;
	int y = i % 9;
	if (map[x][y] != 1) return solve(i + 1);

	unsigned int c = get_candidate(x, y);

	for (unsigned int j = 0b10; j < (0b10 << 9); j <<= 1) {
		if (j & c) {
			map[x][y] = j;
			set_flag(x, y);
			if (solve(i + 1)) return true;
			set_flag(x, y);
		}
	}

	map[x][y] = 1;
	return false; 
}

void print_map(void) {
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			std::cout << std::countr_zero(map[i][j]);
		}
		std::cout << '\n';
	}
}

int main(void) {

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			char c;
			std::cin >> c;
			map[i][j] = 1 << (c - '0');
			if(c!='0') set_flag(i, j);
		}
	}


	while (check_n_set_unique()); 
 
	// solve remaining empty cells with dfs
	solve(0); 

	print_map(); 

}

 
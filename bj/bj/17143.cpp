/*
bj17143 낚시왕

접근법: 구현
복잡한 상태를 빨리 구현하는 것이 중요.
*/

#include<iostream>
#include<algorithm>
#include<list>
#include<vector>
#include<cstring>
 
struct vec2 {
	int x, y;
	vec2& operator=(const vec2&) = default; 
};

struct shark_property {
	vec2 pos;
	int spd, dir; 
};

class shark_set {
public:
	int r, c;
	shark_set(std::istream& is) {
		int m;
		is >> r >> c >> m;
		map = new int[100][100];
		memset(map, 0, sizeof(int) * 100 * 100);
		for (int i = 0; i < m; ++i) {
			int x, y, spd, dir, sz;
			std::cin >> x >> y >> spd >> dir >> sz;
			map[x - 1][y - 1] = sz;
			shark_movement[sz] = { {x - 1,y - 1}, spd, dir };
		} 
	}
	void move() {
		auto temp = new int[100][100];
		memset(temp, 0, sizeof(int) * 100 * 100);
		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < c; ++j) {
				if (map[i][j] != 0) {
					auto pos = _move(shark_movement[map[i][j]]);
					temp[pos.x][pos.y] = std::max(temp[pos.x][pos.y], map[i][j]);
				}
			}
		}
		delete[] map;
		map = temp;
	}
	int do_fishing(int j) {
		int val = 0;
		for (int i = 0; i < r; ++i) {
			if (map[i][j] != 0) {
				val = map[i][j];
				map[i][j] = 0;
				break;
			}
		}
		return val;
	}
	~shark_set() {
		delete[] map;
	}

private: 
	shark_property shark_movement[10001];
	int(*map)[100];
	vec2& _move(shark_property& sh) {
		vec2& pos = sh.pos;
		switch (sh.dir) {
		case 1: // up
			pos.x -= sh.spd;
			while (true) {
				if (0 > pos.x) {
					sh.dir = 2;
					pos.x = -pos.x;
				}
				else if (r <= pos.x) {
					sh.dir = 1;
					pos.x = (2 * r - 2) - pos.x;
				}
				else
					break;
			}
			break;
		case 2: // down
			pos.x += sh.spd;
			while (true) {
				if (0 > pos.x) {
					sh.dir = 2;
					pos.x = -pos.x;
				}
				else if (r <= pos.x) {
					sh.dir = 1;
					pos.x = (2 * r - 2) - pos.x;
				}
				else
					break;
			}
			break;
		case 3: // right
			pos.y += sh.spd;
			while (true) {
				if (0 > pos.y) {
					sh.dir = 3;
					pos.y = -pos.y;
				}
				else if (c <= pos.y) {
					sh.dir = 4;
					pos.y = (2 * c - 2) - pos.y;
				}
				else
					break;
			}
			break;
		case 4: // left
			pos.y -= sh.spd;
			while (true) {
				if (0 > pos.y) {
					sh.dir = 3;
					pos.y = -pos.y;
				}
				else if (c <= pos.y) {
					sh.dir = 4;
					pos.y = (2 * c - 2) - pos.y;
				}
				else
					break;
			}
			break;
		}
		return pos;
	}

};

int main(void) {
 
	int total_weight = 0;
	auto ss = shark_set(std::cin);
	for (int i = 0; i < ss.c; ++i) {
		total_weight += ss.do_fishing(i);
		ss.move();
	} 

	std::cout << total_weight;
}
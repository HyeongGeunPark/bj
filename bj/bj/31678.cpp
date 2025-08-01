/*
bj31678 bingo
다국어 그만좀...

입력
n: 사람 수 (1<=n<=50)

사람 수 만큼 다음의 입력:
1. 사람의 이름(20자 이하 영문)
2. 빙고판 (5*5)

m: 사회자가 뽑은 공의 수 (1<=m<=90)

사회자가 뽑은 공의 수 만큼의 숫자들

출력:
빙고를 완성한 사람의 이름을 출력한다.
순서는 처음에 입력을 받았던 순서대로 정렬되어 있어야 한다.

구현만 잘 하면 된다.

단, 구현을 편하게 하기 위해 다음과 같은 방법을 사용한다.

1. 빙고판의 저장은 다음과 같이 한다.
	std::pair<char, char> board[91];
	그 숫자 있는 (x, y) 좌표를 저장한다.
2. 빙고판의 상태는 다음과 같이 저장한다.
	std::bitset<5> row[5];
	std::bitset<5> col[5];
	std::bitset<5> diag_lt2rb;	// left top to right bottom
	std::bitset<5> diag_rt2lb;	// right top to left bottom
3. 뽑는 공에 대해 다음을 수행한다.
	각 사람에 대해, 그 사람 빙고판에서 그 수가 어디 있는지 구한다.
	그 위치를 이용해 상태를 업데이트한다.
	업데이트 후 빙고가 되는지 체크한다. (std::bitset<>::all() 사용)
	(이미 빙고로 체크된 사람은 그냥 스킵해도 무방하다.)
*/

#include <iostream>
#include <bitset>
#include <sstream>

struct coord {
	coord() : x(0), y(0) {}
	char x, y;
};

class Bingo{
public:
	Bingo() : have_bingo(false) {
	}
	void bingoboard_get(int x, int y, int val) {
		board[val].x = x;
		board[val].y = y;
	}
	void bingo_play(int num) {
		// early return
		if (have_bingo) return;

		const coord& c = board[num];
		if (c.x == 0 && c.y == 0) return;
		// row
		row[c.y-1].set(c.x - 1);
		if (row[c.y-1].all()) {
			have_bingo = true;
			return;
		}
		// col
		col[c.x-1].set(c.y - 1);
		if (col[c.x-1].all()) {
			have_bingo = true;
			return;
		}
		// diag 1
		if (c.x == c.y) {
			diag_lt2rb.set(c.x-1);
			if (diag_lt2rb.all()) {
				have_bingo = true;
				return;
			}
		}
		// diag 2
		if (c.x + c.y == 6) {
			diag_rt2lb.set(c.x-1);
			if (diag_rt2lb.all()) {
				have_bingo = true;
				return;
			}
		} 
	}
	bool have_bingo;

private:
	coord board[91];
	/*
		col->	1	2	3	4	5 (x)
	row
		1		1,1
		2
		3			2,3
		4
		5					4,5 ...
		(y)
	*/
	std::bitset<5> row[5];
	std::bitset<5> col[5];
	std::bitset<5> diag_lt2rb;	// left top to right bottom
	std::bitset<5> diag_rt2lb;	// right top to left bottom
};

struct player {
	std::string name;
	Bingo bingo; 
};

int main() {
	player players[50];
	// player & board input
	int n;
	std::cin >> n;

	for (int i = 0; i < n; ++i) {
		std::cin >> players[i].name;
		for (int y = 1; y <= 5; ++y) {
			for (int x = 1; x <= 5; ++x) {
				int temp;
				std::cin >> temp;
				players[i].bingo.bingoboard_get(x, y, temp);
			}
		}
	}

	// gameplay
	int m;
	std::cin >> m;

	for (int i = 0; i < m; ++i) {
		int ball;
		std::cin >> ball;
		for (int j = 0; j < n; ++j) {
			players[j].bingo.bingo_play(ball);
		}
	}


	// result output

	std::stringstream outbuf;
	int count = 0;

	for (int i = 0; i < n; ++i) {
		if (players[i].bingo.have_bingo) {
			++count;
			outbuf << players[i].name << '\n';
		}
	}

	std::cout << count << '\n';
	std::cout << outbuf.str();

	return 0;
}
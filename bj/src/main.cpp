/*
bj14589 Line Friends (Large)

수직선 위에 N개의 선분이 있고, 서로 겹치는 선분은 "친한" 선분이다.

"친함" 관계로 그래프를 만들고, 각 선분 사이의 거리를 구하여라.

2 <= N <= 150'000
-1'000'000 <= L_i <= R_i <= 1'000'000

1 <= Q <= 150'000 

선분 정보 입력 후 임의의 두 점 사이의 최단거리를 묻는 쿼리가 여러번 입력되면
그에 알맞은 답을 출력하라.

접근

0. 계속된 쿼리에 대응하기 위해 어떤 식으로든 두 선분 사이의 거리를
	구해 놓아야 한다.
1. a -> b의 이동에서, 각 단계마다 가장 큰 끝점을 가진 선분으로 가는 것이
	최적이다.
2. 위 과정을 반복하면 거리를 구할 수 있지만, 이것을 모두 저장할 수는 없다.
3. sparse table을 이용한다.
	1. 임의의 선분 a에서, 2^i번(0<=i)의 이동으로 이동 가능한 최적의 선분을
		찾아 저장해 둔다.
	2. binary shifting을 이용해 a -> b의 최소 거리를 구한다.
4. sparse table의 구축을 위해, 첫 항은 알아야 한다.
	-> 이는 각 선분의 끝점보다 시작점이 작은 선분 중 끝점이 최대인 선분이다.  
 
*/

#include<iostream>
#include<vector>
#include<sstream>
#include<algorithm>


struct Line {
	int index, start, end;
};

class my_sstream : public std::basic_ostringstream<char>
{
public:
	~my_sstream() {
		std::cout << this->str();
	}
} log_out;


bool is_friend(const Line& a, const Line& b) {
	//a   -------
	//b           --------
	if (a.end < b.start
		// a               -------
		// b        -----
		|| b.end < a.start) return false;
	else
		return true;
} 

int main(void) {
	// c++ fast io
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(false);


	// input
	int n;
	std::cin >> n; 

	std::vector<Line> lines(n); 

	for (int i = 0; i < n; ++i) {
		lines[i].index = i + 1;
		std::cin >> lines[i].start;
		std::cin >> lines[i].end;
	}

	// 끝점으로 정렬
	std::sort(lines.begin(), lines.end(),
		[](const Line& a, const Line& b)->bool {
			if (a.start == b.start) {
				return a.end < b.end;
			}
			else {
				return a.start < b.start;
			}
		}); 



	// 쿼리
	int q;
	std::cin >> q;

	for (int i = 0; i < q; ++i) {
		int a, b;
		std::cin >> a >> b;
		
		a = index_transform[a];
		b = index_transform[b];

		if (a > b) {
			std::swap(a, b);
		}
 
		int distance = 1;

		while (true) {
			if (is_friend(lines[a], lines[b])) {
				log_out << distance << '\n';
				break;
			}
			else {
				auto it = std::upper_bound(
					lines.begin(), 
					lines.end(), 
					Line{ 0, lines[a].end, 0 },
					[](const Line& o1, const Line& o2)->bool {
						return o1.start < o2.start;
					}); 
				--it;
				int possible_next = std::distance(lines.begin(), it);

				Line next = optimal_next[possible_next];
				
				if (lines[a].index == next.index) {
					log_out << -1 << '\n';
					break;
				}
				a = index_transform[next.index];
				++distance;
			}
		} 
	} 
	return 0; 
}
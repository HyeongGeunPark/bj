/*
bj28377 Investigating Frog Behaviour on Lily Pads Patterns

번역은 다음과 같다.

1. 한 줄로 놓여진 연못의 패드에 개구리가 앉아 있다.
2. 개구리는 한 쪽 방향으로만 움직인다.
3. 개구리는 가장 가까운 비어있는 패드로 이동한다.
4. 각 개구리가 처음에 앉아 있는 패드의 위치가 주어진다.
5. 어떤 개구리가 움직였는지, 시간 순으로 주어진다.
6. 모든 움직임은 valid하다는 가정이 있다. 즉,
	1. 개구리가 움직일 때에는 반드시 조건에 맞는(오른쪽에 있는 비어있는) 패드가 존재한다.
	2. 개구리가 움직인 후에 반드시 그 패드로 이동한다.

입력
1. 개구리의 수 n (1<= n <= 2* 10^5)
2. i번 개구리가 처음에 앉아 있는 패드의 위치를 나타내는 n개의 정수 x_i (1 <= x_i <= 10^6)
	1. x_i는 strictly increasing하다. (x1 < x2 < ... < xn)
3. 개구리가 움직인 횟수 q (1 <= q <= 2* 10^5)
4. q줄의 정수 입력
	1. 각 줄에는 한 개의 정수가 주어진다.
	2. 이 정수는 몇 번째 개구리가 움직였는지를 나타낸다. (1 <= i <= n)

출력
1. 각 개구리가 움직일 때 마다, 어느 패드로 이동하였는지 출력한다.


1. 간단한 방법 (binary search on set)
	1. ordered_set을 만든다. 여기에는 빈 패드의 위치를 저장한다.
	2. 필요한 빈 패드의 위치를 저장한다.
		1. 대강의 범위 안에 있는 패드만 저장하면 된다.
		2. 정확히는, 
			1. 가장 왼쪽에 있는 개구리의 위치부터,
			2. 가장 오른쪽에 있는 개구리의 위치 + 1까지
			3. 빈 패드만 골라 저장.
	3. 개구리가 움직일 때마다,
		1. 현재 개구리의 위치보다 큰, 가장 작은 빈 패드를 set에서 찾는다.
		2. 그 패드로 이동한다.
			1. set에서 찾은 패드 제거
				1. 이 패드가 가장 오른쪽 패드라면	
					1. set에 가장 오른쪽 패드 + 1 추가
			2. set에 개구리의 현 위치 추가
			3. 개구리의 현 위치 업데이트
		3. 추가로 set에서 찾은 패드를 출력한다.

	worst: nlog(n) + qlog(n)

1-1. 꼭 std::set을 이용하지 않아도 된다.
	1. 빈 위치를 저장하는 배열을 만들어 사용해도 무방하다.
		
2. 다른 방법
	1. 개구리의 위치를 저장하는 배열을 만든다.
	2. 패드의 상태를 나타내는 긴 배열을 만든다.
		1. 이 배열의 인덱스는 패드의 위치를 나타낸다.
		2. 이 배열의 값은 가장 가까운 빈 패드의 위치를 나타낸다.
		3. 초기 개구리 위치를 이용해 이 배열을 초기화한다.
	3. 개구리가 움직일 때마다,
		1. 개구리의 위치를 배열에서 찾는다.
		2. 그 위치의 패드 상태 배열에서 가장 가까운 빈 패드의 위치를 찾는다.
		3. 그 패드로 이동한다.
			1. 패드 상태 배열에서 그 패드의 상태를 업데이트한다.
				1. 그 패드의 왼쪽에 있는 패드들 중, 기존에 그 패드를 가리키고 있었던 패드들을 모두
					그 패드가 가리키고 있던 패드를 가리키게 한다.  
			2. 기존 패드의 상태를 업데이트한다.
				1. 기존 패드의 왼쪽에 있던 패드 중 기존 패드보다 우측을 가리키고 있던 패드들을 모두
					그 패드를 가리키게 한다.  
			2. 개구리의 현 위치를 업데이트한다.
			3. 그 패드를 출력한다.
	worst: n*q?

*/

#include <iostream>
#include <vector> 
#include <algorithm>

int main(void) {

	// c++ fast io
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	// input 1
	int n;
	std::cin >> n;
	int* x = new int[n+1];
	for (int i = 1; i <= n; ++i) {
		std::cin >> x[i];
	}

	int q;
	std::cin >> q;

	// process
	std::vector<int> empty_pads;
	empty_pads.reserve(x[n] + q);

	for (int frog = 1; frog < n; ++frog) {
		for (int empty_pad = x[frog] + 1; empty_pad < x[frog + 1]; ++empty_pad) {
			empty_pads.push_back(empty_pad);
		} 
	}

	int rightmost_frog = x[n];

	for (int i = 0; i < q; ++i) {
		int jumped_frog;
		std::cin >> jumped_frog;

		auto next_pad = std::upper_bound(empty_pads.begin(), empty_pads.end(), x[jumped_frog]);

		if (next_pad == empty_pads.end()) {
			++rightmost_frog;
			empty_pads.push_back(x[jumped_frog]);
			x[jumped_frog] = rightmost_frog; 
		}
		else {
			std::swap(x[jumped_frog], *next_pad); 
		}


		//print
		std::cout << x[jumped_frog] << '\n';
	}

	/*
	std::set<int> empty_pads;

	// initialize empty pads;
	{
		int empty_pad = 1;
		int idx = 1;
		while (empty_pad < x[1]) ++empty_pad;

		while (empty_pad <= x[n] + 1) {
			if (empty_pad == x[idx]) {
				++idx;
				++empty_pad;
				continue;
			}
			empty_pads.insert(empty_pad);
			++empty_pad;
		} 
	}


	// get number of movements
	int q;
	std::cin >> q;

	// get movement and print appropriate output
	for (int i = 0; i < q; ++i) {
		int moved_frog;
		std::cin >> moved_frog;
		int current_pos = x[moved_frog];

		// find next position
		auto next_pos = empty_pads.upper_bound(current_pos);
		x[moved_frog] = *next_pos; // move frog to next position
		if (next_pos == --empty_pads.end()) {
			empty_pads.insert(*next_pos + 1);
		}
		auto next_pos_node = empty_pads.extract(next_pos);
		next_pos_node.value() = current_pos;
		empty_pads.insert(std::move(next_pos_node)); 
		// print
		std::cout << x[moved_frog] << "\n"; 
	}
	*/

	// deallocate manually allocate memory
	delete[] x;


	return 0;
}
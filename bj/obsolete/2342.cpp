/*

bj2342 DDR

���ٹ�(���̳��� ���α׷���)
1. ���� ���´� ���� ��ġ�� ���ǵȴ�.
2. ���������� �Է¹��� ������ ��ġ�� �� ���� �ö� �ִ� ���� ����ϴ�.
	���� �ٸ� �� ���� ��� �ִ����� ���� 5���� ���°� �����Ѵ�.
3. �� �Է��� ���� �� ���� (����, �ּҺ��)�� �̿��� �� (����, �ּҺ��)�� ����ϸ� �ȴ�.

*/

#include<iostream>
#include<vector>
#include<limits>
#include<cstring>

constexpr int MAX = 2'000'000;
unsigned int mem[2][5];

int cost(int current, int next) {
	static int c[5][5] = { 
		{MAX, 2, 2, 2, 2},
		{MAX, 1, 3, 4, 3},
		{MAX, 3, 1, 3, 4},
		{MAX, 4, 3, 1, 3},
		{MAX, 3, 4, 3, 1},
	};
	return c[current][next];
}

void mem_init(unsigned int(*arr)) {
	for (int i = 0; i < 5; ++i)
		arr[i] = MAX; 
}

int main() {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	for (int i = 0; i < 2; ++i)
		mem_init(mem[i]);

	unsigned int (*current) = mem[0];
	unsigned int (*next) = mem[1];

	int last_step;
	std::cin >> last_step;
	current[0] = 2; // ù ����� ������ �� �ٸ� �� ���� 0�� �ִ�.



	for (int cmd; std::cin >> cmd && cmd != 0; std::swap(current, next)) {
		
		mem_init(next); 

		for (int i = 0; i < 5; ++i)// ���������� ���� �� �ű��
			next[i] = std::min(next[i], current[i] + cost(last_step, cmd));
		for (int i = 0; i < 5; ++i)// �ٸ� �� �ű��
			next[last_step] = std::min(next[last_step], current[i] + cost(i, cmd));
		last_step = cmd;
	}

	// select smallest cost
	unsigned int result = MAX;
	for (int i = 0; i < 5; ++i) {
		result = std::min(result, current[i]);
	}

	std::cout << result; 
}
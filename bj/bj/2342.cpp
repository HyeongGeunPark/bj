/*

bj2342 DDR

접근법(다이나믹 프로그래밍)
1. 현재 상태는 발의 위치로 정의된다.
2. 마지막으로 입력받은 패턴의 위치에 한 발이 올라가 있는 것은 명백하다.
  따라서 다른 한 발이 어디 있는지에 따라 5가지 상태가 존재한다.
3. 새 입력이 들어올 때 이전 (상태, 최소비용)을 이용해 새 (상태, 최소비용)을
계산하면 된다.

*/

#include <cstring>
#include <iostream>
#include <limits>
#include <vector>

constexpr int MAX = 2'000'000;
unsigned int mem[2][5];

int cost(int current, int next) {
  static int c[5][5] = {
      {MAX, 2, 2, 2, 2}, {MAX, 1, 3, 4, 3}, {MAX, 3, 1, 3, 4},
      {MAX, 4, 3, 1, 3}, {MAX, 3, 4, 3, 1},
  };
  return c[current][next];
}

void mem_init(unsigned int(*arr)) {
  for (int i = 0; i < 5; ++i) arr[i] = MAX;
}

int main() {
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);

  for (int i = 0; i < 2; ++i) mem_init(mem[i]);

  unsigned int(*current) = mem[0];
  unsigned int(*next) = mem[1];

  int last_step;
  std::cin >> last_step;
  current[0] = 2;  // 첫 명령을 수행한 후 다른 한 발은 0에 있다.

  for (int cmd; std::cin >> cmd && cmd != 0; std::swap(current, next)) {
    mem_init(next);

    for (int i = 0; i < 5; ++i)  // 마지막으로 딛은 발 옮기기
      next[i] = std::min(next[i], current[i] + cost(last_step, cmd));
    for (int i = 0; i < 5; ++i)  // 다른 발 옮기기
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
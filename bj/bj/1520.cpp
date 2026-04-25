/*
bj1520 내리막길

M * N 크기의 지도가 주어진다.
지도에는 각 칸의 높이가 주어진다.
왼쪽 위 칸에서 시작해서 오른쪽 아래 칸으로 가려고 하는데,
항상 지금보다 낮은 높이의 칸으로만 이동한다.

가능한 경로의 갯수를 구하는 프로그램을 작성하시오.

M,N:[1,500]
H(i,j):각 칸의 높이:[1,10000]


모든 입력 케이스에 대해 가능한 경로의 수는 10억 이하의
음이 아닌 정수라는 것이 보장된다.

접근: DP

재귀적 방식이 더 편해 보인다.

(어떤 칸으로 갈 수 있는 길의 경우의 수)
  = (그 칸 주변에 있는 그 칸보다 높은 곳으로 갈 수 있는 길의 경우의 수)

*/

#include <iostream>
#include <vector>

int solve(std::vector<std::vector<int>>& mem, std::vector<std::vector<int>>& map, int i, int j) {
  // outside of map
  if (i < 0 || j < 0 || i >= map.size() || j >= map[0].size())
    return 0;
  // base case
  if (i == 0 && j == 0)
    return 1;
  // other cases
  if (mem[i][j] == -1) {
    mem[i][j] = 0;
    if(i-1 >= 0 && map[i-1][j] > map[i][j])
      mem[i][j] += solve(mem, map, i - 1, j);
    if(i+1 < map.size() && map[i+1][j] > map[i][j])
      mem[i][j] += solve(mem, map, i + 1, j);
    if(j-1 >= 0 && map[i][j-1] > map[i][j])
      mem[i][j] += solve(mem, map, i, j - 1);
    if(j+1 < map[0].size() && map[i][j+1] > map[i][j])
      mem[i][j] += solve(mem, map, i, j + 1);
  }
  return mem[i][j];
}

int main(void) {
  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);


  // input
  int m, n;
  std::cin >> m >> n;

  std::vector<std::vector<int>> map(m, std::vector<int>(n, 0));
  std::vector<std::vector<int>> mem(m, std::vector<int>(n, -1));

  for (int i = 0;i < m;i++) {
    for (int j = 0;j < n;j++) {
      std::cin >> map[i][j];
    }
  }

  // DP
  std::cout << solve(mem, map, m - 1, n - 1);

  return 0;
}
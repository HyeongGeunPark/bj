/*

bj2252 줄 세우기

접근법(위상 정렬- 스택, DFS)
1. 키 비교 데이터를 입력받는다. (각 학생별로 자신보다 키가 작은 학생이 누구인지
상수 시간에 알 수 있도록)
2. 학생들의 번호를 하나하나 출력한다.
  단 출력하기 전에 자신보다 키가 작은 학생을 먼저 출력한다.(재귀적 구현)

다른 접근법(위상 정렬- 큐, Kahn 알고리즘)
1. 키 비교 데이터를 인접 그래프로 저장한다.
2. 저장하면서 키가 큰 학생의 'degree'를 하나씩 올린다.
3. 결과적으로 degree는 자신보다 명시적으로 작은 학생의 수를 저장한다.
4. degree가 0인 학생을 우선 queue에 담는다.
5. 큐에서 한 학생을 꺼내 출력한다.
6. 이 학생보다 명시적으로 키가 큰 학생의 degree를 하나씩 줄인다.
7. 만일 degree가 0이 되었다면 그 학생을 queue에 담는다.
8. queue가 빌 때까지 5-7 반복.

*/

#include <iostream>
#include <vector>

std::vector<std::vector<int>> comparision;
std::vector<bool> printed;

void print(int n) {
  if (printed[n]) return;
  while (comparision[n].size()) {
    int s = comparision[n].back();
    print(s);
    comparision[n].pop_back();
  }
  std::cout << n << ' ';
  printed[n] = true;
}

int main() {
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);

  int n, m;
  std::cin >> n >> m;
  comparision.resize(n + 1);
  printed.resize(n + 1, false);

  for (int i = 0; i < m; ++i) {
    int smaller, taller;
    std::cin >> smaller >> taller;
    comparision[taller].push_back(smaller);
  }

  for (int i = 1; i <= n; ++i) {
    print(i);
  }
}
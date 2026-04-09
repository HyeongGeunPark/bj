/*
bj31714 지정좌석 배치하기 1

n행 m열 강의실이 있다.
강의실의 i행의 높이는 D*i이다.

각 학생의 (좌석 높이 + 키)가 앞 행의 같은 열의 있는 모든 학생의
(좌석 높이 + 키)보다 크게 학생들을 배치할 수 있는지 여부를 파악하라.

(학생은 자신이 앉고자 하는 행을 선택한다.)

가능하다면 YES, 불가능하다면 NO를 출력한다.

N, M: [1,1000] : 강의실의 행, 열
D: [1,100'000] : 각 행의 높이 차이
h_ij: [1,100'000] : 각 학생의 키

접근: 그리디
각 열은 서로 대칭적이다. 즉, 인접한 두 행만 서로 고려하면 된다.

인접한 두 행의 가장 작은 학생부터, 주어진 조건을 만족하는지 서로 비교해 보면 된다.
뒤쪽 행에서 i번째로 키가 큰 학생의 경우, 앞쪽 행에서 조건을 만족하는 학생이
최소한 i명이 되어야 원하는 배치가 가능함은 자명하다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main(void) {
  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);
  int n, m, d;

  std::cin >> n >> m >> d;

  bool result = true;

  std::vector<std::vector<int>> students(n, std::vector<int>(m));

  for (int i = 0;i < n;++i) {
    for (int j = 0;j < m;++j) {
      std::cin >> students[i][j];
    }
    std::sort(students[i].begin(), students[i].end());
  }

  for (int i = 0;i < n-1;++i) {
    for (int j = 0;j < m;++j) {
      if (students[i][j] >= students[i + 1][j] + d) {
        result = false;
        goto print;
      }
    }
  }

print:
  if (result) std::cout << "YES";
  else std::cout << "NO";


  return 0;

}
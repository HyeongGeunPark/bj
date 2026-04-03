/*
bj31248 3+1 하노이 탑


일반적인 하노이 탑에서, 오직 쌓는 것만 가능한 기둥이 하나 더 있는 버전이다.
쌓는 것만 가능한 기둥에 모든 원판은 옮기는 것이 목표이다.

N개 원판을 모두 옮기는 데 필요한 최소 이동 횟수를 구하고,
그러한 이동 방법을 아무거나 하나 출력하라.

이동 방법은 다음과 같은 형식으로 출력한다.
- 기둥 x의 제일 위의 원반을 기둥 y의 제일 위로 옮기는 것을 x y로 표기한다.

1 <= N <= 20

접근: 재귀

가장 아래 있는 원판 2개를 제외하면 정석 하노이 방식으로 움직여야 한다.
가장 아래 있는 원판 2개는 빈 기둥 하나를 이용하여 빠르게 목표 기둥으로 옮길 수 있다.



*/

#include <iostream>
#include <sstream>
#include <string>

std::ostringstream buf;

long long hanoi_3(int n, char source, char dest, char temp){
  long long total_movement = 0;
  if(n == 1){
    buf<<source<<' '<<dest<<'\n';
    return 1;
  }
  else{
    total_movement += hanoi_3(n-1, source, temp, dest);
    total_movement += hanoi_3(1, source, dest, temp);
    total_movement += hanoi_3(n-1, temp, dest, source);
    return total_movement;
  }
}

long long hanoi_3_plus_1(int n, char source, char dest, char temp1, char temp2){
  long long total_movement = 0;
  if(n == 1){
    buf<<source<<' '<<dest<<'\n';
    return 1;
  }
  else if(n==2){
    buf<<source<<' '<<temp1<<'\n';
    buf<<source<<' '<<dest<<'\n';
    buf<<temp1<<' '<<dest<<'\n';
    return 3;
  }
  else{
    total_movement += hanoi_3(n-2, source, temp1, temp2);
    total_movement += hanoi_3_plus_1(2, source, dest, temp2, temp1);
    total_movement += hanoi_3_plus_1(n-2, temp1, dest, source, temp2);
  }
  return total_movement;
}

int main(void){
  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);

  int n;
  std::cin >> n;

  std::cout << hanoi_3_plus_1(n, 'A', 'D', 'B', 'C') << '\n';
  std::cout << buf.str();

  return 0;
}

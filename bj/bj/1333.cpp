/*
bj1333 부재중 전화

앨범에는 노래가 n개, 모든 노래의 길이는 l초, 노래와 노래 사이에는 5초간의
조용한 구간이 있음
0초부터 전화벨이 울리며, D초에 한번씩 1초간 울린다.
0---1--------D---D+1----------...
벨           벨                 
앨범은 1번만 듣는다.
전화벨이 들리는 가장 빠른 시간을 구하라.

접근
[l, l+5) [2l+5, 2l+10) ...
[0, 1) [D, D+1) ...

서로 겹치는 수를 찾는다.
D의 배수 중 처음으로 l+5로 나눈 나머지가 l, l+1, l+2, l+3, l+4인 경우를 찾는다.
mD = k(l+5) + (l~l+4), 단 k<=n이어야 한다.
여기 없으면 mD = (n+1)(l+5) + (l~l+4)가 답이다.

*/

#include<iostream>

int main(void) {
  int n, l, d;
  std::cin >> n >> l >> d;

  int time = d;
  while (true) {
    int dd = time % (l + 5);
    if (l <= dd && dd <= l + 4) {
      std::cout << time;
      break;
    }
    if (time >= n * (l + 5)) {
      std::cout << time;
      break;
    }
    time += d;
  }


  return 0;
}
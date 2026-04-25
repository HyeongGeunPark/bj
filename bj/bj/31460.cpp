/*
bj31460 초콜릿과 11과 팰린드롬

11의 배수이면서 팰린드롬인 N자리의 음이 아닌 정수를 하나 찾기.
0을 제외한 수는 숫자 0으로 시작할 수 없다.

*팰린드롬: 거꾸로 뒤집어도 자기 자신과 동일한 문자열 또는 숫자.

입력
T:테스트 케이스의 수:[1,100]
N:자릿수:[1,10000]

출력
각 테스트 케이스에 대해 11의 배수이면서 팰린드롬인 N자리의 음이 아닌
정수를 한 줄에 출력한다.
답이 여러개면 아무거나 출력한다.
그러한 수가 없으면 -1을 출력한다.

접근
11의 배수이며 팰린드롬인 수는 존재한다.
1자리: 0
2자리: 11
3자리: 121
4자리: 1221
...
n자리: 11111...1110 + 11111...111 = 122222....2221
*/

#include <iostream>
#include <string>

int main(void) {
  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);

  int t;
  std::cin >> t;

  while (t--) {
    int n;
    std::cin >> n;
    if (n == 1) {
      std::cout << "0\n";
    }
    else {
      std::cout << 1;
      std::cout << std::string(n - 2, '2');
      std::cout << "1\n";
    }
  }

  return 0;
}
/*
bj15824 너 봄에는 캡사이신이 맛있단다

음식점의 모든 메뉴의 조합에 따른 "주헌고통지수"의 합을 구한다.
주헌고통지수란, 메뉴에 포함된 가장 매운 음식과 맵지 않은 음식의
스코빌 지수 차이를 말한다.

메뉴 개수 n <= 3000
답을 1'000'000'007로 나눈 나머지를 출력한다.

접근법: 계산?

1. 전체 메뉴의 매운 맛 정도를 정렬한다. -> a[0], ..., a[n-1]
2. 계산은 대강 다음과 같다.
a[n-1]을 제일 매운 메뉴로 가지는 메뉴 조합의 수 = 1 + 2 + 4 + ... + 2^(n-2)
a[n-2]을 제일 매운 메뉴로 가지는 메뉴 조합의 수 = 1 + 2 + 4 + ... + 2^(n-3)
a[1]을 제일 매운 메뉴로 가지는 메뉴 조합의 수 = 1
...
a[0]를 제일 덜 매운 메뉴로 가지는 메뉴 조합의 수 = 1 + 2 + 4 + ... + 2^(n-2)
a[1]를 제일 덜 매운 메뉴로 가지는 메뉴 조합의 수 = 1 + 2 + 4 + ... + 2^(n-3)
a[n-2]를 제일 덜 매운 메뉴로 가지는 메뉴 조합의 수 = 1

3. 따라서, 전체 "주헌고통지수"의 합은 다음과 같다.

s(0) = 0,
s(n) = 1 + 2 + ... + 2^(n-1) ( for n >= 1 )이라 하면,

( a[n-1]*s(n-1) + a[n-2]*s(n-2) + ... + a[1]*s(1) + a[0]*s(0) )
-( a[0]*s(n-1) + a[1]*s(n-2) + ... + a[n-2]*s(0) + a[n-1]*s(0) )

s(n)만 빠르게 계산하고 나머지를 계산하면 된다.
*/

#include <algorithm>
#include <iostream>
#include <vector>

constexpr int MOD = 1'000'000'007;

int main(void) {
  // does fast io matters?
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;
  std::vector<int> menu;
  // input
  menu.reserve(n);
  for (int i = 0; i < n; ++i) {
    int temp;
    std::cin >> temp;
    menu.push_back(temp);
  }

  // sort
  std::ranges::sort(menu);

  // sum of power series(2)
  std::vector<long long> sps;
  sps.reserve(n);
  {
    long long sum = 0;
    long long power = 1;
    for (int i = 0; i < n; ++i) {
      sps.push_back(sum);
      sum += power;
      sum %= MOD;
      power <<= 1;
      power %= MOD;
    }
  }

  // final calculation
  long long result = 0;
  for (int i = 0; i < n; ++i) {
    result += sps[i] * (menu[i] - menu[n - 1 - i]);
    result %= MOD;
  }

  std::cout << result;
}

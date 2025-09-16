/*
bj27527 배너 걸기

지도는 N개의 구간으로 나뉘어져 있음.
N개의 구간에는 물체가 하나씩 있음.
그 물체의 높이를 A_i라고 한다.

배너는 연속된 M개 구간에 걸쳐서 건다.
그 구간에서 ceil(9*M/10)개 이상의 A_i값이 하나의 값으로 같을 때,
배너를 걸 수 있다고 한다.

이 때, 도로에 배너를 걸 수 있는지 확인하는 프로그램을 작성하라.

입력
N, M (1<=M<=N<=2*10^5)
A_1, A_2, ..., A_N (1<=A_i<=10^6)

출력
YES 혹은 NO

접근: 순차 탐색(moving window?)

1. 일단 입력을 다 받는다.
2. 0번 구간에서 M-1번 구간까지 길이 M인 구간에 대해 A_i들의 값과 개수를 센다.
  (map 등 사용)
3. 이후에 가장 앞의 구간을 1개 제거하고 뒤에 1개 구간을 추가하면서 조건을
  만족하는지 평가한다.
4. 언제든지 조건을 만족하면 종료한다.
5. 그렇지 못하면, 배너를 걸지 못하는 것이다.
*/

#include <iostream>
#include <vector>
// #include <unordered_map>
#include <cmath>

int main(void) {
  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);

  // input and process
  int n, m;
  std::cin >> n >> m;

  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }

  // process
  // std::unordered_map<int, int> counts;
  std::vector<int> counts(1000001, 0);
  for (int i = 0; i < m; ++i) {
    /*
    if (counts.count(a[i]) == 0) {
      counts.emplace(a[i], 1);
    }
    else {
      counts[a[i]] += 1;
    }
    */
    counts[a[i]] += 1;

    // early return
    if (counts[a[i]] >= std::ceil(9 * m / 10.0l)) goto print_yes;
  }

  for (int i = m; i < n; ++i) {
    counts[a[i - m]] -= 1;

    /*
    if (counts.count(a[i]) == 0) {
      counts.emplace(a[i], 1);
    }
    else {
      counts[a[i]] += 1;
    }
    */

    counts[a[i]] += 1;

    // early return
    if (counts[a[i]] >= std::ceil(9 * m / 10.0l)) goto print_yes;
  }

  // result print
  std::cout << "NO";
  return 0;

print_yes:
  std::cout << "YES";
  return 0;
}
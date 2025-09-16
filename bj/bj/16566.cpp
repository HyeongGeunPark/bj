/*
bj16566 카드 게임

카드 게임의 규칙은 다음과 같다.
0. 1~N이 적힌 n장의 카드가 2벌 있다.
1. 철수와 민수는 이 중 M개의 숫자를 골라 서로 한 장씩 가진다.
2. 한 턴마다 철수와 민수는 카드 한 장을 내서, 더 큰 수의 카드를 낸 사람이
  승리한다.
3. 한 번 사용한 카드는 버린다.
4. K(<=M)번 반복하여 더 많이 승리한 사람이 최종 승리한다.

특수 규칙
1. 철수는 자신이 가지고 있지 않은 카드도 낼 수 있다.
2. 민수는 철수가 낼 카드를 알 수 있다. 그래서 철수가 낼 카드보다 큰 카드가
  있다면, 그 카드들 중 가장 작은 카드를 내기로 했다.

K번 동안 철수가 낼 카드가 입력으로 주어진다.
그렇다면 민수가 어떤 카드를 낼 지 출력하라.

1 <= M <= N <= 4'000'000
1 <= K <= min(M, 10'000)

접근법
1. 민수의 카드를 정렬한다.
2. 철수가 낼 카드를 입력받을 때마다, 그 수보다 큰 수를 찾는다 - log(M)
3. 그 수와 같거나 크면서 아직 사용하지 않은 카드를 찾는다.
4. 그 카드를 사용했다고 표시한다.
  4-1. bitset을 사용해도 좋고, disjoint set을 사용해도 좋다.
    비슷하다.
*/

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

std::vector<int> next_available;

int find_next(int idx) {
  if (next_available[idx] == idx) {
    return idx;
  } else {
    return next_available[idx] = find_next(next_available[idx]);
  }
}
void merge(int i1, int i2) {
  i1 = find_next(i1);
  i2 = find_next(i2);
  next_available[i1] = i2;
}

int main(void) {
  std::cin.tie(0);
  std::cout.tie(0);
  std::ios_base::sync_with_stdio(false);

  int n, m, k;
  std::cin >> n >> m >> k;
  std::vector<int> cards(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> cards[i];
  }
  std::ranges::sort(cards);

  next_available = std::vector<int>(m + 1);
  std::iota(next_available.begin(), next_available.end(), 0);

  for (int i = 0; i < k; ++i) {
    int c;
    std::cin >> c;
    auto iter = std::upper_bound(cards.begin(), cards.end(), c);
    int idx = iter - cards.begin();
    idx = find_next(idx);
    merge(idx, idx + 1);
    std::cout << cards[idx] << '\n';
  }
}
/*
bj9576 책 나눠주기

1-n의 번호가 부여된 책이 있다.
m명의 학생이 각각 a_i, b_i (1<= a_i <= b_i <= n)의 수를 제출하고,
남아있는 책 중 [a_i, b_i]의 번호를 가진 책 중 하나를 준다.
그런 책이 없다면 그 학생에게는 책을 주지 않는다.

책을 줄 수 있는 최대 학생 수를 구하라.

입력
1. 테스트 케이스의 수
2. 각 테스트 케이스의 첫 줄에 n과 m (1<=n<=1000, 1<=m<=1000)
3. 다음 줄부터 m개의 줄에 a_i, b_i

출력
각 테스트 케이스마다 책을 줄 수 있는 최대 학생 수를 한 줄에 하나씩 출력한다.

접근:
1. 이분매칭

2. 그리디:
  학생별로 가져갈 수 있는 책이 연속된 range로 주어지고,
  1000명, 1000권으로 입력의 갯수가 작으므로 별도의 최적화는 없어도 될 것이다.


*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

/*
int books[1001];
bool visited[1001];
std::pair<int, int> book_range[1001];

bool dfs(int idx) {
  if (visited[idx] == true) return false;
  visited[idx] = true;
  for (int i = book_range[idx].first; i <= book_range[idx].second; ++i) {
    if (books[i] == 0 || dfs(books[i])) {
      books[i] = idx;
      return true;
    } 
  } 
  return 0;
}
*/

int main(void) {

  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);

  // input
  int t;
  std::cin >> t;
  while (t--) {

    // input per test case
    int n, m;
    std::cin >> n >> m;

    std::vector<std::pair<int, int>> book_range(m);

    for (int i = 0; i < m; ++i) {
      std::cin >> book_range[i].first >> book_range[i].second;
    } 

    /*
    // bipartite matching ( dfs, O(VE) )
    int count = 0;
    std::memset(books, 0, sizeof(int)*(n+1));
    for (int i = 1; i <= m; ++i) {
      std::memset(visited, 0, sizeof(bool)*(i+1));
      if (dfs(i)) ++count; 
    } 
    */

    // greedy

    std::sort(book_range.begin(), book_range.end(),
              [](const auto& l, const auto& r) -> bool {
                if (l.second != r.second)
                  return l.second < r.second;
                else
                  return l.first < r.first;
              });

    int count = 0;
    std::vector<bool> used_book(n + 1, false); // naive approach
    for (auto& r : book_range) {
      for (int i = r.first; i <= r.second; ++i) {
        if (used_book[i] == false) {
          ++count;
          used_book[i] = true;
          break;
        } 
      }
    }

    std::cout << count << '\n';
  } 
  return 0;
}


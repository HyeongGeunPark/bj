/*
bj14926 not equal

n개의 숫자(a1, a2, ..., an)가 모두 다르다는 것을 표현하는 한 줄의 표기법을
생각해 보라. C(n, 2)개의 "!="가 필요할 것이다. 이 중 사전순으로 가장 앞에 오는
것을 출력하라.

입력
N : 홀수 자연수 (1<N<500)

출력
예시) 3 -> a1 a2 a3 a1

접근: 깊이 우선 탐색
1. a1부터 탐색한다.
2. a1을 제외한 수 중, 사전순으로 가장 빠른 수를 찾는다.
3. 그 수를 제외하고, 아직 그 수와 명백한 부등 관계가 표현되지 않은 수를
선택한다.
  1. 단, 아직 모든 부등 관계가 표현되지 않았는데 다음 수를 찾지 못하면 이전으로
되돌아감.
4. 반복.
5. 모든 부등 관계가 표현되었으면 종료.

* 명시적 스택 대신 콜 스택을 사용하여도 된다.

*/

#include <bitset>
#include <iostream>
#include <vector>

constexpr int MAX_SIZE = 500;
bool graph[MAX_SIZE][MAX_SIZE];

std::vector<int> result;
int n;

void dfs(int current) {
  for (int i = 0; i < n; ++i) {
    while (!graph[current][i]) {
      graph[current][i] = true;
      graph[i][current] = true;
      dfs(i);
    }
  }
  result.push_back(current);
}

int main(void) {
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);

  std::cin >> n;

  for (int i = 0; i < n; ++i) {
    graph[i][i] = true;
  }

  dfs(0);

  for (auto itr = result.rbegin(); itr != result.rend(); ++itr) {
    std::cout << 'a' << *itr + 1 << ' ';
  }

  /*
  std::vector<std::vector<bool>> unequality(n, std::vector<bool>(n, false));
  std::vector<int> result;

  for (int i = 0; i < n; ++i) {
    unequality[i][i] = true;
  }

  int total_length = (n * (n - 1)) / 2;

  result.push_back(0);
  int idx;
  int idx2 = 0;

  while (true) {
    idx = result.back();

    // find next candidate
    int i;
    for (i = idx2; i < n; ++i) {
      if (i != idx && unequality[idx][i] == false) {
        unequality[idx][i] = true;
        unequality[i][idx] = true;
        idx = i;
        result.push_back(idx);
        idx2 = 0;
        break;
      }
    }
    // no candidate
    if (i == n) {
      //
      if (result.size() == total_length) break;
      else {
        idx2 = idx + 1;
        result.pop_back();
      }
    }
  }

  for (auto i : result) {
    std::cout << 'a' << i + 1 << ' ';
  }
  std::cout << "a1";

  */

  return 0;
}
/*

bj2473 세 용액

용액의 농도: 절대값 1'000'000'000 이하
용액의 갯수: 3~5000개

합이 0에 제일 가까워지는 세 용액을 고르고 오름차순으로 나열하라.

접근법(투 포인터)
1. 용액을 정렬한다.
2. 한 용액을 고른다.
3. 투 포인터 알고리즘으로 나머지 두 용액을 찾는다.(bj2467 참고)
4. 같은 용액을 두 번 고르지 않도록 주의한다.

*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

struct answer {
  std::vector<long long> liquids;
  long long sum = std::numeric_limits<long long>::max();
};

int main(void) {
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);

  int n;
  std::vector<long long> arr;
  answer ans;
  std::cin >> n;
  arr.resize(n);
  ans.liquids.resize(3);
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }

  std::sort(arr.begin(), arr.end());

  // 우선 한 용액을 고른다.
  for (int i = 0; i < n - 1; ++i) {
    // 2 pointers
    // 고른 용액을 또 고르지 않도록 포인터의 시작 위치를 조절한다.
    for (int lp = i + 1, rp = n - 1; lp < rp;) {
      long long sum = arr[i] + arr[lp] + arr[rp];
      if (std::abs(ans.sum) > std::abs(sum)) {
        ans.liquids[0] = arr[i];
        ans.liquids[1] = arr[lp];
        ans.liquids[2] = arr[rp];
        ans.sum = sum;
      }

      if (sum > 0) {
        --rp;
      } else if (sum < 0) {
        ++lp;
      } else {
        goto Print;  // 합이 0인 경우를 찾으면 더 계산할 필요가 없다.
      }
    }
  }

Print:
  for (auto elem : ans.liquids) std::cout << elem << ' ';
}
/*
bj30467 등불 날리기

n개의 등불을 1초에 1개씩 순서대로 날리며,
나중에 날린 등불이 앞서 날린 등불을 추월하는 횟수를 센다.
연속한 S개의 등불을 날릴 때 그 횟수가 가장 많아지는 경우의
횟수를 구하라.

접근: 머지소트 트리
1. 머지소트 트리를 구성한다.
2. s개의 연속한 등불을 선택하는데, 좌측부터 생각한다.
3. 현재 선택된 등불 영역에서 가장 왼쪽의 등불을 뺀다.
4. 현재 영역에서 이 등불보다 속도가 빠른 등불의 수 만큼 결과에서 뺀다.
5. 현재 선택된 등불 영역에 오른쪽에 하나를 추가로 더한다.
6. 그 등불보다 느린 등불의 개수만큼 결과에 더한다.
7. 최대 횟수를 갱신한다.

시간복잡도: n * ( log(n) )^2
*/
#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

class mergeSortTree {
 public:
  mergeSortTree(std::vector<int>& arr) : sz{arr.size()}, node(arr.size() * 4) {
    init(0, sz, 0, arr);
  }

  int queryLesser(int s, int e, int val) {
    return queryLesser_internal(s, e, val, 0, 0, sz);
  }
  int queryGreater(int s, int e, int val) {
    return queryGreater_internal(s, e, val, 0, 0, sz);
  }

 private:
  std::vector<std::vector<int>> node;
  const size_t sz;

  void init(int s, int e, int index, std::vector<int>& arr) {
    if (e == s + 1) {
      // base case
      node[index].push_back(arr[s]);
    } else {
      int mid = s + (e - s) / 2;  // == (s+e)/2
      int leftIndex = index * 2 + 1;
      int rightIndex = index * 2 + 2;
      init(s, mid, leftIndex, arr);   // left subnode
      init(mid, e, rightIndex, arr);  // right subnode
      // merge
      node[index].resize(node[leftIndex].size() + node[rightIndex].size());
      std::ranges::merge(node[leftIndex], node[rightIndex],
                         node[index].begin());
    }
  }

  int queryLesser_internal(int s, int e, int val, int index, int l, int r) {
    if (r <= s || e <= l) {
      // query in empty array
      return default_value();
    }
    if (s <= l && r <= e) {
      // current node is in the query range
      return countLesser(val, index);
    }
    int mid = l + (r - l) / 2;
    int result = 0;
    result += queryLesser_internal(s, e, val, index * 2 + 1, l, mid);
    result += queryLesser_internal(s, e, val, index * 2 + 2, mid, r);
    return result;
  }
  int queryGreater_internal(int s, int e, int val, int index, int l, int r) {
    if (r <= s || e <= l) {
      // query in empty array
      return default_value();
    }
    if (s <= l && r <= e) {
      // current node is in the query range
      return countGreater(val, index);
    }
    int mid = l + (r - l) / 2;
    int result = 0;
    result += queryGreater_internal(s, e, val, index * 2 + 1, l, mid);
    result += queryGreater_internal(s, e, val, index * 2 + 2, mid, r);
    return result;
  }
  int default_value() { return 0; }
  int countLesser(int val, int index) {
    auto& arr = node[index];
    auto iter = std::ranges::lower_bound(arr, val);
    return std::distance(arr.begin(), iter);
  }
  int countGreater(int val, int index) {
    auto& arr = node[index];
    auto iter = std::ranges::upper_bound(arr, val);
    return std::distance(iter, arr.end());
  }
};

int main() {
  std::vector<int> speed;
  int n;
  int s;
  std::cin >> n >> s;
  for (int i = 0; i < n; ++i) {
    int temp;
    std::cin >> temp;
    speed.push_back(temp);
  }

  mergeSortTree mstree{speed};

  int l = 0;
  int r = 1;
  long long count = 0;
  long long result = std::numeric_limits<long long>::min();
  while (r < s) {
    count += mstree.queryLesser(l, r, speed[r]);
    ++r;
  }
  result = std::max(result, count);
  while (r < n) {
    count -= mstree.queryGreater(l + 1, r, speed[l]);
    ++l;
    count += mstree.queryLesser(l, r, speed[r]);
    ++r;
    result = std::max(result, count);
  }

  std::cout << result;

  return 0;
}
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

struct vec2 {
  int val, ind;
};

bool vec2_comp_ind(const vec2& a, const vec2& b) { return a.ind < b.ind; }
bool vec2_comp_val(const vec2& a, const vec2& b) { return a.val < b.val; }

int main(void) {
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);
  int n, k;
  std::cin >> n >> k;

  std::vector<vec2> arr;
  arr.reserve(n);

  for (int i = 0; i < n; ++i) {
    int p;
    std::cin >> p;
    arr.push_back(vec2{p, i});
  }

  std::sort(arr.begin(), arr.end(), vec2_comp_val);

  std::set<int> indices;
  int result = 1e9;
  for (int i = 0; i < n; ++i) {
    indices.insert(arr[i].ind);
    if (indices.size() == k) {
      result = std::min(*indices.rbegin() - *indices.begin(), result);
      indices.erase(arr[i - k + 1].ind);
    }
  }

  std::cout << result;
}
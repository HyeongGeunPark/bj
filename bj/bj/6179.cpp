/*

bj6179 River Crossing

John이 소(1<=N<=2500)를 데리고 강을 건넌다.

뗏목을 타고 건너는데 걸리는 시간이 주어진다.

혼자 건너갈 때 M(1<=M<=1000)분이 걸린다.
여기에 소를 i마리 더 태우면 M_i(1<=M_i<=1000)분이 더 걸린다.
참고로, i<j일때 M_i<M_j이다.

John이 소와 함께 강을 건너는 데 걸리는 최소 시간을 구하시오.

입력:
N M
M_1
M_2
...
M_N

접근: 동적 계획법.

T_0 = M
T_1 = M_1
...
T_N = min(
  M_N,
  T_(N-1) + T_0 + T_1,
  T_(N-2) + T_0 + T_2,
  ...
  T_(N-(N/2)) + T_0 + T_(N/2) <- integer division
)

-> O(N^2)
*/

#include <iostream>
// #include <memory>

int main(void) {
  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);

  int n;
  std::cin >> n;

  // std::unique_ptr<int[]> m_arr(new int[n+1]);
  int* m_arr = new int[n + 1];

  std::cin >> m_arr[0];

  for (int i = 0; i < n; ++i) {
    int temp;
    std::cin >> temp;
    m_arr[i + 1] = m_arr[i] + temp;
  }

  for (int i = 2; i <= n; ++i) {
    for (int j = 1; j <= i / 2; ++j) {
      m_arr[i] = std::min(m_arr[i], m_arr[i - j] + m_arr[0] + m_arr[j]);
    }
  }

  std::cout << m_arr[n];

  delete[] m_arr;
  return 0;
}
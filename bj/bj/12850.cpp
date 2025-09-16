/*

bj12850 본대 산책2

주어진 맵에서, 주어진 시작점을 출발하여 정확히 D번의 경로를 지난 후
다시 돌아오는 경로의 경우의 수를 구한다.

접근법: 인접행렬의 거듭제곱

그래프의 인접행렬을 A라고 하자. A는 unweighted graph이다.
A(i,j)는 꼭지점 i와 j를 연결하는 변의 개수이다.

꼭지점 i에서 꼭지점 j로 가는, 길이 d의 경로의 개수는
A^d(i, j)로 구할 수 있다.
*/

/*
그래프 정의

정보과학관	전산관	미래관	신양관	한경직기념관	진리관	학생회관
형남공학관 0			1		2		3 4
5		6			7
*/

#include <algorithm>
#include <iostream>
#include <vector>

template <int w, int h>
struct Mat {
  int value[w][h];
};

constexpr int MOD = 1'000'000'007;

template <int w, int m, int h>
Mat<w, h> mat_mul(const Mat<w, m>& m1, const Mat<m, h>& m2) {
  Mat<w, h> result;
  for (int i = 0; i < w; ++i) {
    for (int j = 0; j < h; ++j) {
      long long sum = 0;

      for (int k = 0; k < m; ++k) {
        sum += (long long)m1.value[i][k] * m2.value[k][j];
        sum %= MOD;
      }
      result.value[i][j] = static_cast<int>(sum);
    }
  }
  return result;
}

#define DEBUG 0

template <int n>
Mat<n, n> mat_pow(const Mat<n, n>& m, int pow) {
  Mat<n, n> result;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      result.value[i][j] = (i == j) ? 1 : 0;
    }
  }
  Mat<n, n> exp = m;

#if DEBUG
  int n = 0;
  int e = 1;
#endif

  while (pow) {
    if (pow & 1) {
      result = mat_mul(result, exp);
#if DEBUG
      n += e;
      std::cerr << "mat_mul, n==" << n << '\n';
      mat_print(result);
#endif
    }
    pow >>= 1;
    exp = mat_mul(exp, exp);
#if DEBUG
    e <<= 1;
#endif
  }
  return result;
}

#if DEBUG
template <int w, int h>
void mat_print(const Mat<w, h>& m) {
  for (int i = 0; i < w; ++i) {
    for (int j = 0; j < h; ++j) {
      std::cerr << m.value[i][j] << '\t';
    }
    std::cerr << '\n';
  }
}
#endif

constexpr Mat<8, 8> map = {.value = {
                               {0, 1, 1, 0, 0, 0, 0, 0},  // 정보과학관
                               {1, 0, 1, 1, 0, 0, 0, 0},  // 전산관
                               {1, 1, 0, 1, 1, 0, 0, 0},  // 미래관
                               {0, 1, 1, 0, 1, 1, 0, 0},  // 신양관
                               {0, 0, 1, 1, 0, 1, 0, 1},  // 한경직기념관
                               {0, 0, 0, 1, 1, 0, 1, 0},  // 진리관
                               {0, 0, 0, 0, 0, 1, 0, 1},  // 학생회관
                               {0, 0, 0, 0, 1, 0, 1, 0},  // 형남공학관
                           }};

int main(void) {
  int d;
  std::cin >> d;
  std::cout << mat_pow(map, d).value[0][0] << '\n';
}

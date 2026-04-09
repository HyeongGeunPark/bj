/*
bj15836 matrix multiplication calculator

행렬 곱셈을 하는 프로그램을 만드시오.
곱셈이 불가능하다면 "undefined"를 출력하시오. (m != p)

n, m: 앞 행렬 차원(n행 m열) : [1,20]
p, q: 뒤 행렬 차원(p행 q열) : [1,20]

n, m, p, q가 0이면 입력이 끝난다. (프로그램을 종료할 것)

케이스마다 "Case #x:"라는 줄을 출력하라 (x는 1부터 시작)
그 후 행렬곱셈의 결과를 출력한다 (n행 q열)

접근: 구현
그냥 구현만 하면 된다.

*/

#include <iostream>
//#include <vector>
#include <array>
#include <algorithm>

int main(void) {
  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);

  int x = 0;
  
  while (true) {
    ++x;
    int n, m, p, q;
    std::cin >> n >> m >> p >> q;
    // quit
    if (n * m * p * q == 0) {
      break;
    }
    std::cout << "Case #" << x << ":\n";
    // matrix input
    std::array<std::array<int, 20>, 20> a, b;
    std::array<std::array<int, 20>, 20> c{};

    for (int i = 0;i < n;++i) {
      for (int j = 0;j < m;++j) {
        std::cin >> a[i][j];
      }
    }
    for (int i = 0;i < p;++i) {
      for (int j = 0;j < q;++j) {
        std::cin >> b[j][i];
      }
    }

    // undefined
    if (m != p) {
      std::cout << "undefined\n";
      continue;
    }

    for (int i = 0;i < n;++i) {
      for (int j = 0;j < q;++j) {
        // requires c++20
        //c[i][j] = std::inner_product(a[i].begin(), a[i].end(), b[j].begin());
        for(int k=0;k<m;++k){
          c[i][j] += a[i][k] * b[j][k];
        }
      }
    }

    for (int i = 0;i < n;++i) {
      std::cout << "| ";
      for (int j = 0;j < q;++j) {
        std::cout << c[i][j] << ' ';
      }
      std::cout << "|\n";
    }
  }

  return 0;
}




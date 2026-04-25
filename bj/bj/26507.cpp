/*
bj26507 Rhonda

i개의 10*10 그리드가 주어진다.
n개의 수열이 주어진다.
수열의 각 원소는 그리드의 번호를 나타내며,
주어진 번호의 그리드를 element-wise하게 더한 그리드를 수열마다
출력하면 된다.

접근: 구현

그대로 만들면 된다.
사용하는 언어의 입출력을 다루는 방법을 숙지할 것.

*/

#include<iostream>
#include<vector>
#include<array>
#include<limits>
#include<string>
#include<sstream>
#include<iomanip>




int main(void) {
  using mat10_10 = std::array<std::array<int, 10>, 10>;
  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);

  int ii;
  std::cin >> ii;
  std::vector<mat10_10> layers(ii);

  //std::cin >> std::ws;
  for (int k = 0; k < ii; ++k) {
    std::cin.ignore(std::numeric_limits < std::streamsize>::max(), '\n');
    for (int i = 0;i < 10;++i) {
      for (int j = 0;j < 10;++j) {
        char c;
        std::cin.get(c);
        layers[k][i][j] = c - '0'; // char to int
      }
      std::cin.ignore(std::numeric_limits < std::streamsize>::max(), '\n');
    }
  }

  int n;
  std::cin >> n;
  std::cin.ignore(std::numeric_limits < std::streamsize>::max(), '\n');

  for (int i = 0;i < n;++i) {
    std::string line;
    std::getline(std::cin, line);

    std::vector<int> occurence(ii, 0);
    std::istringstream iss(line);
    for (int num; iss >> num;) {
      ++occurence[num];
    }

    mat10_10 result = {0,};
    for (int j = 0;j < ii;++j) {
      for (int k = 0;k < 10;++k) {
        for (int l = 0;l < 10;++l) {
          result[k][l] += layers[j][k][l] * occurence[j];
        }
      }
    }


    for (int k = 0;k < 10;++k) {
      for (int l = 0;l < 10;++l) {
        std::cout << std::setw(2) << std::setfill('0') << result[k][l];
        std::cout << ' ';
      }
      std::cout << '\n';
    }
    std::cout << '\n';
  }


  return 0;


}
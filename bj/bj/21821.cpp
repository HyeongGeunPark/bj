/*
bj21821 Acowdemia II

K개의 publication이 주어진다.
publication마다 저자의 목록이 주어지는데, 이는 노력 - 이름(알파벳) 순으로
정렬된다. publication을 작성할 때, 더 경력이 긴 사람은 경력이 짧은 사람보다 더
많은 노력을 들이지 않는다.

입력
K: publication의 수 ( 1<= K <= 100 )
N: 사람의 수 ( 1 <= N <= 100 )
각 사람의 이름. (<= 10 chars)
각 publication의 저자 목록 (space-separated)

출력
N * N
i번째 줄에, j!=i에서, j번째 문자는 다음과 같다.
1 : i번째 사람이 j번째 사람보다 명백하게 경력이 길다.
0 : i번째 사람이 j번째 사람보다 명백하게 경력이 짧다.
? : 주어진 정보로 알 수 없다.
i == j인 경우 B를 출력한다.

접근
1. 각 publication의 저자 목록에서, 알파벳 역순으로 나오는 첫 번째 사람은 앞서
   나온 사람들보다 명백하게 경력이 길다.
   1-1. 그 뒤에 나온 사람들도 마찬가지다.

*/

#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

int main(void) {
  int k, n;
  std::cin >> k >> n;

  std::unordered_map<std::string, int> name_to_index;

  for (int i = 0; i < n; ++i) {
    std::string name;
    std::cin >> name;
    name_to_index.insert({name, i});
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::vector<std::vector<char>> result(n, std::vector<char>(n, '?'));

  for (int i = 0; i < k; ++i) {
    std::string temp;
    std::string temp2;
    std::vector<std::string> authors;

    std::getline(std::cin, temp);
    std::stringstream ss(temp);
    while (ss >> temp2) {
      authors.push_back(temp2);
    }

    //

    for (int j = 1; j < authors.size(); ++j) {
      if (authors[j - 1] > authors[j]) {
        for (int l = 0; l < j; ++l) {
          for (int m = j; m < authors.size(); ++m) {
            int& index_l = name_to_index[authors[l]];
            int& index_m = name_to_index[authors[m]];
            // m is senior than l
            result[index_l][index_m] = '0';
            result[index_m][index_l] = '1';
          }
        }
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    result[i][i] = 'B';
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cout << result[i][j];
    }
    std::cout << '\n';
  }

  return 0;
}

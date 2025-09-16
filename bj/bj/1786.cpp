/*
bj1786 찾기

O(n) 시간복잡도의 문자열 검색 기능을 구현해 보아라.

입력 문자열 길이 <= 1'000'000
알파벳 대소문자와 공백으로만 이루어져 있다.

출력
첫 번째 줄: 매칭 횟수
두 번째 줄: 매칭 위치를 공백으로 구분하여 출력


접근법: KMP 알고리즘
문제에서 설명해 주는 알고리즘은 KMP 알고리즘이다.
설명해 주는 그대로 구현하면 되니 잘 읽고 구현해 보자.

1. 찾을 문자열의 상태천이함수를 먼저 계산한다. (전처리)
2. 이를 이용해 검색을 시작한다.

주의.
1. 출력에 1-based index를 사용하는 것에 주의.
2. 라인 단위 입력을 받아야 함에 주의.

*/

#include <iostream>
#include <string>
#include <vector>

namespace MyLib {

void kmp(const std::string& doc, const std::string& key,
         std::vector<int>& result) {
  // prerequisite
  if (doc.size() < key.size()) {
    return;
  }
  if (key.size() == 0) {
    return;
  }

  // preprocess
  std::vector<int> preprocess(key.size() + 1, 0);
  // example
  // key
  //		a	b	c	d	a	b	d
  // preprocess
  // 	-1	0	0	0	0	1	2	0	-> size
  // = key.size()+1
  {
    int i = -1;
    int j = 0;
    preprocess[0] = -1;
    while (j != key.size()) {
      if (i == -1 || key[i] == key[j]) {
        ++i;
        ++j;
        preprocess[j] = i;
      } else {
        i = preprocess[i];
      }
    }
  }

  // find
  {
    int i = 0;  // cursor for document
    int j = 0;  // cursor for key
    while (i != doc.size()) {
      if (j == -1 || doc[i] == key[j]) {
        // searching
        ++i;
        ++j;
      } else {
        // match fail
        j = preprocess[j];
      }

      if (j == key.size()) {
        // matched
        result.push_back(i - key.size());
        j = preprocess[j];
      }
    }
  }
}

}  // namespace MyLib

int main() {
  std::cin.tie(0);
  std::cout.tie(0);
  std::ios_base::sync_with_stdio(0);

  std::string key;
  std::string doc;
  std::vector<int> out;

  std::getline(std::cin, doc);
  std::getline(std::cin, key);

  MyLib::kmp(doc, key, out);

  // output
  std::cout << out.size() << '\n';
  if (out.size() == 0) return 0;

  for (auto i : out) {
    // 0-based index to 1-based index
    std::cout << i + 1 << ' ';
  }
  std::cout << '\n';

  return 0;
}
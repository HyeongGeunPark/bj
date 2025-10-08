/*
bj 6998 Tree Isomorphism

두 트리가 동형인지 파악하는 문제.

입력

테스트 케이스의 갯수가 주어진다. (n < 100)

테스트 케이스당 두 트리가 pre-order로 입력된다.
모든 child의 순회 이후 #이 추가로 입력된다 (모호성 해소).
모든 node label과 #은 space-delimited이다.

출력
테스트 케이스당 다음 두 문장 중 하나를 출력한다.

The two trees are not isomorphic.
혹은
The two trees are isomorphic.

접근

1. 트리를 그 형태(위상?)에 따라 유일하게 어떠한 linear한 representation으로 변환하는 방법을 생각한다.
  1. "유일함"을 위해 이 representation은 비교 가능해야 한다.
  2. 다음과 같은 방법을 사용할 수 있을 것이다:
    1. 노드 하나를 []로 표현한다.
      1. [과 ]은 서로 구분 가능한 어떠한 것이든 상관 없을 것이다.
      2. on-bit (1)과 off-bit (0), character '1'과 '0', character '['과 ']' 등등...
    2. subtree가 있는 노드는 [과 ] 사이에 모든 subtree를 동일한 representation으로
      표현하여 나열한다.
      1. 예시
                    1
                   / \
                  2   3
                 / \
                4   5
          -> [[][[][]]], 혹은, 1101101000
    3. 유일함을 위해, 모든 subtree는 모종의 방법으로 순서를 비교하여 정렬되어야 한다.
      1. naive하게 graphic character를 사용하고 string comparision을 사용해도 좋을 것이다.
        1. strcmp, std::string::operator< 등
        2. 직접 구현도 크게 어렵지 않을 것이다.
        3. 정렬만 가능하다면 어떠한 방법을 써도 좋을 것이다.
      2. 만일 노드의 갯수가 알려진 길이로 한정되어 있다면 0-bit와 1-bit를 사용하고
       전체 트리를 1개의 integer로 나타내어 <를 사용하는 것도 쉽게 구현 가능해 보인다.
        1. 노드 갯수 * 2의 길이가 필요하다.
  3. 입력이 preorder이고 child의 끝이 표시되므로 입력과 동시에
    이 representation으로 변환하는 것이 가능하다.

2. 그 representation에서 두 트리를 비교한다.
  1. 동일하면 동형이다.


주의
c++을 사용한다면 line-based input을 하는 방법을 고려하라.
아니면, 노드 이름과 같은 갯수의 #이 나올 수 밖에 없다는 사실을 이용하라.  
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string parse_tree(void) {

  std::string result;
  std::vector<std::string> subtrees;

  std::string temp;
  std::cin >> temp;

  if (temp != "#") {
    // temp is a valid node label
    // read subtrees from std::cin 
    for (temp = parse_tree(); !temp.empty(); temp = parse_tree()) {
      subtrees.push_back(temp);
    }

    // "ordered" is important. "how" is not important.
    std::sort(subtrees.begin(), subtrees.end()); 

    // construct the final representation
    result.push_back('[');
    for (std::string& subtree : subtrees) {
      result.append(subtree);
    }
    result.push_back(']');

    // and return that
    return result;

  } else {
    // it was the end of child list
    // return empty string 
    return result;
  } 
}

int main() {
  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);

  int n;
  std::cin >> n;
  while (n--) {
    std::string a = parse_tree();
    std::string b = parse_tree();

    if (a == b) {
      std::cout << "The two trees are isomorphic.\n";
    } else {
      std::cout << "The two trees are not isomorphic.\n";
    } 
  } 

  return 0;
}

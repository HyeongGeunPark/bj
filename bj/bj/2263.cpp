/*

bj2263 트리의 순회

이진 트리의 인오더와 포스트오더가 주어졌을 때 프리오더를 구하는 프로그램을
작성하라.

인오더: left subtree - root - right subtree
포스트오더: left subtree - right subtree - root
프리오더: root - left subtree - right subtree

*/

#include <iostream>
#include <vector>
constexpr int N = 100'000;

std::vector<int> in;
std::vector<int> post;
std::vector<int> pos;

void process(int in_s, int in_e, int post_s, int post_e) {
  int root = post[post_e - 1];
  int mid = pos[root - 1];
  std::cout << root << ' ';
  if (mid != in_s) process(in_s, mid, post_s, post_s + (mid - in_s));
  if (mid + 1 != in_e)
    process(mid + 1, in_e, post_e - (in_e - mid), post_e - 1);
}

int main(void) {
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);

  int n;
  std::cin >> n;

  in.resize(n);
  post.resize(n);
  pos.resize(n);

  for (int i = 0; i < n; ++i) {
    std::cin >> in[i];
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> post[i];
  }
  for (int i = 0; i < n; ++i) {
    // radix sort
    pos[in[i] - 1] = i;
  }

  process(0, n, 0, n);
}
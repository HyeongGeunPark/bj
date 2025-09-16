#include <iostream>
#include <vector>

struct node {
  char value;
  int underings;
  int depth;
  std::vector<node*> childs;
  node* parent;

  node() : value(0), underings(0), depth(0)
};

node root;
std::vector<node*> strings;

void input_process() {
  std::string s;
  std::cin >> s;
  node* cur = &root;

  for (char c : s) {
  }
}

int main(void) {
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);

  root.value = 0;
  root.underings = 0;
  root.depth = 0;

  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    input_process();
  }
}

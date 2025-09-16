#pragma GCC optimize("O3")

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int nodes[10001];

int postorder(int start_ind, int upperbound) {
  int root = nodes[start_ind];
  if (upperbound < root) {
    return start_ind;
  }

  int ind_right = postorder(start_ind + 1, root);
  int ind_end = postorder(ind_right, upperbound);

  printf("%d\n", root);

  return ind_end;
}

int main(void) {
  int len = 0;

  /*    read_f();*/
  struct stat stat;
  fstat(STDIN_FILENO, &stat);
  size_t file_size = stat.st_size;
  char* RBUF = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, STDIN_FILENO, 0);

  int n = 0;
  int index = 0;
  int num_valid = 0;
  for (int i = 0; i < file_size; i++) {
    char c = RBUF[i];
    int is_num = '0' <= c && c <= '9';
    if (is_num) {
      n = 10 * n + c - '0';
      num_valid = 1;
      continue;
    }
    if (num_valid) {
      nodes[index++] = n;
      n = 0;
      num_valid = 0;
    }
  }
  len = index;
  nodes[len] = INT_MAX;

  postorder(0, 10000000);
  return 0;
}
#pragma GCC optimize("O3")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char wbuf[20000000];
char* wp;

void star(int x, int y, int n, int len) {
  int i;
  if (n == 3) {
    char* p = wbuf + x * len + y;
    *p = '*';
    p += len;
    *(p - 1) = '*';
    *(p + 1) = '*';
    p = p + len - 2;
    memset(p, '*', 5);
    return;
  }
  n >>= 1;
  star(x, y, n, len);
  star(x + n, y - n, n, len);
  star(x + n, y + n, n, len);
}

int main(void) {
  int n;
  int len;
  int total_len;
  int i;
  scanf("%d", &n);
  len = n << 1;
  total_len = n * len;
  memset(wbuf, ' ', total_len);
  char* p = wbuf - 1;
  i = n;
  while (i--) {
    p += len;
    *p = '\n';
  }

  star(0, n - 1, n, len);

  write(STDOUT_FILENO, wbuf, total_len);

  return 0;
}
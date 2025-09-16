/*#pragma GCC optimize("O3")*/

#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

char* RBUF;
char* rp;
#define WBUF_SIZE 1 << 2
char WBUF[WBUF_SIZE];
char* wp = WBUF;

static inline size_t mymmap() {
  struct stat stat;
  fstat(STDIN_FILENO, &stat);
  RBUF = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, STDIN_FILENO, 0);
  rp = RBUF;
  return stat.st_size;
}

static inline int is_num(char* c) { return (*c >= '0' && *c <= '9'); }

static inline void write_f(void) { write(STDOUT_FILENO, WBUF, wp - WBUF); }

static inline int readd(int* n) {
  int r = 0;
  int sign = 1;
  while (1) {
    if (is_num(rp)) {
      break;
    } else if (*rp == '-') {
      sign = 0;
      rp++;
      break;
    }
    rp++;
  }
  while (1) {
    r *= 10;
    r += ((*rp++) - '0');
    if (!is_num(rp)) {
      break;
    }
  }
  *n = sign ? r : -r;
}

int main(void) {
  int n;
  int i, j;
  int a[200001];
  int b[200001];
  char used[200001] = {0};
  int current;
  mymmap();

  readd(&n);

  b[0] = 1;
  for (i = 1; i <= n; i++) {
    readd(b + i);
    if (b[i] - 1 > i) {
      goto no;
    }
    if (b[i] > (n + 1)) {
      goto no;
    }
    if (b[i] > b[i - 1]) {
      used[b[i - 1]] = 1;
      a[i] = b[i - 1];
    } else if (b[i] < b[i - 1]) {
      goto no;
    }
  }
  if (b[n] != n + 1) {
    goto no;
  }

  current = 1;
  for (i = 1; i <= n; i++) {
    while (used[current]) {
      current++;
    }
    if (a[i] == 0) {
      a[i] = current++;
    } else {
      if (current < b[i]) {
        goto no;
      }
    }
  }

  printf("Yes\n");
  for (i = 1; i <= n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
  return 0;

no:
  printf("No\n");
  return 0;
}
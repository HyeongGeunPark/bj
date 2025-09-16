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
#define max(a, b) ((a) > (b) ? (a) : (b))

int main(void) {
  int n;
  int i;

  int r[200001];
  int memo[200001] = {0};
  mymmap();

  readd(&n);
  for (i = 1; i <= n; i++) {
    readd(r + i);
  }

  memo[1] = 1;
  for (i = 1; i < n; i++) {
    if (memo[i] != 0 && (i + r[i]) <= n) {
      memo[i + r[i]] = max(memo[i + r[i]], memo[i] + 1);
    }
  }

  for (i = n - 1; i > 1; i--) {
    if (memo[i] != 0 && (i - r[i] > 0)) {
      memo[i - r[i]] = max(memo[i - r[i]], memo[i] + 1);
    }
  }

  for (i = 1; i < n; i++) {
    if (memo[i] != 0 && (i + r[i]) <= n) {
      memo[i + r[i]] = max(memo[i + r[i]], memo[i] + 1);
    }
  }

  printf("%d\n", memo[n] - 1);

  return 0;
}
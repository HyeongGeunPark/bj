#pragma GCC optimize("O3")

#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

char* RBUF;
char* rp;
#define WBUF_SIZE 1 << 17
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

static inline void writed(int n, char end) {
  char buf[20];
  int sign = 1;
  int i = 0;
  if (n < 0) {
    sign = 0;
    n = -n;
  }
  while (1) {
    buf[i++] = n % 10 + '0';
    n /= 10;
    if (n == 0) {
      break;
    }
  }
  if (sign == 0) {
    buf[i++] = '-';
  }
  while (i > 0) {
    *(wp++) = buf[--i];
  }
  *wp++ = end;
}

#define max(a, b) ((a) > (b) ? (a) : (b))

int main(void) {
  int n, m;
  int i, j, k;
  int a, b, c;
  int newlen;
  int map[101][101] = {0};
  mymmap();
  readd(&n);
  readd(&m);
  for (i = 0; i < m; i++) {
    readd(&a);
    readd(&b);
    readd(&c);

    if (map[a][b] == 0 || map[a][b] > c) {
      map[a][b] = c;
    }
  }

  // floyd-warshall
  for (k = 1; k <= n; k++) {
    for (i = 1; i <= n; i++) {
      for (j = 1; j <= n; j++) {
        if (i == j) continue;
        if (map[i][k] == 0 || map[k][j] == 0) continue;
        newlen = map[i][k] + map[k][j];
        if (map[i][j] == 0 || map[i][j] > newlen) {
          map[i][j] = newlen;
        }
      }
    }
  }

  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      writed(map[i][j], ' ');
    }
    *(wp - 1) = '\n';
  }
  write_f();

  return 0;
}
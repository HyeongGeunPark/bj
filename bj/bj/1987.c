#pragma GCC optimize("O3")

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/******************************************************************/

// simple buffered read / write

#include <sys/mman.h>
#include <sys/stat.h>

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

#define IGNORE_SPACE 1

static inline char readc(int mode) {
  if (mode == IGNORE_SPACE) {
    while (*rp < 33) {
      rp++;
    }
  }
  return *rp++;
}

static inline void reads(char* c) {
  while (1) {
    if (*rp > 32) {
      break;
    }
    rp++;
  }
  while (1) {
    *(c++) = *(rp++);
    if (*rp == '\n' || *rp == 0) {
      break;
    }
  }
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

static inline void writes(char* c, char end) {
  while (*c) {
    *wp++ = *c++;
  }
  *wp++ = end;
}

/******************************************************************/
#define max(a, b) ((a) > (b) ? (a) : (b))
int r, c;
char map[20][20];
int visited[20][20] = {0};
int max_len;
int mov_x[4] = {1, 0, -1, 0};
int mov_y[4] = {0, -1, 0, 1};

void dfs(int x, int y, int depth, int used) {
  int xx, yy;
  if (visited[x][y] == used) {
    return;
  }
  if (max_len < depth) {
    max_len = depth;
  }
  visited[x][y] = used;
  for (int i = 0; i < 4; i++) {
    xx = x + mov_x[i];
    yy = y + mov_y[i];
    if (xx < 0 || yy < 0 || xx >= r || yy >= c ||
        used & (1 << (map[xx][yy] - 'A'))) {
      continue;
    }
    dfs(xx, yy, depth + 1, used | (1 << (map[xx][yy] - 'A')));
  }
}

int main(void) {
  mymmap();
  readd(&r);
  readd(&c);

  for (int i = 0; i < r; i++) {
    reads(map[i]);
  }

  dfs(0, 0, 1, 1 << (map[0][0] - 'A'));
  printf("%d\n", max_len);

  return 0;
}
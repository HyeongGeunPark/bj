#pragma GCC optimize("O3")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

char* RBUF;
char* rp;

static inline size_t mymmap() {
  struct stat stat;
  fstat(STDIN_FILENO, &stat);
  RBUF = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, STDIN_FILENO, 0);
  rp = RBUF;
  return stat.st_size;
}

static inline int is_num(char* p) { return (*p >= '0' && *p <= '9'); }

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

#define min(a, b) ((a) > (b) ? (b) : (a))
#define abs(a) ((a) < 0 ? -(a) : (a))

int main(void) {
  size_t filesize = mymmap();
  int n, m;
  int i, j;
  int temp;
  int hl = 0;
  int cl = 0;
  int h[100][2];
  int c[13][2];
  int len[13][100] = {0};
  int clen[13][100] = {0};
  int minlen = 1 << 20;
  int v[13][13] = {0};

  readd(&n);
  readd(&m);

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      readd(&temp);
      if (temp == 1) {
        h[hl][0] = i;
        h[hl][1] = j;
        hl++;
      } else if (temp == 2) {
        c[cl][0] = i;
        c[cl][1] = j;
        cl++;
      }
    }
  }

  // find smallest chicken combination with m elements
  int d = 0;
  int cur = -1;
  int path[13];
  while (d > -1) {
    // if depth is reached, update min length and backtrack
    if (d == m) {
      d--;
      int t = 0;
      for (i = 0; i < hl; i++) {
        t += clen[d][i];
      }
      minlen = min(minlen, t);
      continue;
    }

    // select unvisited chicken in this depth
    for (i = (d == 0 ? 0 : path[d - 1] + 1); i < cl; i++) {
      if (v[d][i] == 0) {
        cur = i;
        v[d][i] = 1;
        path[d] = cur;
        break;
      }
    }
    // cannot select next depth -> backtrack
    if (i == cl) {
      for (i = 0; i < cl; i++) {
        v[d][i] = 0;
      }
      d--;
      continue;
    }
    // calculate chicken length
    if (len[cur][0] == 0) {
      for (i = 0; i < hl; i++) {
        len[cur][i] = abs(c[cur][0] - h[i][0]) + abs(c[cur][1] - h[i][1]);
      }
    }
    if (d == 0) {
      for (i = 0; i < hl; i++) {
        clen[d][i] = len[cur][i];
      }
    } else {
      for (i = 0; i < hl; i++) {
        clen[d][i] = min(clen[d - 1][i], len[cur][i]);
      }
    }
    // call next depth
    d++;
  }

  // print minlen
  printf("%d\n", minlen);
  return 0;
}
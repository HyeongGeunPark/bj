#pragma GCC optimize("O3")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/******************************************************************/

// simple buffered read / write

#define BUF_SIZE 1000000
char RBUF[BUF_SIZE];
char WBUF[BUF_SIZE];
char* rp = RBUF;
char* wp = WBUF;

static inline int is_num(char* c) { return (*c >= '0' && *c <= '9'); }

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

static inline void writes(char* c, char end) {
  while (*c != 0) {
    *(wp++) = *(c++);
  }
  *(wp++) = end;
}

static inline void writec(char c) { *(wp++) = c; }

/******************************************************************/

int main(void) {
  int n, m;
  int i, j;
  int d;
  int path[9] = {0};
  int tried[9][9] = {
      0,
  };

  read(STDIN_FILENO, RBUF, BUF_SIZE);
  readd(&n);
  readd(&m);

  d = 1;

  while (d) {
    // find untried valid node
    for (i = path[d - 1] + 1; i <= (n - m + d); i++) {
      if (tried[d][i] == 0) {
        tried[d][i] = 1;
        path[d] = i;
        break;
      }
    }
    // if there is no valid node untried
    if (i == (n - m + d + 1)) {
      // backtrack
      for (j = 1; j <= n; j++) {
        tried[d][j] = 0;
      }
      d--;
      continue;
    }
    // solution found, print
    if (d == m) {
      for (j = 1; j <= m; j++) {
        writec('0' + path[j]);
        writec(' ');
      }
      writec('\n');
    } else {
      // still solving
      d++;
    }
  }

  write(STDOUT_FILENO, WBUF, wp - WBUF);
  return 0;
}

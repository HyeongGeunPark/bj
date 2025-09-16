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

static inline void readd(int* n) {
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
  int n;
  int i, j, k;
  int temp;
  int min = 10000000;
  int cost[1000][3];
  int memo[1000][3] = {0};
  read(STDIN_FILENO, RBUF, BUF_SIZE);
  readd(&n);
  for (i = 0; i < n; i++) {
    for (j = 0; j < 3; j++) {
      readd(&cost[i][j]);
    }
  }

  // dp
  for (i = 0; i < 3; i++) {
    memo[0][i] = cost[0][i];
  }
  for (i = 1; i < n; i++) {
    for (j = 0; j < 3; j++) {
      for (k = 0; k < 3; k++) {
        if (j == k) {
          continue;
        }
        temp = memo[i - 1][k] + cost[i][j];
        if (memo[i][j] == 0 || memo[i][j] > temp) {
          memo[i][j] = temp;
        }
      }
    }
  }

  for (i = 0; i < 3; i++) {
    if (memo[n - 1][i] < min) {
      min = memo[n - 1][i];
    }
  }
  writed(min, '\n');
  write(STDOUT_FILENO, WBUF, wp - WBUF);
  return 0;
}

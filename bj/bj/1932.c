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

/******************************************************************/

// some macros

#define max(a, b) ((a) > (b) ? (a) : (b))

int main(void) {
  int n;
  int res = 0;
  int arr[500][500];
  int memo[500][500] = {
      0,
  };
  int i, j;
  read(STDIN_FILENO, RBUF, BUF_SIZE);
  readd(&n);
  for (i = 0; i < n; i++) {
    for (j = 0; j <= i; j++) {
      readd(&arr[i][j]);
    }
  }

  // dp
  memo[0][0] = arr[0][0];
  for (i = 0; i < (n - 1); i++) {
    for (j = 0; j <= i; j++) {
      memo[i + 1][j] = max(memo[i + 1][j], memo[i][j] + arr[i + 1][j]);
      memo[i + 1][j + 1] =
          max(memo[i + 1][j + 1], memo[i][j] + arr[i + 1][j + 1]);
    }
  }
  for (i = 0; i < n; i++) {
    res = max(res, memo[n - 1][i]);
  }
  printf("%d\n", res);
  return 0;
}

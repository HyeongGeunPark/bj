#pragma GCC optimize("O3")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/******************************************************************/

// simple buffered read / write

#define BUF_SIZE 2000000
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
  int n, m;
  int i, j, ii, jj;
  int value;
  int x, y, px, py;
  int result = 0;
  int arr[500][500];
  read(STDIN_FILENO, RBUF, BUF_SIZE);
  readd(&n);
  readd(&m);
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      readd(&arr[i][j]);
    }
  }

  // I shape
  for (i = 3; i < n; i++) {
    for (j = 0; j < m; j++) {
      value = 0;
      for (ii = i - 3; ii <= i; ii++) {
        value += arr[ii][j];
      }
      result = max(result, value);
    }
  }
  // - shape
  for (i = 0; i < n; i++) {
    for (j = 3; j < m; j++) {
      value = 0;
      for (jj = j - 3; jj <= j; jj++) {
        value += arr[i][jj];
      }
      result = max(result, value);
    }
  }
  // O shape
  for (i = 1; i < n; i++) {
    for (j = 1; j < m; j++) {
      value = 0;
      for (ii = i - 1; ii <= i; ii++) {
        for (jj = j - 1; jj <= j; jj++) {
          value += arr[ii][jj];
        }
      }
      result = max(result, value);
    }
  }
  // L, S, T shape
  for (i = 1; i < n; i++) {
    for (j = 2; j < m; j++) {
      value = 0;
      for (ii = i - 1; ii <= i; ii++) {
        for (jj = j - 2; jj <= j; jj++) {
          value += arr[ii][jj];
        }
      }
      // L
      result = max(result, value - arr[i - 1][j - 2] - arr[i - 1][j - 1]);
      result = max(result, value - arr[i][j - 2] - arr[i][j - 1]);
      result = max(result, value - arr[i - 1][j - 1] - arr[i - 1][j]);
      result = max(result, value - arr[i][j - 1] - arr[i][j]);
      // S
      result = max(result, value - arr[i][j] - arr[i - 1][j - 2]);
      result = max(result, value - arr[i][j - 2] - arr[i - 1][j]);
      // T
      result = max(result, value - arr[i][j] - arr[i][j - 2]);
      result = max(result, value - arr[i - 1][j] - arr[i - 1][j - 2]);
    }
  }
  for (i = 2; i < n; i++) {
    for (j = 1; j < m; j++) {
      value = 0;
      for (ii = i - 2; ii <= i; ii++) {
        for (jj = j - 1; jj <= j; jj++) {
          value += arr[ii][jj];
        }
      }
      // L
      result = max(result, value - arr[i - 1][j - 1] - arr[i - 2][j - 1]);
      result = max(result, value - arr[i - 1][j] - arr[i - 2][j]);
      result = max(result, value - arr[i][j - 1] - arr[i - 1][j - 1]);
      result = max(result, value - arr[i][j] - arr[i - 1][j]);
      // S
      result = max(result, value - arr[i][j] - arr[i - 2][j - 1]);
      result = max(result, value - arr[i][j - 1] - arr[i - 2][j]);
      // T
      result = max(result, value - arr[i][j] - arr[i - 2][j]);
      result = max(result, value - arr[i - 2][j - 1] - arr[i][j - 1]);
    }
  }

  writed(result, '\n');
  write(STDOUT_FILENO, WBUF, wp - WBUF);
  return 0;
}

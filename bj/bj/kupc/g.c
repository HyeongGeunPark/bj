/*#pragma GCC optimize("O3")*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/******************************************************************/

// simple buffered read / write

#define RBUF_SIZE 4000000
#define WBUF_SIZE 10
char RBUF[RBUF_SIZE];
char WBUF[WBUF_SIZE];
char* rp = RBUF;
char* wp = WBUF;

static inline int is_num(char* c) { return (*c >= '0' && *c <= '9'); }

static inline char readc() { return *rp++; }

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

static inline int readlld(long long* n) {
  long long r = 0;
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

/******************************************************************/

#define max(a, b) ((a) > (b) ? (a) : (b))

int main(void) {
  int n;
  int i;
  long long a[200004] = {0};
  long long m[200004] = {
      0,
      LLONG_MIN,
      LLONG_MIN,
      0,
  };
  long long res = LLONG_MIN;
  read(STDIN_FILENO, RBUF, RBUF_SIZE);
  readd(&n);
  for (i = 0; i < n; i++) {
    readlld(&a[i]);
  }
  for (i = 1; i < n + 1; i++) {
    m[i] = max(m[i], m[i - 1] + a[i - 1]);
    m[i + 2] = m[i - 1] + 2 * (a[i - 1] + a[i] + a[i + 1]);
  }
  for (i = n; i < n + 3; i++) {
    if (res < m[i]) {
      res = m[i];
    }
  }
  printf("%lld\n", res);
  return 0;
}

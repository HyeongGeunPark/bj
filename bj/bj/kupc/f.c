#pragma GCC optimize("O3")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/******************************************************************/

// simple buffered read / write

#define RBUF_SIZE 300000
#define WBUF_SIZE 20
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

// some macros
static inline int icomp(const void* a, const void* b) {
  const int* aa = (const int*)a;
  const int* bb = (const int*)b;
  return *aa - *bb;
}

#define max(a, b) ((a) > (b) ? (a) : (b))
#define abs(a) ((a) > 0 ? (a) : -(a))

int main(void) {
  int n, m, r;
  int i, j, k;
  int base;
  double area;
  double max_area = -1;
  int post[2000];
  int len[40001] = {0};
  int pole[40000];

  read(STDIN_FILENO, RBUF, RBUF_SIZE);
  readd(&n);
  readd(&m);
  readd(&r);
  for (i = 0; i < n; i++) {
    readd(&post[i]);
  }
  qsort(post, n, sizeof(int), icomp);
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      len[post[j] - post[i]] = 1;
    }
  }
  for (i = 0; i < m; i++) {
    readd(&pole[i]);
  }
  qsort(pole, m, sizeof(int), icomp);

  // brute force
  for (i = 1; i < 40001; i++) {
    if (len[i] == 0) {
      continue;
    }
    base = i;
    // binary search, pole
    int start = 0;
    int end = m;
    int mid;
    while (start < end) {
      mid = (start + end) >> 1;
      area = ((double)base * pole[mid]) / 2;
      if (area < r) {
        start = mid + 1;
      } else {
        end = mid;
      }
    }
    area = ((double)base * pole[start]) / 2;
    if (area != r) {
      start--;
    }
    if (start < 0) {
      continue;
    }
    area = ((double)base * pole[start]) / 2;
    max_area = max(max_area, area);
  }
  if (max_area < 0) {
    printf("-1\n");
  } else {
    printf("%.1lf\n", max_area);
  }

  return 0;
}

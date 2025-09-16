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

static inline readd(long long* n) {
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

static inline void writed(long long n, char end) {
  char buf[40];
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
typedef long long int ll;

int main(void) {
  ll n;
  ll i, j;
  ll memo[100001];
  memo[0] = 0;  // initial point
  ll t[100001] = {-1};
  ll b[100001] = {0};
  ll c[100001] = {0};

  mymmap();

  readd(&n);
  for (i = 1; i <= n; i++) {
    readd(t + i);
  }
  for (i = 1; i <= n; i++) {
    readd(b + i);
  }
  for (i = 1; i <= n; i++) {
    readd(c + i);
  }

  for (i = 1; i <= n; i++) {
    ll tt = t[i] - b[i];
    // binary search
    int l = 0;
    int r = i;
    int mid;
    while (l < r) {
      // l becomes leftmost element which is greater than or equal to tt
      mid = (l + r) / 2;
      if (t[mid] < tt) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    l--;  // rightmost element which is lesser than or equal to tt

    if (memo[i - 1] > memo[l] + c[i]) {
      memo[i] = memo[i - 1];
    } else {
      memo[i] = memo[l] + c[i];
    }
  }
  printf("%lld\n", memo[n]);

  return 0;
}
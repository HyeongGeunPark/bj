/*#pragma GCC optimize("O3")*/

#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

char* RBUF;
char* rp;
#define WBUF_SIZE 1 << 1
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

#define MOD 1000000007

int gcd(int a, int b) {
  int r = a % b;

  while (r) {
    a = b;
    b = r;
    r = a % b;
  }
  return b;
}

struct xgcd_r {
  long long gcd;
  long long s;
  long long t;
};

struct xgcd_r xgcd(int a, int b) {
  struct xgcd_r res;

  long long r, s1, s2, s, t1, t2, t, q;
  s1 = 1;
  s2 = 0;
  t1 = 0;
  t2 = 1;
  while (1) {
    q = a / b;
    r = a - (q * b);
    s = s1 - (q * s2);
    t = t1 - (q * t2);

    if (r == 0) {
      break;
    }
    a = b;
    b = r;
    s1 = s2;
    s2 = s;
    t1 = t2;
    t2 = t;
  }

  res.gcd = b;
  res.s = s2;
  res.t = t2;

  return res;
}

unsigned long long mod_inv(int x, int mod) {
  // 확장 유클리드 호제법
  struct xgcd_r r = xgcd(x, mod);
  unsigned long long res;
  if (r.s < 0) {
    res = (long long)r.s + (unsigned long long)MOD;
  } else {
    res = (unsigned long long)r.s;
  }
  return res;
}

unsigned long long mod_power(int x, int pow, int mod) {
  unsigned long long result = 1;
  unsigned long long temp = x;
  while (pow) {
    if (pow & 1) {
      result = (result * temp) % mod;
    }
    temp = (temp * temp) % mod;
    pow >>= 1;
  }
  return result;
}

unsigned long long mod_inv_fermi(int x, int mod) {
  // 페르마 소정리
  // mod = prime number, x and mod are pairwise prime
  return mod_power(x, mod - 2, mod);
}

int main(void) {
  int m;
  int i;
  unsigned long long result = 0;
  int n, s;
  int g, si;
  mymmap();

  readd(&m);

  for (i = 0; i < m; i++) {
    readd(&n);
    readd(&s);
    g = gcd(n, s);
    n /= g;
    s /= g;
    result = (result + (s * mod_inv_fermi(n, MOD))) % MOD;
  }

  printf("%llu\n", result);

  return 0;
}
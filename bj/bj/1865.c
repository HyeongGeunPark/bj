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

static inline int readd(short* n) {
  short r = 0;
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

static inline void writes(char* c, char end) {
  while (*c) {
    *wp++ = *c++;
  }
  *wp++ = end;
}
#include <limits.h>

struct edge {
  short s, e, t;
};

int bellman(int n, int m, int w, struct edge* edge) {
  int i, j, k;
  int current;
  int minlen[501] = {0};  // all vertice are start point
  int newlen;
  int update;

  for (i = 0; i < n; i++) {
    update = 0;
    for (j = 0; j < m; j++) {
      if (minlen[edge[j].e] > (newlen = minlen[edge[j].s] + edge[j].t)) {
        update = 1;
        minlen[edge[j].e] = newlen;
      }
      if (minlen[edge[j].s] > (newlen = minlen[edge[j].e] + edge[j].t)) {
        update = 1;
        minlen[edge[j].s] = newlen;
      }
    }
    for (j = m; j < w; j++) {
      if (minlen[edge[j].e] > (newlen = minlen[edge[j].s] + edge[j].t)) {
        update = 1;
        minlen[edge[j].e] = newlen;
      }
    }
    if (update == 0) {
      // already in optimal point, there would be no further update
      break;
    }
  }
  if (i == n) {
    // fould a (V)-step route updated
    // which means that there exist at least 1 negative cycle
    return 1;
  } else {
    // no negative cycle detected
    return 0;
  }
}

int main(void) {
  short tc, n, m, w;
  short s, e, t;
  short i, j, k;

  struct edge edges[2700];
  mymmap();

  readd(&tc);

  for (i = 0; i < tc; i++) {
    readd(&n);
    readd(&m);
    readd(&w);
    w += m;
    for (j = 0; j < m; j++) {
      // bidirectional road
      readd(&edges[j].s);
      readd(&edges[j].e);
      readd(&edges[j].t);
    }
    for (j = m; j < w; j++) {
      // unidirectional wormhole
      readd(&edges[j].s);
      readd(&edges[j].e);
      readd(&edges[j].t);
      edges[j].t = -edges[j].t;
    }

    // bellman-ford algorithm
    // return 1 when negative cycle detected
    printf((bellman(n, m, w, edges) ? "YES\n" : "NO\n"));
  }

  return 0;
}

/*#pragma GCC optimize("O3")*/
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

char* RBUF;
char* rp;
#define WBUF_SIZE 1 << 2
char WBUF[WBUF_SIZE];
char* wp = WBUF;
struct stat _stat;

static inline size_t mymmap() {
  fstat(STDIN_FILENO, &_stat);
  RBUF = mmap(NULL, _stat.st_size, PROT_READ, MAP_PRIVATE, STDIN_FILENO, 0);
  rp = RBUF;
}

static inline void mymunmap() { munmap(RBUF, _stat.st_size); }

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

struct edge {
  int dest, cost;
  struct edge* next;
};

struct edge edges[200000];
struct edge* map[100001];
struct edge* ep = edges;

int maxlen = 0;

int dfs(int start, int prev) {
  struct edge* adj = map[start];
  int m1 = 0, m2 = 0;
  for (struct edge* node = adj; node != NULL; node = node->next) {
    int dest = node->dest;
    if (dest != prev) {
      int cost = node->cost + dfs(dest, start);
      if (m1 < cost) {
        m2 = m1;
        m1 = cost;
      } else if (m2 < cost) {
        m2 = cost;
      }
    }
  }
  if (maxlen < (m1 + m2)) {
    maxlen = (m1 + m2);
  }
  return m1;
}

int main(void) {
  int v;
  int i, j;
  int start, dest, cost;
  mymmap();
  readd(&v);

  for (i = 0; i < v; i++) {
    readd(&start);
    for (readd(&dest); dest > 0; readd(&dest)) {
      readd(&cost);
      ep->cost = cost;
      ep->dest = dest;
      ep->next = map[start];
      map[start] = ep++;
    }
  }

  // dfs
  dfs(1, 0);

  printf("%d\n", maxlen);

  // free
  mymunmap();
  return 0;
}
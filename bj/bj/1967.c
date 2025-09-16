/*#pragma GCC optimize("O3")*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/******************************************************************/

// simple buffered read / write

#include <sys/mman.h>
#include <sys/stat.h>

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

static inline void writes(char* c, char end) {
  while (*c) {
    *wp++ = *c++;
  }
  *wp++ = end;
}

/******************************************************************/

#define EDGE_SIZE 10

struct edge {
  int dest;
  int cost;
};

struct edgelist {
  struct edge* edges;
  int size;
  int len;
};

#define edgelist_init(name, n) \
  struct edgelist* name = malloc((n + 1) * sizeof(struct edgelist))

void edgelist_free(struct edgelist* el, int n) {
  for (int i = 1; i <= n; i++) {
    if (el[i].edges != NULL) {
      free(el[i].edges);
    }
  }
  free(el);
}

void edge_add(struct edgelist* el, int dest, int cost) {
  if (el->edges == NULL) {
    el->edges = malloc(EDGE_SIZE * sizeof(struct edge));
    el->len = 0;
    el->size = EDGE_SIZE;
  } else if (el->len == el->size) {
    el->size <<= 1;
    el->edges = realloc(el->edges, el->size * sizeof(struct edge));
  }
  el->edges[el->len].dest = dest;
  el->edges[el->len].cost = cost;
  el->len++;
}

/******************************************************************/
// stack
#define STACK_SIZE 10

struct stack {
  int* data;
  int len;
  int size;
};

#define stack_init(name) \
  struct stack name = {  \
      .len = 0, .size = STACK_SIZE, .data = malloc(STACK_SIZE * sizeof(int))}

#define stack_free(name) free(name.data)

void stack_push(struct stack* s, int data) {
  if (s->len == s->size) {
    s->size <<= 1;
    s->data = realloc(s->data, s->size * sizeof(int));
  }

  s->data[s->len++] = data;
}

int stack_pop(struct stack* s) {
  if (s->len == 0) {
    return 0;
  }
  return s->data[--s->len];
}

/******************************************************************/
#define max(a, b) ((a) > (b) ? (a) : (b))

int main(void) {
  int n;
  int i, j;
  int start, dest, cost;
  int current;
  int farthest_node;
  int farthest_cost;
  int* len;
  stack_init(s);

  mymmap();
  readd(&n);
  edgelist_init(el, n);
  len = calloc((n + 1), sizeof(int));

  for (i = 0; i < n - 1; i++) {
    readd(&start);
    readd(&dest);
    readd(&cost);

    edge_add(&el[start], dest, cost);
    edge_add(&el[dest], start, cost);
  }

  // find farthest node from root, dfs
  start = 1;
  len[start] = 1;
  farthest_cost = 1;

  stack_push(&s, start);

  while (s.len) {
    current = stack_pop(&s);
    struct edgelist* neigh = &el[current];
    for (i = 0; i < neigh->len; i++) {
      struct edge* next = &neigh->edges[i];
      if (len[next->dest] == 0) {
        int nextlen = next->cost + len[current];
        len[next->dest] = nextlen;
        stack_push(&s, next->dest);
        if (farthest_cost < nextlen) {
          farthest_cost = nextlen;
          farthest_node = next->dest;
        }
      }
    }
  }

  // find farthest node from previously found farthest node from root
  memset(len, 0, (n + 1) * sizeof(int));

  start = farthest_node;
  len[start] = 1;
  farthest_cost = 1;

  stack_push(&s, start);

  while (s.len) {
    current = stack_pop(&s);
    struct edgelist* neigh = &el[current];
    for (i = 0; i < neigh->len; i++) {
      struct edge* next = &neigh->edges[i];
      if (len[next->dest] == 0) {
        int nextlen = next->cost + len[current];
        len[next->dest] = nextlen;
        stack_push(&s, next->dest);
        if (farthest_cost < nextlen) {
          farthest_cost = nextlen;
          farthest_node = next->dest;
        }
      }
    }
  }

  printf("%d\n", farthest_cost - 1);

  // free
  edgelist_free(el, n);
  stack_free(s);
  free(len);

  return 0;
}
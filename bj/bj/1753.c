/*#pragma GCC optimize("O3")*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

char* RBUF;
char* rp;
#define WBUF_SIZE 1 << 20
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

/*********************************************************************/
// minheap
#define HEAP_SIZE 1000000
struct heapnode {
  int key;
  int data;
};
struct minheap {
  struct heapnode* data;
  int size;
};
#define minheap_init(name) \
  struct minheap name = {  \
      .data = malloc(sizeof(struct heapnode) * (HEAP_SIZE + 1)), .size = 0}

#define minheap_free(name) free(name.data)

static inline void minheap_add(struct minheap* h, int key, int data) {
  if (h->size == HEAP_SIZE) {
    return;
  }
  int c = ++h->size;
  int p = c >> 1;

  while (p) {
    if (h->data[p].key > key) {
      h->data[c] = h->data[p];
      c = p;
      p = c >> 1;
      continue;
    }
    break;
  }
  h->data[c].data = data;
  h->data[c].key = key;
}

static inline struct heapnode minheap_del(struct minheap* h) {
  struct heapnode r = {0, 0};
  if (h->size == 0) {
    return r;
  }
  r = h->data[1];
  struct heapnode t = h->data[h->size--];

  int p = 1;
  int c = p << 1;
  while (c <= h->size) {
    if (c < h->size && h->data[c].key > h->data[c + 1].key) {
      c++;
    }
    if (h->data[c].key < t.key) {
      h->data[p] = h->data[c];
      p = c;
      c = p << 1;
      continue;
    }
    break;
  }
  h->data[p] = t;
  return r;
}

/*********************************************************************/

// array list for map

#define LIST_SIZE 10

struct edge {
  int dest;
  int len;
};

struct edgelist {
  struct edge* data;
  int size;
  int len;
};

void edge_append(struct edgelist* e, int dest, int len) {
  if (e->data == NULL) {
    e->size = LIST_SIZE;
    e->len = 0;
    e->data = malloc(sizeof(struct edge) * (LIST_SIZE + 1));
  } else if (e->len == e->size) {
    e->size <<= 1;
    e->data = realloc(e->data, sizeof(struct edge) * (e->size + 1));
  }
  e->data[e->len].dest = dest;
  e->data[e->len].len = len;
  e->len++;
}

void edgelist_free(struct edgelist* el, int v) {
  struct edge* temp;
  int i;
  for (i = 1; i <= v; i++) {
    temp = el[i].data;
    if (temp != NULL) {
      free(temp);
    }
  }
  free(el);
}

/*********************************************************************/

int main(void) {
  int v, e;
  int i, j;
  int a, b, c;
  int start;
  char visited[20001] = {0};
  int len[20001];
  int current;
  struct heapnode temp;
  mymmap();

  minheap_init(h);

  struct edgelist* map;

  readd(&v);
  readd(&e);
  readd(&start);
  map = malloc(sizeof(struct edgelist) * (v + 1));
  for (i = 0; i <= v; i++) {
    len[i] = INT_MAX;
  }

  for (i = 1; i <= e; i++) {
    readd(&a);
    readd(&b);
    readd(&c);
    edge_append(&map[a], b, c);
  }

  minheap_add(&h, 0, start);
  len[start] = 0;
  while (h.size) {
    temp = minheap_del(&h);
    current = temp.data;
    if (visited[current]) {
      continue;
    }
    if (temp.key > len[current]) {
      continue;
    }
    struct edgelist* neigh = &map[current];
    for (i = 0; i < neigh->len; i++) {
      int newlen = len[current] + neigh->data[i].len;
      if (len[neigh->data[i].dest] > newlen) {
        len[neigh->data[i].dest] = newlen;
        minheap_add(&h, newlen, neigh->data[i].dest);
      }
    }
    visited[current] = 1;
  }

  for (i = 1; i <= v; i++) {
    if (len[i] == INT_MAX) {
      writes("INF", '\n');
    } else {
      writed(len[i], '\n');
    }
  }

  write_f();

  // free
  edgelist_free(map, v);
  minheap_free(h);

  return 0;
}

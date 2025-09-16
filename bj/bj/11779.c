/*#pragma GCC optimize("O3")*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

char* RBUF;
char* rp;
#define WBUF_SIZE 1 << 13
char WBUF[WBUF_SIZE];
char* wp = WBUF;
size_t filesize;

static inline size_t mymmap() {
  struct stat stat;
  filesize = fstat(STDIN_FILENO, &stat);
  RBUF = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, STDIN_FILENO, 0);
  rp = RBUF;
  return stat.st_size;
}

static inline void mymunmap() { munmap(RBUF, filesize); }

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

/***********************************************************************/
// MINHEAP

#define HEAPSIZE 100000
struct node {
  int value, key;
};

struct minheap {
  struct node* data;
  int size;
  int len;
};

#define minheap_init(name)                 \
  struct minheap name = {.size = HEAPSIZE, \
                         .len = 0,         \
                         .data = malloc((HEAPSIZE + 1) * sizeof(struct node))}
#define minheap_free(name) free(name.data)
#define minheap_size(name) name.len

static inline void minheap_add(struct minheap* h, int value, int key) {
  // c is key, i is value
  int c = ++h->len;
  int p = c >> 1;
  while (p) {
    if (h->data[p].key > key) {
      h->data[c] = h->data[p];
      c = p;
      p = c >> 1;
    } else {
      break;
    }
  }
  h->data[c].key = key;
  h->data[c].value = value;
}

static inline struct node minheap_del(struct minheap* h) {
  struct node r = h->data[1];
  struct node temp = h->data[h->len--];
  int p = 1;
  int c = 2;
  while (c <= h->len) {
    if (c < h->len && h->data[c].key > h->data[c + 1].key) {
      c++;
    }
    if (h->data[c].key < temp.key) {
      h->data[p] = h->data[c];
      p = c;
      c = p << 1;
    } else {
      break;
    }
  }
  h->data[p] = temp;
  return r;
}

/******************************************************************/
// array list map
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

int main(void) {
  int minlen[1001] = {0};
  short prev[1001] = {0};
  int path[1001] = {0};
  int n, m;
  int s, e, t;
  int i, j;
  struct node cur;
  minheap_init(h);
  mymmap();
  readd(&n);
  readd(&m);
  edgelist_init(map, n);
  for (i = 0; i < m; i++) {
    readd(&s);
    readd(&e);
    readd(&t);
    edge_add(map + s, e, t);
  }

  readd(&s);
  readd(&e);

  // dijkstra
  minlen[s] = 1;
  minheap_add(&h, s, 1);
  while (minheap_size(h)) {
    cur = minheap_del(&h);
    struct edgelist* cmap = map + cur.value;
    if (cur.key > minlen[cur.value]) {
      continue;
    } else if (cur.value == e) {
      break;
    }
    for (i = 0; i < cmap->len; i++) {
      int newlen = minlen[cur.value] + cmap->edges[i].cost;
      int dest = cmap->edges[i].dest;
      if (minlen[dest] == 0 || minlen[dest] > newlen) {
        minlen[dest] = newlen;
        prev[dest] = cur.value;
        minheap_add(&h, dest, newlen);
      }
    }
  }

  for (i = 1, j = e; prev[j] != 0; j = prev[j], i++) {
    path[1001 - i] = j;
  }
  path[1001 - i] = s;

  writed(minlen[e] - 1, '\n');
  writed(i, '\n');
  while (i) {
    writed(path[1001 - i], ' ');
    i--;
  }
  *wp++ = '\n';

  write_f();

  edgelist_free(map, n);
  minheap_free(h);
  mymunmap();
  return 0;
}

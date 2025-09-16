#pragma GCC optimize("O3")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/******************************************************************/

// simple buffered read / write

#define BUF_SIZE 1000000
char RBUF[BUF_SIZE];
char WBUF[BUF_SIZE];
char* rp = RBUF;
char* wp = WBUF;

static inline int is_num(char* c) { return (*c >= '0' && *c <= '9'); }

static inline void readd(int* n) {
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

static inline void writes(char* c, char end) {
  while (*c != 0) {
    *(wp++) = *(c++);
  }
  *(wp++) = end;
}

static inline void writec(char c) { *(wp++) = c; }

/******************************************************************/

// auto-resizing simple stack

struct stack {
  int* data;
  int size;
  int len;
};

static inline void stack_push(struct stack* s, int n) {
  if (s->size == s->len) {
    s->size <<= 1;
    s->data = realloc(s->data, sizeof(int) * (s->size));
  }
  s->data[s->len++] = n;
}

static inline int stack_pop(struct stack* s) {
  if (s->len == 0) {
    return 0;
  }
  return s->data[--s->len];
}

static inline int stack_len(struct stack* s) { return s->len; }

/******************************************************************/

int main(void) {
  int n;
  int i, j;
  int t1, t2;
  int c;
  struct stack* cc;
  struct stack* map;
  int* p;
  struct stack s = {
      .data = malloc(sizeof(int) * 100000), .len = 0, .size = 100000};

  read(STDIN_FILENO, RBUF, BUF_SIZE);
  readd(&n);
  map = malloc(sizeof(struct stack) * (n + 1));
  for (i = 0; i < n; i++) {
    map[i].size = 5;
    map[i].len = 0;
    map[i].data = malloc(sizeof(int) * 5);
  }
  p = calloc((n + 1), sizeof(int));

  // bidirectional graph
  for (i = 1; i < n; i++) {
    readd(&t1);
    readd(&t2);
    stack_push(&map[t1], t2);
    stack_push(&map[t2], t1);
  }

  // predecessor find(dfs)
  stack_push(&s, 1);
  p[1] = -1;
  while (stack_len(&s)) {
    c = stack_pop(&s);
    cc = &map[c];
    for (i = 0; i < stack_len(cc); i++) {
      if (p[cc->data[i]] == 0) {
        p[cc->data[i]] = c;
        stack_push(&s, cc->data[i]);
      }
    }
  }
  for (i = 2; i < n + 1; i++) {
    writed(p[i], '\n');
  }

  write(STDOUT_FILENO, WBUF, wp - WBUF);

  for (i = 0; i < n + 1; i++) {
    free(map[i].data);
  }
  free(map);
  free(p);
  free(s.data);
  return 0;
}

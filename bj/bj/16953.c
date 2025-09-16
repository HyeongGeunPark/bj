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

// simple auto-resizing circular queue
#define QUEUE_SIZE 1
struct queue {
  int* data;
  int f;
  int l;
  int size;
};

#define queue_init(name)                                             \
  struct queue name = {.data = malloc(sizeof(int) * QUEUE_SIZE + 1), \
                       .f = 0,                                       \
                       .l = 0,                                       \
                       .size = QUEUE_SIZE}
#define queue_free(name) free(name.data);

static inline int queue_len(struct queue* q) {
  int r = q->l - q->f;
  return r < 0 ? r + q->size + 1 : r;
}

static inline void queue_resize(struct queue* q) {
  if (q->l > q->f) {
    q->size <<= 1;
    q->data = realloc(q->data, sizeof(int) * q->size + 1);
  } else {
    int* temp = malloc(sizeof(int) * 2 * q->size + 1);
    memcpy(temp, &(q->data[q->f]), sizeof(int) * (q->size - q->f + 1));
    memcpy(temp + q->size - q->f + 1, q->data, sizeof(int) * q->l);
    free(q->data);
    q->data = temp;
    q->l = q->size;
    q->f = 0;
    q->size <<= 1;
  }
}

static inline void queue_add_last(struct queue* q, int n) {
  if (queue_len(q) == q->size) {
    queue_resize(q);
  }
  q->data[q->l++] = n;
  if (q->l > q->size) {
    q->l = 0;
  }
}

static inline int queue_del(struct queue* q) {
  if (queue_len(q) == 0) {
    return 0;
  }
  int r = q->data[q->f++];
  if (q->f > q->size) {
    q->f = 0;
  }
  return r;
}

/******************************************************************/
#define TEN_9 1000000000
#define TEN_8 100000000

int main(void) {
  int a, b;
  queue_init(q);
  int cnt, len, current;
  int temp;
  read(STDIN_FILENO, RBUF, BUF_SIZE);
  readd(&a);
  readd(&b);

  // bfs
  cnt = 1;

  queue_add_last(&q, a);
  while ((len = queue_len(&q)) != 0) {
    cnt++;
    while (len--) {
      current = queue_del(&q);
      if (current > (TEN_9 >> 1)) {
        // overflow detection
        continue;
      }

      if ((temp = current << 1) < b) {
        queue_add_last(&q, temp);
      } else if (temp == b) {
        goto solved;
      }
      if (current >= (TEN_8)) {
        // overflow detection
        continue;
      }
      if ((temp = (current * 10 + 1)) < b) {
        queue_add_last(&q, temp);
      } else if (temp == b) {
        goto solved;
      }
    }
  }
  cnt = -1;
solved:
  writed(cnt, '\n');
  write(STDOUT_FILENO, WBUF, wp - WBUF);

  queue_free(q);
  return 0;
}

#pragma GCC optimize("O3")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_SIZE 10000

struct queue {
  int* data;
  int size;
  int f, l;
};

#define queue_init(name)                                           \
  struct queue name = {.data = malloc(sizeof(int) * (QUEUE_SIZE)), \
                       .size = QUEUE_SIZE,                         \
                       .f = 0,                                     \
                       .l = 0}

#define queue_free(name) free(q.data)

static inline int queue_len(struct queue* q) { return q->l - q->f; }

static inline void queue_resize(struct queue* q) {
  int* temp = q->data;
  q->size <<= 1;
  q->data = malloc(sizeof(int) * (q->size));
  memcpy(q->data, (char*)(temp + (q->f)), sizeof(int) * ((q->l) - (q->f)));
  free(temp);
  q->l -= q->f;
  q->f = 0;
}

static inline void queue_add_last(struct queue* q, int n) {
  if (q->l == q->size) {
    queue_resize(q);
  }

  q->data[q->l++] = n;
}

static inline int queue_del(struct queue* q) {
  if (queue_len(q) == 0) {
    return 0;
  }
  return q->data[q->f++];
}

int main(void) {
  int v[100001] = {0};
  int s, g;
  int current;
  int len;
  int cnt;
  queue_init(q);
  scanf("%d %d", &s, &g);

  cnt = 0;
  if (s > 0) {
    while ((s) < 100001) {
      if (s == g) {
        goto print;
      }
      if (v[s] == 0) {
        queue_add_last(&q, s);
        v[s] = 1;
      }
      s <<= 1;
    }
  } else if (s == 0) {
    if (v[s] == 0) {
      queue_add_last(&q, s);
      v[s] = 1;
    }
  }

  while (len = queue_len(&q)) {
    cnt++;
    while (len--) {
      current = queue_del(&q);
      s = current - 1;
      if (s == g) {
        goto print;
      }
      if (s > 0) {
        while ((s) < 100001) {
          if (s == g) {
            goto print;
          }
          if (v[s] == 0) {
            queue_add_last(&q, s);
            v[s] = 1;
          } else {
            break;
          }
          s <<= 1;
        }
      } else if (s == 0) {
        if (v[s] == 0) {
          queue_add_last(&q, s);
          v[s] = 1;
        }
      }
      s = current + 1;
      if (s == g) {
        goto print;
      }
      if (s > 0) {
        while ((s) < 100001) {
          if (s == g) {
            goto print;
          }
          if (v[s] == 0) {
            queue_add_last(&q, s);
            v[s] = 1;
          } else {
            break;
          }
          s <<= 1;
        }
      } else if (s == 0) {
        if (v[s] == 0) {
          queue_add_last(&q, s);
          v[s] = 1;
        }
      }
    }
  }

print:
  queue_free(q);
  printf("%d\n", cnt);
  return 0;
}
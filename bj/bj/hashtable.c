#include <stdio.h>
#include <stdlib.h>
// hashtable for map

#define HASH_SIZE 307
#define HASH_MULTIFLIER 13

struct hashnode {
  int v;
  int l;
  struct hashnode* next;
};

struct hashtable {
  struct hashnode** data;
  int size;
};

static inline int hash(int n) {
  int h = 0;
  while (n) {
    h *= HASH_MULTIFLIER;
    h += n % 10;
    h %= HASH_SIZE;
    n /= 10;
  }
  return h;
}

static inline void hashtable_free(struct hashtable* ht) {
  struct hashnode *pos, *temp;
  for (int i = 0; i < HASH_SIZE; i++) {
    pos = ht->data[i];
    if (pos == NULL) {
      continue;
    }
    while (pos) {
      temp = pos->next;
      free(pos);
      pos = temp;
    }
  }
  free(ht->data);
}

static inline void hashtable_init(struct hashtable* ht) {
  ht->data = calloc(HASH_SIZE, sizeof(struct hashnode*));
  ht->size = HASH_SIZE;
}

static inline struct hashnode* hashnode_create(int v, int l) {
  struct hashnode* new = malloc(sizeof(struct hashnode));
  new->v = v;
  new->l = l;
  new->next = NULL;
  return new;
}

static inline void hashtable_add(struct hashtable* ht, int v, int l) {
  int i = hash(v);
  struct hashnode* pos = ht->data[i];
  if (pos == NULL) {
    ht->data[i] = hashnode_create(v, l);
    return;
  }
  while (pos->next != NULL) {
    if (pos->v == v) {
      if (pos->l > l) {
        pos->l = l;
        return;
      }
    }
    pos = pos->next;
  }
  pos->next = hashnode_create(v, l);
}

static inline struct hashnode* hashtable_find(struct hashtable* ht, int v) {
  int i = hash(v);
  struct hashnode* pos = ht->data[i];
  while (pos) {
    if (pos->v == v) {
      break;
    }
  }
  return pos;
}

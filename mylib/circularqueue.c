#pragma GCC optimize("O3")

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

/******************************************************************/

// simple auto-resizing circular queue
#define QUEUE_SIZE 1 
struct queue{
    int *data;
    int f;
    int l;
    int size;
};

#define queue_init(name) struct queue name = {\
                .data = malloc(sizeof(int)*QUEUE_SIZE+1),\
                .f=0, .l=0, .size=QUEUE_SIZE}
#define queue_free(name) free(name.data);

static inline int queue_len(struct queue *q){
    int r = q->l - q->f;
    return r<0?r+q->size+1:r;
}

static inline void queue_resize(struct queue *q){
    if(q->l > q->f){
        q->size <<= 1;
        q->data = realloc(q->data, sizeof(int)*q->size+1);
    }
    else{
        int *temp = malloc(sizeof(int)*2*q->size+1);
        memcpy(temp, &(q->data[q->f]), sizeof(int) * (q->size - q->f + 1));
        memcpy(temp + q->size - q->f + 1, q->data, sizeof(int)*q->l);
        free(q->data);
        q->data = temp;
        q->l = q->size;
        q->f = 0;
        q->size <<= 1;
    }
}

static inline void queue_add_last(struct queue *q, int n){
    if(queue_len(q)==q->size){
        queue_resize(q);
    }
    q->data[q->l++] = n;
    if(q->l > q->size){
        q->l = 0;
    }
}

static inline int queue_del(struct queue *q){
    if(queue_len(q) == 0){
        return 0;
    }
    int r = q->data[q->f++];
    if(q->f > q->size){
        q->f = 0;
    }
    return r;
}

/******************************************************************/

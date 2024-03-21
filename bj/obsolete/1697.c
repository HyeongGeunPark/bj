// baekjoon gcc optimize options
#pragma GCC optimize("O3")

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**************************************************************************/

// resizable circular queue

#define QUEUE_SIZE 1000

struct queue{
    int *data;
    int size;
    int f;
    int r;
};

#define queue_init(name) struct queue name={\
        .data=malloc(sizeof(int)*(QUEUE_SIZE+1)), .size=QUEUE_SIZE,\
        .f=0, .r=0}

#define queue_free(name) free(name.data)

static inline int queue_is_empty(struct queue *q){
    return (q->f==q->r);
}

static inline int queue_is_full(struct queue *q){
    int n = (q->r-q->f);
    return n==1 || n==-q->size;
}

static inline void queue_resize(struct queue *q){
    if(q->f>q->r){
        q->size += QUEUE_SIZE;
        q->data = realloc(q->data, sizeof(int)*(q->size+1));
        return;
    }
    else{
        int *dest = malloc(sizeof(int)*(q->size+QUEUE_SIZE+1));
        int to_end = (q->size+1)-(q->r);
        memcpy(dest, q->data+q->r, sizeof(int)*to_end);
        memcpy(dest + to_end, q->data, sizeof(int)*q->f);
        free(q->data);
        q->data = dest;
        q->r = 0;
        q->f = q->size;
        q->size += QUEUE_SIZE;
    }
    return;
}

static inline void queue_add_last(struct queue *q, int n){
    if(queue_is_full(q)){
        queue_resize(q);
    }

    q->data[q->f] = n;

    if(q->f==q->size){
        q->f=0;
    }
    else{
        q->f++;
    }
}

static inline int queue_del(struct queue *q){
    if(queue_is_empty(q)){
        printf("queue error: queue is empty\n");
        return 0;
    }
    int r = q->data[q->r];
    if(q->r==q->size){
        q->r=0;
    }
    else{
        q->r++;
    }
    return r;
}

/**************************************************************************/

int main(void){
    int n, k;
    scanf("%d %d", &n, &k);
    if(n==k){
        printf("0");
        return 0;
    }

    // bfs
    queue_init(q);
    int *t = calloc(100001, sizeof(int));
    queue_add_last(&q, n);
    t[n] = 1;
    int i, r;
    while(1){
        i = queue_del(&q);

        if(i+1 == k){
            r = t[i]+1;
            break;
        }
        else if(i+1<100001 && t[i+1]==0){
            t[i+1] = t[i]+1;
            queue_add_last(&q, i+1);
        }
        if(i-1 == k){
            r = t[i]+1;
            break;
        }
        else if(i-1>=0 && t[i-1]==0){
            t[i-1] = t[i]+1;
            queue_add_last(&q, i-1);
        }
        if(i*2 == k){
            r = t[i]+1;
            break;
        }
        else if(i*2<100001 && t[i*2]==0){
            t[i*2] = t[i]+1;
            queue_add_last(&q, i*2);
        }
    }

    printf("%d\n", r-1);

    queue_free(q);
    free(t);

    return 0;
}
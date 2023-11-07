/*#pragma GCC optimize("O3")*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

// minheap
#define HEAP_SIZE 10000
struct heapnode{
    int key;
    int data;
};
struct minheap{
    struct heapnode* data;
    int size;
};
#define minheap_init(name) struct minheap name = {\
        .data = malloc(sizeof(struct heapnode)*(HEAP_SIZE+1)),\
        .size = 0}

#define minheap_free(name) free(name.data)

static inline void minheap_add(struct minheap *h, struct heapnode new){
    if(h->size == HEAP_SIZE){
        return;
    }
    int c = ++h->size;
    int p = c>>1;

    while(p){
        if(h->data[p].key > new.key){
            h->data[c] = h->data[p];
            c = p;
            p = c>>1;
            continue;
        }
        break;
    }
    h->data[c] = new;
}

static inline struct heapnode minheap_del(struct minheap *h){
    struct heapnode r = {0, 0};
    if(h->size == 0){
        return r;
    }
    r = h->data[1];
    struct heapnode t = h->data[h->size--];

    int p = 1;
    int c = p<<1;
    while(c<=h->size){
        if(c<h->size && h->data[c].key > h->data[c+1].key){
            c++;
        }
        if(h->data[c].key < t.key){
            h->data[p] = h->data[c];
            p = c;
            c = p<<1;
            continue;
        }
        break;
    }
    h->data[p] = t;
    return r;
}


int main(void){

    short map[801][801] = {0};
    int len[801];
    char visited[801];
    int n, e;
    int a, b, c;
    int i, j, k;
    int s, g1, g2;
    long long result[6];
    long long res0, res1, res2;
    int start[3];
    int v1, v2;
    int goal[6];
    struct heapnode temp, cur;
    minheap_init(h);
    scanf("%d %d", &n, &e);

    for(i=0;i<e;i++){
        scanf("%d %d %d", &a, &b, &c);
        map[a][b] = c;
        map[b][a] = c;
    }
    scanf("%d %d", &v1, &v2);

    start[0] = v2;
    start[1] = 1;
    start[2] = n;
    goal[0] = 0;
    goal[1] = goal[3] = goal[5] = v1;
    goal[2] = goal[4] = v2;


    visited[0] = 1;

    // dijkstra
    for(i=0;i<3;i++){
        s = start[i];
        g1 = goal[2*i];
        g2 = goal[2*i+1];
        memset(visited+1, 0, n+1);
        for(j=0;j<=n;j++){
            len[j] = INT_MAX;
        }
        h.size = 0;
        len[s] = 0;
        temp.key = len[s];
        temp.data = s;
        minheap_add(&h, temp);

        while(h.size!=0 && (visited[g1] == 0 || visited[g2] == 0)){
            cur = minheap_del(&h);
            if(visited[cur.data]){
                continue;
            }
            for(j=1;j<=n;j++){
                if(map[cur.data][j] != 0 && visited[j] == 0){
                    temp.data = j;
                    temp.key = cur.key+map[cur.data][j];
                    if(len[j] > temp.key){
                        len[j] = temp.key;
                        minheap_add(&h, temp);
                    }
                }
            }
            visited[cur.data] = 1;
        }
        result[2*i] = len[g1];
        result[2*i+1] = len[g2];
    }



    res0 = result[1];
    res1 = result[2]+result[5];
    res2 = result[3]+result[4];

    if(res0>=INT_MAX || (res1>=INT_MAX && res2>=INT_MAX)){
        res0 = -1;
    }
    else if(res1>res2){
        res0 += res2;
    }
    else{
        res0 += res1;
    }
    printf("%lld\n", res0);

    minheap_free(h);

    return 0;
}
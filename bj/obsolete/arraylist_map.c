
#include<stdio.h>
#include<stdlib.h>
/******************************************************************/

#define EDGE_SIZE 10

struct edge{
    int dest;
    int cost;
};

struct edgelist{
    struct edge *edges;
    int size;
    int len;
};

#define edgelist_init(name, n) struct edgelist *name = \
                        malloc((n+1)*sizeof(struct edgelist))

void edgelist_free(struct edgelist *el, int n){
    for(int i=1;i<=n;i++){
        if(el[i].edges!=NULL){
            free(el[i].edges);
        }
    }
    free(el);
}

void edge_add(struct edgelist *el, int dest, int cost){
    if(el->edges==NULL){
        el->edges = malloc(EDGE_SIZE * sizeof(struct edge));
        el->len = 0;
        el->size = EDGE_SIZE;
    }
    else if(el->len == el->size){
        el->size <<= 1;
        el->edges = realloc(el->edges, el->size * sizeof(struct edge));
    }
    el->edges[el->len].dest = dest;
    el->edges[el->len].cost = cost;
    el->len++;
}

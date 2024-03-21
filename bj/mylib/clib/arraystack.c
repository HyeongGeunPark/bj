#include<stdio.h>
#include<stdlib.h>
// stack
#define STACK_SIZE 10

struct stack{
    int *data;
    int len;
    int size;
};

#define stack_init(name) struct stack name = {.len = 0, .size = STACK_SIZE,\
                .data = malloc(STACK_SIZE * sizeof(int))}

#define stack_free(name) free(name.data)

void stack_push(struct stack *s, int data){
    if(s->len == s->size){
        s->size <<= 1;
        s->data = realloc(s->data, s->size * sizeof(int));
    }

    s->data[s->len++] = data;

}

int stack_pop(struct stack *s){
    if(s->len==0){
        return 0;
    }
    return s->data[--s->len];
}
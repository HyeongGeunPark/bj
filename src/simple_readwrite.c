/*#pragma GCC optimize("O3")*/

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

/******************************************************************/

// simple buffered read / write

#define BUF_SIZE 200000
char RBUF[BUF_SIZE];
char WBUF[BUF_SIZE];
char *rp = RBUF;
char *wp = WBUF;

static inline int is_num(char* c){
    return (*c>='0' && *c<='9');
}

static inline int readd(int *n){
    int r = 0;
    int sign = 1;
    while(1){
        if(is_num(rp)){
            break;
        }
        else if(*rp=='-'){
            sign = 0;
            break;
        }
        rp++;
    }
    while(1){
        r *= 10;
        r += ((*rp++) - '0');
        if(!is_num(rp)){
            break;
        }
    }
    *n = sign?r:-r;
}

static inline void writed(int n, char end){
    char buf[20];
    int sign = 1;
    int i = 0;
    if(n<0){
        sign = 0;
        n = -n;
    }
    while(1){
        buf[i++] = n%10 + '0';
        n /= 10;
        if(n==0){
            break;
        }
    }
    if(sign==0){
        buf[i++] = '-';
    }
    while(i>0){
        *(wp++) = buf[--i];
    }
    *wp++ = end;
}

/******************************************************************/

// simple stack

#define STACK_SIZE 100000

struct stack{
    int *data;
    int len;
};

#define stack_init(name) struct stack name={\
                .data=malloc(sizeof(int)*STACK_SIZE), .len=0}
#define stack_free(name) free(name.data)

static inline int stack_pop(struct stack *s){
    if(s->len == 0){
        return 0;
    }
    return s->data[--s->len];
}

static inline void stack_push(struct stack *s, int n){
    s->data[s->len++] = n;
}

static inline int stack_len(struct stack *s){
    return s->len;
}

/******************************************************************/

// some macros

#define max(a, b) ((a)>(b)?(a):(b))

int main(void){

    int n, m;
    int i, j;
    int d;
    int value;
    int x, y, px, py;
    int result=0;
    int arr[500][500];
    read(STDIN_FILENO, RBUF, BUF_SIZE);
    readd(&n);
    readd(&m);
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            readd(&arr[i][j]);
        }
    }


    writed(result, '\n');
    write(STDOUT_FILENO, WBUF, wp-WBUF);
    return 0;
}

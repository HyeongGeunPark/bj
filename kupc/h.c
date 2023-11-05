/*#pragma GCC optimize("O3")*/

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<limits.h>

/******************************************************************/

// simple buffered read / write

/*
#define RBUF_SIZE 4000000
#define WBUF_SIZE 10
char RBUF[RBUF_SIZE];
char WBUF[WBUF_SIZE];
char *rp = RBUF;
char *wp = WBUF;
*/
char *RBUF = NULL;
char *rp = NULL;
char *WBUF = NULL;
char *wp = NULL;

#define rbuf_init(len) RBUF=malloc(sizeof(char)*len);rp=RBUF
#define wbuf_init(len) WBUF=malloc(sizeof(char)*len);wp=WBUF
#define rbuf_free() free(RBUF)
#define wbuf_free() free(WBUF)

static inline int is_num(char* c){
    return (*c>='0' && *c<='9');
}

static inline char readc(){
    return *rp++;
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
            rp++;
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

static inline int readlld(long long *n){
    long long r = 0;
    int sign = 1;
    while(1){
        if(is_num(rp)){
            break;
        }
        else if(*rp=='-'){
            sign = 0;
            rp++;
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

static inline void reads(char *c){
    while(1){
        if(*rp>32){
            break;
        }
        rp++;
    }
    while(1){
        *(c++) = *(rp++);
        if(*rp == '\n' || *rp == 0){
            break;
        }
    }
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

static inline void writelld(long long n, char end){
    char buf[60];
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
#define RBUF_SIZE 5000000
#define WBUF_SIZE 5000000

#define max(a, b) ((a)>(b)?(a):(b))

int main(void){

    int n, m, q;
    int i, j;
    int x, y;
    long long temp;
    long long **pond;
    RBUF = malloc(sizeof(char)*RBUF_SIZE);
    rp = RBUF;
    WBUF = malloc(sizeof(char)*WBUF_SIZE);
    wp = WBUF;

    read(STDIN_FILENO, RBUF, RBUF_SIZE);


    readd(&n);
    readd(&m);
    readd(&q);

    pond = malloc(sizeof(long long*)*n);
    for(i=0;i<n;i++){
        pond[i] = malloc(sizeof(long long)*m);
    }


    for(j=0;j<m;j++){
        readlld(&pond[0][j]);
    }
    for(i=1;i<n;i++){
        readlld(&temp);
        pond[i][0] = pond[i-1][0] + temp;
        for(j=1;j<m;j++){
            readlld(&temp);
            pond[i][j] = pond[i-1][j-1] + pond[i-1][j] + temp;
        }
    }

    for(i=0;i<q;i++){
        readd(&x);
        readd(&y);
        writelld(pond[x-1][y-1], '\n');
    }
    write(STDOUT_FILENO, WBUF, wp-WBUF);

    rbuf_free();
    wbuf_free();
    for(i=0;i<n;i++){
        free(pond[i]);
    }
    free(pond);

    return 0;
}

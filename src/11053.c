#pragma GCC optimize("O3")

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

/******************************************************************/

// simple buffered read / write

#define BUF_SIZE 1000000
char RBUF[BUF_SIZE];
char WBUF[BUF_SIZE];
char *rp = RBUF;
char *wp = WBUF;

static inline int is_num(char* c){
    return (*c>='0' && *c<='9');
}

static inline void readd(int *n){
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

static inline void writes(char *c, char end){
    while(*c != 0){
        *(wp++) = *(c++);
    }
    *(wp++) = end;
}

static inline void writec(char c){
    *(wp++) = c;
}

/******************************************************************/

#define max(a,b) ((a)>(b)?(a):(b))

int main(void){
    int n;
    int i, j;
    int res;
    int arr[1000];
    int memo[1000] = {0};


    read(STDIN_FILENO, RBUF, BUF_SIZE);
    readd(&n);
    for(i=0;i<n;i++){
        readd(&arr[i]);
    }

    for(i=0;i<n;i++){
        // forward propagation
        for(j=i+1; j<n;j++){
            if(arr[j] > arr[i])
                memo[j] = max(memo[j], memo[i]+1);
        }
    }
    // find max
    res = 0;
    for(i=0;i<n;i++){
        res = max(res, memo[i]);
    }
    writed(res+1, '\n');
    write(STDOUT_FILENO, WBUF, wp-WBUF);
    return 0;
}

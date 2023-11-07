#pragma GCC optimize("O3")

#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#include<unistd.h>

/******************************************************************/

// simple buffered read / write

#define RBUF_SIZE 650000
#define WBUF_SIZE 10
char RBUF[RBUF_SIZE];
char WBUF[WBUF_SIZE];
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

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

int main(void){

    int n;
    int i, j;
    int res1 = 0;
    int res2 = INT_MAX;
    int arr[100000][3] = {0};
    int mem[100000][3];
    read(STDIN_FILENO, RBUF, RBUF_SIZE);
    readd(&n);

    for(i=0;i<n;i++){
        for(j=0;j<3;j++){
            readd(&arr[i][j]);
        }
    }

    for(i=0;i<3;i++){
        mem[0][i] = arr[0][i];
    }
    for(i=1;i<n;i++){
        mem[i][0] = arr[i][0] + max(mem[i-1][0], mem[i-1][1]);
        mem[i][1] = arr[i][1] + max(max(mem[i-1][0], mem[i-1][1]), mem[i-1][2]);
        mem[i][2] = arr[i][2] + max(mem[i-1][1], mem[i-1][2]);
    }
    for(i=0;i<3;i++){
        if(res1<mem[n-1][i]){
            res1 = mem[n-1][i];
        }
    }

    for(i=1;i<n;i++){
        mem[i][0] = arr[i][0] + min(mem[i-1][0], mem[i-1][1]);
        mem[i][1] = arr[i][1] + min(min(mem[i-1][0], mem[i-1][1]), mem[i-1][2]);
        mem[i][2] = arr[i][2] + min(mem[i-1][1], mem[i-1][2]);
    }
    for(i=0;i<3;i++){
        if(res2>mem[n-1][i]){
            res2 = mem[n-1][i];
        }
    }
    writed(res1, ' ');
    writed(res2, '\n');
    write(STDOUT_FILENO, WBUF, wp-WBUF);
    return 0;
}
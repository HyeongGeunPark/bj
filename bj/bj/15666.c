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

static inline int icomp(const void *a, const void *b){
    const int *aa = (const int*)a;
    const int *bb = (const int*)b;
    return *aa-*bb;
}

static inline void permute(int depth, int n, int m, int *node, int *path){
    int i;
    if(depth == m){
        //print
        for(i=0;i<m;i++){
            writed(node[path[i]], ' ');
        }
        writec('\n');
    }
    else{
        for(i=(depth==0?0:path[depth-1]);i<n;i++){
            path[depth] = i;
            permute(depth+1, n, m, node, path);
            while(i<n && node[i] == node[i+1]){
                i++;
            }
        }
    }
}

int main(void){
    int n, m;
    int i;
    int node[8];
    int path[8];
    int selected[8] = {0};

    read(STDIN_FILENO, RBUF, BUF_SIZE);
    readd(&n);
    readd(&m);
    for(i=0;i<n;i++){
        readd(node+i);
    }
    qsort(node, n, sizeof(int), icomp);

    permute(0, n, m, node, path);

    write(STDOUT_FILENO, WBUF, wp-WBUF);

    return 0;
}

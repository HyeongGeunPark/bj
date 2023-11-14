#pragma GCC optimize("O3")

// 5~101
#include<stdio.h>
#include<unistd.h>
#include<string.h>

#include<sys/stat.h>
#include<sys/mman.h>

char *RBUF;
char *rp;
#define WBUF_SIZE 1<<20
char WBUF[WBUF_SIZE];
char *wp = WBUF;

static inline size_t mymmap(){
    struct stat stat;
    fstat(STDIN_FILENO, &stat);
    RBUF = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, STDIN_FILENO, 0);
    rp = RBUF;
    return stat.st_size;
}

static inline int is_num(char* c){
    return (*c>='0' && *c<='9');
}

static inline void write_f(void){
    write(STDOUT_FILENO, WBUF, wp-WBUF);
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

static inline void writes(char *c, char end){
    while(*c){
        *wp++ = *c++;
    }
    *wp++ = end;
}


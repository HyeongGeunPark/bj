/*#pragma GCC optimize("O3")*/

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<limits.h>

/******************************************************************/

// simple buffered read / write

#include<sys/stat.h>
#include<sys/mman.h>

char *RBUF;
char *rp;
#define WBUF_SIZE 1<<24
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

/******************************************************************/

#define max(a, b) ((a)>(b)?(a):(b))

int main(void){

    int n, m, q;
    int i, j;
    int x, y;
    int temp;
    int **pond;
    mymmap();


    readd(&n);
    readd(&m);
    readd(&q);

    pond = malloc(sizeof(int*)*(n+2));
    for(i=0;i<=n+1;i++){
        pond[i] = calloc(m+1, sizeof(int));
    }


    for(i=2;i<=n+1;i++){
        for(j=1;j<=m;j++){
            readd(&temp);
            pond[i][j] = pond[i-1][j] + pond[i-1][j-1] - pond[i-2][j-1]+ temp;
        }
    }

    for(i=0;i<q;i++){
        readd(&x);
        readd(&y);
        writed(pond[x+1][y], '\n');
    }

    write_f();

    for(i=0;i<n+1;i++){
        free(pond[i]);
    }
    free(pond);

    return 0;
}

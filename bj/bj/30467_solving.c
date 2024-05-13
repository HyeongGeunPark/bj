/*#pragma GCC optimize("O3")*/

#include<stdio.h>
#include<unistd.h>
#include<string.h>

#include<sys/stat.h>
#include<sys/mman.h>

char *RBUF;
char *rp;
#define WBUF_SIZE 1<<2
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



int main(void){

    int n, s;
    int i, j;
    int max_wish;
    int wish;
    int speed[100000];

    mymmap();

    readd(&n);
    readd(&s);

    for(i=0;i<n;i++){
        readd(speed+i);
    }

    wish = 0;
    for(i=0;i<s;i++){
        for(j=i+1;j<s;j++){
            if(speed[i]<speed[j]){
                wish++;
            }
        }
    }

    max_wish = wish;

    // windowing
    n -= s;
    for(i=0;i<n;i++){
        // remove first & add last
        for(j=i+1;j<i+s;j++){
            if(speed[i]<speed[j]){
                wish--;
            }
            if(speed[j]<speed[i+1]){
                wish++;
            }
        }

        // update max value
        if(max_wish<wish){
            max_wish = wish;
        }
    }

    printf("%d\n", max_wish);
    return 0;
}
#pragma GCC optimize("O3")

#include<stdio.h>
#include<unistd.h>
#include<string.h>

#include<sys/stat.h>
#include<sys/mman.h>

char *RBUF;
char *rp;
#define WBUF_SIZE 1<<1
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

#define max(a,b) ((a)>(b)?(a):(b))

int main(void){

    int n;
    int i, j;
    int result;
    int temp;
    int arr[1000];
    int fwd[1000] = {0};
    int bwd[1000] = {0};
    mymmap();

    readd(&n);
    for(i=0;i<n;i++){
        readd(&arr[i]);
    }

    // fwd dp
    for(i=0;i<n;i++){
        for(j=0;j<i;j++){
            if(arr[j]<arr[i] && fwd[i]<=fwd[j]){
                fwd[i] = fwd[j]+1;
            }
        }
    }

    // bwd dp
    result = 0;
    for(i=n-1;i>=0;i--){
        for(j=n-1;j>i;j--){
            if(arr[j]<arr[i] && bwd[i]<=bwd[j]){
                bwd[i] = bwd[j]+1;
            }
        }
        temp = bwd[i] + fwd[i];
        if(result < temp){
            result = temp;
        }
    }

    printf("%d\n" ,result+1);
    return 0;

}
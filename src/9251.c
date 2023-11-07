#pragma GCC optimize("O3")

#include<stdio.h>
#include<unistd.h>
#include<string.h>

#include<sys/stat.h>
#include<sys/mman.h>

char *RBUF;

static inline size_t mymmap(){
    struct stat stat;
    fstat(STDIN_FILENO, &stat);
    RBUF = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, STDIN_FILENO, 0);
    return stat.st_size;
}

#define max(a,b) ((a)>(b)?(a):(b))

int main(void){

    int lcs[1002] = {0};
    int i, j;
    int mm, t;
    int len_a, len_b;

    char a[1002];
    char b[1002];

    size_t filesize = mymmap();
    sscanf(RBUF, " %s\n %s\n", a+1, b+1);
    len_a = strlen(a+1)+1;
    len_b = strlen(b+1)+1;


    // lcs - DP
    for(i=1;i<len_a;i++){
        mm = 0;
        for(j=1;j<len_b;j++){
            t = lcs[j];
            if(a[i] == b[j]){
                lcs[j] = max(mm+1, lcs[j]);
            }
            else{
                lcs[j] = max(lcs[j], lcs[j-1]);
            }
            mm = t;
        }
    }
    printf("%d\n", lcs[len_b-1]);

    return 0;

}

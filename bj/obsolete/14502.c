/*#pragma GCC optimize("O3")*/

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
size_t inputfilesize;

static inline size_t mymmap(){
    struct stat stat;
    inputfilesize = fstat(STDIN_FILENO, &stat);
    RBUF = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, STDIN_FILENO, 0);
    rp = RBUF;
    return stat.st_size;
}

static inline void mymunmap(){
    munmap(RBUF, inputfilesize);
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




int main(void){

    int i, j, k;
    int a, b, c;
    int space_num = 0;
    int virus_num = 0;
    int map[10][10];
    int tmap[10][10];
    int virus[64][2];
    int space[64][2];
    int n, m;

    int v_queue[100][2];
    int q_first;
    int q_last;
    mymmap();
    readd(&n);
    readd(&m);
    // bracket
    for(i=0;i<m+2;i++){
        tmap[0][i] = 1;
        tmap[n+1][i] = 1;
    }
    for(i=0;i<n+2;i++){
        tmap[i][0] = 1;
        tmap[i][m+1] = 1;
    }

    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            readd(&map[i][j]);
            if(map[i][j]==0){
                space[space_num][0] = i;
                space[space_num++][1] = j;
            }
            if(map[i][j]==2){
                v_queue[virus_num][0] = i;
                v_queue[virus_num++][1] = j;
            }
        }
    }

    int min_queue = 100;

    // wall select(brute force)
    for(i=0;i<space_num;i++){
        map[space[i][0]][space[i][1]] = 1;
        for(j=i+1;j<space_num;j++){
            map[space[j][0]][space[j][1]] = 1;
            for(k=j+1;k<space_num;k++){
                map[space[k][0]][space[k][1]] = 1;
                // map initialize
                for(a=1;a<=n;a++){
                    for(b=1;b<=m;b++){
                        tmap[a][b] = map[a][b];
                    }
                }

                // virus bfs
                q_first = 0;
                q_last = virus_num;
                while(q_last != q_first){
                    int x, y;
                    x = v_queue[q_first][0];
                    y = v_queue[q_first++][1];
                    // boundary check
                    if(tmap[x-1][y]==0){
                        tmap[x-1][y] = 2;
                        v_queue[q_last][0] = x-1;
                        v_queue[q_last++][1] = y;
                        if(q_last >= min_queue){
                            break;
                        }
                    }
                    if(tmap[x+1][y]==0){
                        tmap[x+1][y] = 2;
                        v_queue[q_last][0] = x+1;
                        v_queue[q_last++][1] = y;
                        if(q_last >= min_queue){
                            break;
                        }
                    }
                    if(tmap[x][y-1]==0){
                        tmap[x][y-1] = 2;
                        v_queue[q_last][0] = x;
                        v_queue[q_last++][1] = y-1;
                        if(q_last >= min_queue){
                            break;
                        }
                    }
                    if(tmap[x][y+1]==0){
                        tmap[x][y+1] = 2;
                        v_queue[q_last][0] = x;
                        v_queue[q_last++][1] = y+1;
                        if(q_last >= min_queue){
                            break;
                        }
                    }
                    // backtrack

                }
                if(min_queue > q_last){
                    min_queue = q_last;
                }
                map[space[k][0]][space[k][1]] = 0;
            }
            map[space[j][0]][space[j][1]] = 0;
        }
        map[space[i][0]][space[i][1]] = 0;
    }

    mymunmap();
    printf("%d\n", space_num - 3 - min_queue + virus_num);
    return 0;
}

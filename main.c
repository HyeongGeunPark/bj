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

int map[8][8];
int tmap[8][8];
int virus[64][2];
int space[64][2];
int n, m;

int v_queue[100][2];
int q_first;
int q_last;


int main(void){

    int i, j, k;
    int a, b, c;
    int space_num = 0;
    int virus_num = 0;
    scanf("%d %d", &n, &m);
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            scanf("%d", &map[i][j]);
            if(map[i][j]==0){
                space[space_num][0] = i;
                space[space_num][1] = j;
                space_num++;
            }
            if(map[i][j]==2){
                virus[virus_num][0] = i;
                virus[virus_num][1] = j;
                virus_num++;
            }
        }
    }

    int max_safe = 0;

    // wall select(brute force)
    for(i=0;i<space_num;i++){
        for(j=i+1;j<space_num;j++){
            for(k=j+1;k<space_num;k++){
                //selected wall -> space[i], space[j], space[k]
                int sx[3] = {space[i][0], space[j][0], space[k][0]};
                int sy[3] = {space[i][1], space[j][1], space[k][1]};
                tmap[8][8]; //temporary map
                memcpy(tmap, map, sizeof(int) * 64);
                for(a=0;a<3;a++){
                    tmap[sx[a]][sy[a]] = 1;  // make wall
                }

                // virus bfs
                int safe_num = space_num-3;
                q_first = q_last = 0;
                for(a=0;a<virus_num;a++){
                    v_queue[q_last][0] = virus[a][0];
                    v_queue[q_last][1] = virus[a][1];
                    q_last++;
                }
                while(q_last != q_first){
                    int x, y, xx, yy;
                    int dx[4] = {0, 0, 1, -1};
                    int dy[4] = {1, -1, 0, 0};
                    x = v_queue[q_first][0];
                    y = v_queue[q_first][1];
                    q_first++;
                    for(b=0;b<4;b++){
                        xx = x+dx[b];
                        yy = y+dy[b];
                        if( 0>xx || n<=xx) continue;    //boundary check
                        if( 0>yy || m<=yy) continue;
                        if(tmap[xx][yy]!=0) continue;   // visited check
                        tmap[xx][yy] = 2;
                        safe_num--;
                        v_queue[q_last][0] = xx;
                        v_queue[q_last][1] = yy;
                        q_last++;
                    }
                }
                if(safe_num > max_safe){
                    max_safe = safe_num;
                }
            }
        }
    }

    printf("%d\n", max_safe);
    return 0;
}

// gdb debug functions
void tmapp(){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%2d ", tmap[i][j]);
        }
        printf("\r\n");
    }
}
void mapp(){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%2d ", map[i][j]);
        }
        printf("\r\n");
    }
}

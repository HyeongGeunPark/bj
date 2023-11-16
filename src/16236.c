/*#pragma GCC optimize("O3")*/
#include<stdio.h>
#include<stdlib.h>

struct pos{
    int x, y;
};

#define Q_SIZE 1000
struct pos q[Q_SIZE];
struct pos s[500];
int ql = 0, qf = 0;
int sl = 0;

int pos_comp(const void *a, const void *b){
    const struct pos *aa = (const struct pos *)a;
    const struct pos *bb = (const struct pos *)b;
    if(aa->x == bb->x){
        return aa->y-bb->y;
    }
    else{
        return aa->x-bb->x;
    }
}

#define queue_add_last(a, b) q[ql].x=(a);q[ql].y=(b);if(++ql==Q_SIZE)ql=0
#define queue_del(a, b) (a)=q[qf].x;(b)=q[qf].y;if(++qf==Q_SIZE)qf=0
#define stack_add(a, b) s[sl].x=(a);s[sl++].y=(b)

// bfs
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};
int time = 0;
int size = 2;
int eaten = 0;
#define not_in_range(x, n) ((x)<0 || (x)>=(n))
struct pos bfs(int x, int y, int n, int (*visited)[20], int (*map)[20]){
    sl = ql = qf = 0;
    int qe;
    int i, j;
    int xx, yy;
    int initial_time = time--;

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            visited[i][j] = 0;
        }
    }

    queue_add_last(x, y);
    visited[x][y] = 1;
    map[x][y] = 0;
    while(ql!=qf && !sl){
        qe = ql;
        while(qf!=qe){
            queue_del(x, y);
            // found nearest edible fish
            if(map[x][y] != 0 && map[x][y] < size){
                stack_add(x, y);
            }
            for(i=0;i<4;i++){
                xx = x + dx[i];
                yy = y + dy[i];
                if(not_in_range(xx, n) || not_in_range(yy, n)){
                    continue;
                }
                if(visited[xx][yy] == 1){
                    continue;
                }
                if(map[xx][yy] > size){
                    continue;
                }
                visited[xx][yy] = 1;
                queue_add_last(xx, yy);
            }
        }
        time++;
    }
    // found
    if(sl){
        qsort(s, sl, sizeof(struct pos), pos_comp);
        x = s[0].x;
        y = s[0].y;
        map[x][y] = 0;
        eaten++;
        if(eaten==size){
            size++;
            eaten = 0;
        }
        return (struct pos){.x=x, .y=y};
    }
    // not found
    else{
        time = initial_time;
        return (struct pos){.x=-1, .y=-1};
    }
}

int main(void){
    int n;
    int i, j;
    int map[20][20];
    int visited[20][20] = {0};
    struct pos s;


    scanf("%d", &n);
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            scanf("%d", &map[i][j]);
            if(map[i][j]==9){
                s.x = i;
                s.y = j;
            }
        }
    }

    while(s.x>=0){
        s = bfs(s.x, s.y, n, visited, map);
/*        mp(map, n);*/
    }

    printf("%d\n", time);
    return 0;
}

/*void mp(int (*map)[20], int n){*/
/*    int i, j;*/
/*    for(i=0;i<n;i++){*/
/*        for(j=0;j<n;j++){*/
/*            printf("%2d", map[i][j]);*/
/*        }*/
/*        printf("\n");*/
/*    }*/
/*    printf("\n");*/
/*}*/
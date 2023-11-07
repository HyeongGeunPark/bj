/*#pragma GCC optimize("O3")*/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static inline int  isnum(char c){
    return c>='0' && c<='9';
}

#define QUEUE_SIZE 1000

struct queue{
    int *data;
    int size;
    int f, l;
};

#define queue_init(name) struct queue name = {\
            .data = malloc(sizeof(int)*(QUEUE_SIZE+1)), .f=0, .l=0}
#define queue_free(name) free(name.data);

static inline void queue_resize(struct queue *q){
    q->size+=QUEUE_SIZE;
    int *temp  = q->data;
    q->data = malloc(sizeof(int)*(q->size));
    memcpy(q->data, &(temp[q->f]), sizeof(int)*(q->l-q->f));
    free(temp);
    q->l -= q->f;
    q->f = 0;
}

static inline int queue_len(struct queue *q){
    return q->l - q->f;
}

static inline void queue_add_last(struct queue *q, int data){
    if(q->l == q->size){
        queue_resize(q);
    }
    q->data[q->l++] = data;
}

static inline int queue_del(struct queue *q){
    if(queue_len(q)==0){
        return 0;
    }
    return q->data[q->f++];
}

int main(void){

    int n, m;
    int i, j;
    int temp;
    int truth;
    int party_len;
    int party_people[51][51] = {0};
    int updated;
    int people_truth[51] = {0};
    int party_truth[51] = {0};
    int people_truth_len;
    queue_init(q);
    
    scanf("%d %d", &n, &m);

    scanf("%d", &people_truth_len);
    for(j=0;j<people_truth_len;j++){
        scanf("%d", &temp);
        queue_add_last(&q, temp);
        people_truth[temp] = 1;
    }

    for(i=1;i<=m;i++){
        scanf("%d", &party_len);
        for(j=0;j<party_len;j++){
            scanf("%d", &temp);
            party_people[i][temp] = 1;
        }
    }

    while(queue_len(&q)){
        temp = queue_del(&q);
        for(i=1;i<=m;i++){
            if(party_people[i][temp] && party_truth[i] == 0){
                party_truth[i] = 1;
                for(j=1;j<=n;j++){
                    if(party_people[i][j] && people_truth[j]==0){
                        people_truth[j] = 1;
                        queue_add_last(&q, j);
                    }
                }
            }
        }
    }

    temp = 0;
    for(i=1;i<=m;i++){
        if(party_truth[i]==0){
            temp++;
        }
    }
    printf("%d\n", temp);
    queue_free(q);
    return 0;
}
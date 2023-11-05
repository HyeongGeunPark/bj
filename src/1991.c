#pragma GCC optimize("O3")

#include<stdio.h>

struct tree_node{
    char c;
    struct tree_node *l, *r;
};

void preorder(struct tree_node *t){
    if(t==NULL){
        return;
    }
    printf("%c", t->c);
    preorder(t->l);
    preorder(t->r);
}

void inorder(struct tree_node *t){
    if(t==NULL){
        return;
    }
    inorder(t->l);
    printf("%c", t->c);
    inorder(t->r);
}

void postorder(struct tree_node *t){
    if(t==NULL){
        return;
    }
    postorder(t->l);
    postorder(t->r);
    printf("%c", t->c);
}

int main(void){

    char p, l, r;
    struct tree_node t[26];
    int n;
    int i, j;
    scanf("%d\n", &n);
    for(i=0;i<n;i++){
        t[i].c = i+'A';
    }
    for(i=0;i<n;i++){
        scanf("%c ", &p);
        scanf("%c ", &l);
        scanf("%c ", &r);
        if(l!='.'){
            t[p-'A'].l = &t[l-'A'];
        }
        else{
            t[p-'A'].l = NULL;
        }
        if(r!='.'){
            t[p-'A'].r = &t[r-'A'];
        }
        else{
            t[p-'A'].r = NULL;
        }
    }
    preorder((struct tree_node *)t); printf("\n");
    inorder((struct tree_node *)t); printf("\n");
    postorder((struct tree_node *)t); printf("\n");

    return 0;
}
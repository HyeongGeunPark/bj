/***********************************************************************/
// MINHEAP

#define HEAPSIZE 20000
struct node{
    int value, key;
};

struct minheap{
    struct node *data;
    int size;
    int len;
};

#define minheap_init(name) struct minheap name = {.size = HEAPSIZE, .len = 0,\
            .data = malloc((HEAPSIZE+1) * sizeof(struct node))}
#define minheap_free(name) free(name.data)

static inline void minheap_add(struct minheap *h, int value, int key){
    // c is key, i is value
    int c = ++h->len;
    int p = c>>1;
    while(p){
        if(h->data[p].key > key){
            h->data[c] = h->data[p];
            c = p;
            p = c>>1;
        }
        else{
            break;
        }
    }
    h->data[c].key = key;
    h->data[c].value = value;
}

static inline struct node minheap_del(struct minheap *h){
    struct node r = h->data[1];
    struct node temp = h->data[h->len--];
    int p = 1;
    int c = 2;
    while(c<=h->len){
        if(c<h->len && h->data[c].key > h->data[c+1].key){
            c++;
        }
        if(h->data[c].key < temp.key){
            h->data[p] = h->data[c];
            p = c;
            c = p<<1;
        }
        else{
            break;
        }
    }
    h->data[p] = temp;
    return r;
}

/***********************************************************************/
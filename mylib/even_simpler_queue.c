// even simpler circular queue

struct pos{
    char x, y;
};

#define Q_SIZE 10000
struct pos q[Q_SIZE];
int ql = 0, qf = 0;

#define queue_add_last(a, b) q[ql].x=(a);q[ql].y=y;if(++ql==Q_SIZE)ql=0

#define queue_del(a, b) (a)=q[qf].x;(b)=q[qf].y;if(++qf==Q_SIZE)qf=0



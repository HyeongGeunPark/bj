// even simpler circular queue

/******************************************************************/
// coordinate
struct pos{
    char x, y;
};

#define Q_SIZE 10000
struct pos q[Q_SIZE];
int ql = 0, qf = 0;

#define queue_add_last(a, b) q[ql].x=(a);q[ql].y=y;if(++ql==Q_SIZE)ql=0
#define queue_del(a, b) (a)=q[qf].x;(b)=q[qf].y;if(++qf==Q_SIZE)qf=0
#define queue_len() (ql-qf>0?ql-qf:ql-qf+Q_SIZE)
#define queue_is_full() (ql==qf)

/******************************************************************/
// one integer value

#define Q_SIZE 2000
int q[Q_SIZE];
int ql = 0, qf = 0;

#define queue_add_last(a) q[ql]=(a);if(++ql==Q_SIZE)ql=0
#define queue_del(a) (a)=q[qf];if(++qf==Q_SIZE)qf=0

/******************************************************************/
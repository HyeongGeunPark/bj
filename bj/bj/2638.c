/*#pragma GCC optimize("O3")*/
#include <stdio.h>

const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {1, -1, 0, 0};

int map[100][100];
char visited[100][100];
int n, m;

struct pos {
  char x, y;
};

#define Q_SIZE 10000
struct pos q[Q_SIZE];
int ql = 0, qf = 0;

#define queue_add_last(a, b) \
  q[ql].x = (a);             \
  q[ql].y = (b);             \
  if (++ql == Q_SIZE) ql = 0
#define queue_del(a, b) \
  (a) = q[qf].x;        \
  (b) = q[qf].y;        \
  if (++qf == Q_SIZE) qf = 0

int not_in_range(int x, int n) { return x < 0 || x >= n; }

int dfs(int x, int y) {
  // start point: (x, y)

  int i;
  int xx, yy;
  for (i = 0; i < 4; i++) {
    xx = x + dx[i];
    yy = y + dy[i];
    if (not_in_range(xx, n) || not_in_range(yy, m)) {
      continue;
    }
    if (map[xx][yy] == 0 && visited[xx][yy] == 0) {
      visited[xx][yy] = 1;
      dfs(xx, yy);
    } else if (map[xx][yy] != 0) {
      map[xx][yy]++;
      if (map[xx][yy] == 3) {
        queue_add_last(xx, yy);
      }
    }
  }
}

int main(void) {
  int i, j;
  int t;

  scanf("%d %d", &n, &m);
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      scanf("%d", &map[i][j]);
    }
  }
  // First, using dfs, find cheese block which contacts 2 side with outside
  dfs(0, 0);

  t = 0;
  // Next, from the cheese blocks found previously, do dfs
  while (qf != ql) {
    t++;
    int q_end = ql;
    while (qf != q_end) {
      queue_del(i, j);
      dfs(i, j);
    }
  }

  printf("%d\n", t);

  return 0;
}

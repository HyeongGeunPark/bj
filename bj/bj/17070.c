/*#pragma GCC optimize("O3")*/

typedef enum _direction { HORIZONTAL = 0, DIAGONAL, VERTICAL } direction;

#include <stdio.h>

int main(void) {
  int n;
  int map[17][17] = {0};
  int mem[17][17][3] = {0};
  int i, j, k;
  int result;
  direction d;
  // map input
  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      scanf("%d", &map[i][j]);
    }
  }

  // dp
  mem[0][1][HORIZONTAL] = 1;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      for (d = HORIZONTAL; d < 3; d++) {
        if (d != VERTICAL && map[i][j + 1] == 0) {
          mem[i][j + 1][HORIZONTAL] += mem[i][j][d];
        }
        if (map[i][j + 1] == 0 && map[i + 1][j] == 0 &&
            map[i + 1][j + 1] == 0) {
          mem[i + 1][j + 1][DIAGONAL] += mem[i][j][d];
        }
        if (d != HORIZONTAL && map[i + 1][j] == 0) {
          mem[i + 1][j][VERTICAL] += mem[i][j][d];
        }
      }
    }
  }

  result = 0;
  for (d = 0; d < 3; d++) {
    result += mem[n - 1][n - 1][d];
  }

  printf("%d\n", result);
  return 0;
}
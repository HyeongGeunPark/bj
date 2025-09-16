/*#pragma GCC optimize("O3")*/

#include <stdio.h>
int r, c, t;
int room[52][52];
int new_room[52][52];

int cleaner_c;
int cleaner_up;
int cleaner_down;

void diffusion() {
  int i, j, k;
  int dx[4] = {0, 0, -1, 1};
  int dy[4] = {-1, 1, 0, 0};
  // initialize new_room
  for (i = 1; i <= r; i++) {
    for (j = 1; j <= c; j++) {
      new_room[i][j] = 0;
    }
  }

  // calculate diffusion
  for (i = 1; i <= r; i++) {
    for (j = 1; j <= c; j++) {
      if (room[i][j] == 0 || room[i][j] == -1) {
        continue;
      }
      int x, y;
      int base = room[i][j] / 5;
      new_room[i][j] += room[i][j];

      for (k = 0; k < 4; k++) {
        x = i + dx[k];
        y = j + dy[k];
        if (room[x][y] == -1) {
          continue;
        }
        new_room[x][y] += base;
        new_room[i][j] -= base;
      }
    }
  }

  // save calculated values
  for (i = 1; i <= r; i++) {
    for (j = 1; j <= c; j++) {
      if (room[i][j] == -1) continue;
      room[i][j] = new_room[i][j];
    }
  }
}

void cleaner() {
  int i;
  for (i = cleaner_c; i > 1; i--) {
    if (room[i][cleaner_up] == -1) continue;
    room[cleaner_up][i] = room[cleaner_up][i - 1];
    room[cleaner_down][i] = room[cleaner_down][i - 1];
  }

  for (i = cleaner_up; i > 1; i--) {
    if (room[i][1] == -1) {
      continue;
    } else {
      room[i][1] = room[i - 1][1];
    }
  }

  for (i = cleaner_down; i < r; i++) {
    if (room[i][1] == -1) {
      continue;
    } else {
      room[i][1] = room[i + 1][1];
    }
  }

  // 위 아래 변
  for (i = 1; i < c; i++) {
    room[1][i] = room[1][i + 1];
    room[r][i] = room[r][i + 1];
  }

  for (i = 1; i < cleaner_up; i++) {
    if (room[i + 1][c] == -1) {
      room[i][c] = 0;
      break;
    }
    room[i][c] = room[i + 1][c];
  }

  for (i = r; i > cleaner_down; i--) {
    if (room[i - 1][c] == -1) {
      room[i][c] = 0;
      break;
    }
    room[i][c] = room[i - 1][c];
  }

  for (i = c; i > cleaner_c; i--) {
    if (room[cleaner_up][i - 1] == -1) {
      room[cleaner_up][i] = 0;
      room[cleaner_down][i] = 0;
      break;
    }
    room[cleaner_up][i] = room[cleaner_up][i - 1];
    room[cleaner_down][i] = room[cleaner_down][i - 1];
  }
}

int main(void) {
  int i, j, k;

  scanf("%d %d %d", &r, &c, &t);

  for (i = 1; i <= r; i++) {
    for (j = 1; j <= c; j++) {
      scanf("%d", &room[i][j]);
      if (room[i][j] == -1) {
        cleaner_c = j;
        cleaner_down = i;
      }
    }
  }
  for (i = 0; i <= r + 1; i++) {
    room[i][0] = -1;
    room[i][c + 1] = -1;
  }
  for (i = 0; i <= c + 1; i++) {
    room[0][i] = -1;
    room[r + 1][i] = -1;
  }

  cleaner_up = cleaner_down - 1;

  while (t--) {
    diffusion();
    /*        roomp();*/
    cleaner();
    /*        roomp();*/
  }

  int result = 0;
  for (i = 1; i <= r; i++) {
    for (j = 1; j <= c; j++) {
      if (room[i][j] > 0) {
        result += room[i][j];
      }
    }
  }

  printf("%d\n", result);

  return 0;
}

/*void roomp(){*/
/*    int i, j;*/
/*    for(i=1;i<=r;i++){*/
/*        for(j=1;j<=c;j++){*/
/*            printf("%3d", room[i][j]);*/
/*        }*/
/*        printf("\r\n");*/
/*    }*/
/*    printf("\r\n");*/
/*}*/

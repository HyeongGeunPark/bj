#pragma GCC optimize("O3")
#include <stdio.h>
#define abs(a) (((a) > 0) ? (a) : -(a))
#define min(a, b) ((a) > (b) ? (b) : (a))

int main(void) {
  int n, m;
  int i, j, k;
  int temp;
  int crashed[10] = {0};
  int res;
  int mag;
  int r;
  int found;

  scanf("%d %d", &n, &m);
  for (i = 0; i < m; i++) {
    scanf("%d", &temp);
    crashed[temp] = 1;
  }

  res = abs(n - 100);
  for (i = 0; i < res; i++) {
    for (j = -1; j < 2; j += 2) {
      found = 1;
      temp = n + i * j;
      if (temp < 0) continue;
      mag = 0;
      do {
        mag++;
        r = temp % 10;
        if (crashed[r]) {
          found = 0;
          break;
        }
        temp /= 10;
      } while (temp);
      if (found) {
        res = min(res, mag + i);
        goto print;
      }
    }
  }
print:
  printf("%d\n", res);

  return 0;
}
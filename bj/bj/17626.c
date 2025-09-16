#define N_MAX 50000
#include <math.h>
#include <stdio.h>

#define min(a, b) (((a) > (b)) ? (b) : (a))

int main(void) {
  int n;
  scanf("%d", &n);
  int s = (int)sqrt(n);
  int ans;

  int i, j, k;
  for (i = 0; i <= s; i++) {
    for (j = i; j <= s; j++) {
      for (k = j; k <= s; k++) {
        if (n != ((i * i) + (j * j) + (k * k))) continue;
        if (i == 0 && j == 0) {
          ans = 1;
          goto print;
        }
        if (i == 0) {
          ans = 2;
          goto print;
        }
        ans = 3;
        goto print;
      }
    }
  }
  ans = 4;
print:
  printf("%d", ans);
  return 0;
}

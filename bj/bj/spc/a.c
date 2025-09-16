/*#pragma GCC optimize("O3")*/

#include <stdio.h>

int main(void) {
  int l1, r1;
  int l2, r2;
  int t;
  int jam = 0;

  scanf("%d", &t);
  scanf("%d %d", &l1, &r1);
  if (l1 != 0 && l1 == r1) {
    jam++;
  }

  t--;

  while (t--) {
    scanf("%d %d", &l2, &r2);
    if (l2 != 0 && l2 == l1) {
      jam++;
    }
    if (r2 != 0 && r2 == r1) {
      jam++;
    }
    if (l2 != 0 && l2 == r2) {
      jam++;
    }
    l1 = l2;
    r1 = r2;
  }

  printf("%d\n", jam);
  return 0;
}
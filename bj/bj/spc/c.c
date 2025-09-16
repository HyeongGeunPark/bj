/*#pragma GCC optimize("O3")*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int icomp(const void* a, const void* b) {
  int* aa = (int*)a;
  int* bb = (int*)b;
  return *aa - *bb;
}

int main(void) {
  int n, m;
  int l, r;
  int i, j;
  int A[301];
  int AA[301];
  int B[301];

  scanf(" %d", &n);

  for (i = 1; i <= n; i++) {
    scanf(" %d", A + i);
  }

  scanf(" %d", &m);

  for (i = 0; i < m; i++) {
    scanf(" %d %d", &l, &r);
    for (j = 1; j <= n; j++) {
      B[A[j]] = j;
    }
    qsort(B + l, r - l + 1, sizeof(int), icomp);
    for (j = 1; j <= n; j++) {
      AA[B[j]] = j;
    }

    for (j = 1; j <= n; j++) {
      printf("%d ", AA[j]);
    }
    printf("\n");
  }

  return 0;
}
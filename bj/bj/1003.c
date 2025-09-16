#include <stdio.h>
#define NMAX 40
int main(void) {
  int t;
  int fib[NMAX + 1] = {0};
  int calculated = 1;
  fib[0] = 0;
  fib[1] = 1;
  scanf("%d", &t);
  for (int i = 0; i < t; i++) {
    int n;
    scanf("%d", &n);
    if (n == 0) {
      printf("1 0\n");
      continue;
    }
    for (int j = (calculated + 1); j <= n; j++) {
      fib[j] = fib[j - 1] + fib[j - 2];
    }
    calculated = n;
    printf("%d %d\n", fib[n - 1], fib[n]);
  }
  return 0;
}

#pragma GCC optimize("O3")

#include <stdio.h>
#include <stdlib.h>

#define DUCK 0
#define GOOSE 1
#define MAX_LEN 200000

int main(void) {
  unsigned int n;
  scanf("%d", &n);
  if (n & 1) {
    printf("Goose\n");
  } else {
    printf("Duck\n");
  }
  return 0;
}
#include <stdio.h>

int main() {
  int i, j, n = 2, m = 4, B[4][2];
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      scanf("%d", &B[j][n - 1 - i]);
    }
  }
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      if (j < n - 1) {
        printf("%d ", B[i][j]);
      } else {
        printf("%d", B[i][j]);
      }
    }
    if (i < m - 1) {
      printf("\n");
    }
  }
  return 0;
}

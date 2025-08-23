#include <stdio.h>
#include <stdlib.h>
int main() {
  int n, err = 0, sum = 0;
  if (scanf("%d", &n) == 1) {
    char ch;
    ch = getchar();
    if (ch == ' ' || ch == '\n' || ch == '\0') {
      int *vector = (int *)malloc(n * 2 * sizeof(int));
      for (int i = 0; i < n * 2; i++) {
        if (scanf("%d", &vector[i]) == 1) {
          char ch;
          ch = getchar();
          if (i < 2 * n - 1) {
            if (ch == ' ' || ch == '\n' || ch == '\0') {
            } else {
              err = 1;
            }
          } else {
            if (ch == ' ' || ch == '\n' || ch == '\0' || ch == EOF) {
            } else {
              err = 1;
            }
          }
        } else {
          err = 1;
        }
      }
      for (int i = 0; i < n; i++) {
        sum += vector[i] * vector[i + n];
      }

      free(vector);
    } else {
      err = 1;
    }
  } else {
    err = 1;
  }
  if (err == 0) {
    printf("%d", sum);
  } else if (err == 1) {
    printf("n/a");
  }
  return 0;
}

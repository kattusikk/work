#include <stdio.h>
#include <stdlib.h>

int main() {
  int *num;
  int i;
  num = (int *)malloc(1 * sizeof(int));
  for (i = 0; scanf("%d", &num[i]) == 1 && num[i] != -1; i++) {
    num = (int *)realloc(num, (i + 2) * sizeof(int));
  }
  int count = i, pos_max = 0, pos_min = 0;
  for (i = 1; i < count; i++) {
    if (num[i] > num[pos_max]) {
      pos_max = i;
    }
    if (num[i] < num[pos_min]) {
      pos_min = i;
    }
  }
  int tmp = num[pos_max];
  num[pos_max] = num[pos_min];
  num[pos_min] = tmp;
  for (i = 0; i < count; i++) {
    printf("%d", num[i]);
    if (i != count - 1) {
      printf(" ");
    }
  }
  free(num);
  return 0;
}

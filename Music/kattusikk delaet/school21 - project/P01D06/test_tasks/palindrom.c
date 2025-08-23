#include <stdio.h>
#include <stdlib.h>

int main() {
  char *str;
  int i;
  str = (char *)malloc(1 * sizeof(char));
  for (i = 0; scanf("%c", &str[i]) == 1 && str[i] != '\n'; i++) {
    if (str[i] != ' ') {
      if (str[i] >= 65 && str[i] <= 90) {
        str[i] += 32;
      }
      str = (char *)realloc(str, (i + 2) * sizeof(char));
    } else {
      i--;
    }
  }
  int count = i, res = 1;
  for (i = 0; i < (count + 1) / 2; i++) {
    if (str[i] != str[count - 1 - i]) {
      res = 0;
      break;
    }
  }
  if (res) {
    printf("Yes");
  } else {
    printf("No");
  }
  free(str);
  return 0;
}

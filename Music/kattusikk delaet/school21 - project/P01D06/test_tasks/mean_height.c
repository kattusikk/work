#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  typedef struct students {
    char name[21], surname[21];
    int height;
  } STUDENTS;
  int num, err = 0;
  if (scanf("%d", &num) == 1) {
    STUDENTS *stu;
    stu = (STUDENTS *)malloc(num * sizeof(STUDENTS));
    char buf[21];
    for (int i = 0; i < num; i++) {
      if (scanf("%s", stu[i].name) == 1) {
        if (scanf("%s", stu[i].surname) == 1) {
          if (scanf("%d", &stu[i].height) == 1 && stu[i].height > 0) {
            err = 0;
          } else {
            err = 1;
          }
        } else {
          err = 1;
        }
      } else {
        err = 1;
      }
    }
    if (!err) {
      if (scanf("%s", buf) == 1) {
        char **ptr;
        int count = 0;
        double sum = 0;
        ptr = (char **)malloc(num * sizeof(char *));
        for (int i = 0; i < num; i++) {
          ptr[i] = (char *)malloc(21 * sizeof(char));
        }
        for (int i = 0; i < num; i++) {
          if (!strcmp(stu[i].name, buf)) {
            count++;
            ptr[count - 1] = stu[i].surname;
            sum += stu[i].height;
          }
        }
        for (int i = 0; i < count; i++) {
          printf("%s", ptr[i]);
          if (i < count - 1) {
            printf(", ");
          } else {
            printf(": ");
          }
        }
        free(ptr);
        printf("%.0f", round(sum / count));
      } else {
        err = 1;
      }
    }
    free(stu);
  } else {
    err = 1;
  }
  if (err == 1) {
    printf("n/a");
  }
  return 0;
}

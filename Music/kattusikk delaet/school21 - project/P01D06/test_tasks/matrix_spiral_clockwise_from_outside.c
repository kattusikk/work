#include <stdio.h>
void input_spiral_matrix(int up, int down, int left, int right, int **matrix,
                         char ch, int i, int j, int direction);
int main() {
  int row, column;
  if (scanf("%d %d", &row, &column) == 2 && row > 0 && column > 0) {
    int matrix[15][15];
    int *p[15];
    int **mat = (int **)p;
    for (int k = 0; k < 15; k++) {
      mat[k] = (int *)matrix + k * 15;
    }
    input_spiral_matrix(row - 1, 0, -1, column - 1, mat, 'j', 0, 0, 1);
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < column; j++) {
        printf("%d ", matrix[i][j]);
      }
      if (i < row - 1) printf("\n");
    }
  } else {
    printf("n/a");
  }
  return 0;
}
void input_spiral_matrix(int up, int down, int left, int right, int **matr,
                         char ch, int i, int j, int direction) {
  scanf("%d", &matr[i][j]);
  if (ch == 'j') {
    if (j * direction < right * direction) {
      input_spiral_matrix(up, down, left, right, matr, ch, i, j + direction,
                          direction);
    } else {
      ch = 'i';
      if (j == right) {
        left += direction;
      } else {
        right -= direction;
        direction *= -1;
      }
      if (up != down) {
        input_spiral_matrix(down, up, left, right, matr, ch, i + direction, j,
                            direction);
      }
    }
  } else if (ch == 'i') {
    if (i * direction < down * direction) {
      input_spiral_matrix(up, down, left, right, matr, ch, i + direction, j,
                          direction);
    } else {
      ch = 'j';
      if (i == down) {
        up += direction;
        direction *= -1;
      } else {
        down -= direction;
      }
      if (left != right) {
        input_spiral_matrix(up, down, right, left, matr, ch, i, j + direction,
                            direction);
      }
    }
  }
}

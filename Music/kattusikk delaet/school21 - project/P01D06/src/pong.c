#include <stdio.h>
#include <stdlib.h>
#ifdef LINUX
#include <unistd.h>
#endif
#ifdef WINDOWS
#include <windows.h>
#endif

void draw_field();
void draw_field2();
void char_map();
void mySleep(int sleepMs);

const int HEIGHT = 25-1;
const int WIDTH = 80 - 1;

int main() {
  //system("clear");
  draw_field();
  mySleep(10000);
  printf("\x1b[7A");
  printf("^^^^^");
  // system("clear");
  // draw_field2();
  // char_map();
  return 0;
}

void char_map() {
  for (int i = 0; i <= 0xFF; i++) {
    printf("%c", i);
  }
}

void draw_field() {
  int i, j;
  for (i = 0; i <= HEIGHT; i++) {
    for (j = 0; j <= WIDTH; j++) {
      if ((i == 0 || i == HEIGHT) && j != WIDTH)
        printf("-");
      else if (j == WIDTH)
        printf("\n");
      else if ((j == 0 || j == WIDTH - 1) && i != 0 && i != HEIGHT)
        printf("|");
      else if ((j == (WIDTH - 1) / 2) && i != 0 && i != HEIGHT)
        printf("|");
      else
        printf("$");
    }
  }
}
void draw_field2() {
  int i, j;
  for (i = 0; i <= HEIGHT; i++) {
    for (j = 0; j <= WIDTH; j++) {
      if (i == 5 && j == 5) printf("*");
      if ((i == 0 || i == HEIGHT) && j != WIDTH)
        printf("-");
      else if (j == WIDTH)
        printf("\n");
      else if ((j == 0 || j == WIDTH - 1) && i != 0 && i != HEIGHT)
        printf("|");
      else if ((j == (WIDTH - 1) / 2) && i != 0 && i != HEIGHT)
        printf("|");
      else
        printf(" ");
    }
  }
}

void mySleep(int sleepMs)
{
#ifdef LINUX
    usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#endif
#ifdef WINDOWS
    Sleep(sleepMs);
#endif
}

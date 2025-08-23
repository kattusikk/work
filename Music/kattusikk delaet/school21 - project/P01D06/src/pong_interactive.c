#include <ncurses.h>
#include <stdio.h>

int game_over(int score_left, int score_right) {
    int result = 0;
    if (score_left >= 21 || score_right >= 21) {
        result = 1;
    }
    return result;
}

void print_winner(int score_left, int score_right) {
    clear();
    if (score_left > score_right) {
        printw("Win player 1\n");
    } else {
        printw("Win player 2\n");
    }
    refresh();
    getch();
}

int check_goal(int ball_x) {
    int result = 0;
    if (ball_x <= 0) {
        result = 1;
    } else if (ball_x >= 80 - 1) {
        result = 2;
    }
    return result;
}

int move_paddle_1(char move, int paddle_y) {
    int new_y = paddle_y;
    if ((move == 'a' || move == 'A') && paddle_y > 1) {
        new_y--;
    } else if ((move == 'z' || move == 'Z') && paddle_y < 25 - 3 - 1) {
        new_y++;
    }
    return new_y;
}

int move_paddle_2(char move, int paddle_y) {
    int new_y = paddle_y;
    if ((move == 'k' || move == 'K') && paddle_y > 1) {
        new_y--;
    } else if ((move == 'm' || move == 'M') && paddle_y < 25 - 3 - 1) {
        new_y++;
    }
    return new_y;
}

int update_ball(int ball_x, int ball_dx) {
    int new_x = ball_x + ball_dx;
    return new_x;
}

int bounce_y(int ball_y, int ball_dy) {
    int new_dy = ball_dy;
    if (ball_y <= 1 || ball_y >= 25 - 2) {
        new_dy = -ball_dy;
    }
    return new_dy;
}

int bounce_x(int ball_x, int ball_y, int ball_dx, int paddle1_y, int paddle2_y) {
    int new_dx = ball_dx;
    if (ball_x == 3 && ball_y >= paddle1_y && ball_y < paddle1_y + 3) {
        new_dx = -ball_dx;
    } else if (ball_x == 80 - 4 && ball_y >= paddle2_y && ball_y < paddle2_y + 3) {
        new_dx = -ball_dx;
    }
    return new_dx;
}

void draw_field(int ball_x, int ball_y, int paddle1_y, int paddle2_y, int score_left, int score_right) {
    clear();
    for (int x = 0; x < 80; x++) {
        printw("-");
    }
    printw("\n");

    for (int y = 1; y < 25 - 1; y++) {
        for (int x = 0; x < 80; x++) {
            if (x == 0 || x == 80 - 1) {
                printw("|");
            } else if (x == 80 / 2) {
                printw("|");
            } else if (x == 2 && y >= paddle1_y && y < paddle1_y + 3) {
                printw("|");
            } else if (x == 80 - 3 && y >= paddle2_y && y < paddle2_y + 3) {
                printw("|");
            } else if (x == ball_x && y == ball_y) {
                printw("*");
            } else {
                printw(" ");
            }
        }
        printw("\n");
    }

    for (int x = 0; x < 80; x++) {
        printw("-");
    }
    printw("\n");

    printw("Player 1: %d (A/Z) | Player 2: %d (K/M)\n", score_left, score_right);
    refresh();
}

int reset_ball_dx(int direction) {
    int dx = -1;
    if (direction == 1) {
        dx = 1;
    }
    return dx;
}

int reset_ball_dy(int direction) {
    int dy = -1;
    if (direction == 1) {
        dy = 1;
    }
    return dy;
}

int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    int paddle1_y = 25 / 2, paddle2_y = 25 / 2;
    int ball_x = 80 / 2, ball_y = 25 / 2, ball_dx = -1, ball_dy = 1;
    int score_left = 0, score_right = 0;
    while (!game_over(score_left, score_right)) {
        draw_field(ball_x, ball_y, paddle1_y, paddle2_y, score_left, score_right);
        char move = getch();
        paddle1_y = move_paddle_1(move, paddle1_y);
        paddle2_y = move_paddle_2(move, paddle2_y);
        ball_x = update_ball(ball_x, ball_dx);
        ball_y = update_ball(ball_y, ball_dy);
        ball_dy = bounce_y(ball_y, ball_dy);
        ball_dx = bounce_x(ball_x, ball_y, ball_dx, paddle1_y, paddle2_y);
        int goal = check_goal(ball_x);
        if (goal == 1) {
            score_right++;
            ball_x = 80 / 2, ball_y = 25 / 2;
            ball_dx = reset_ball_dx(goal);
            ball_dy = reset_ball_dy(goal);
        } else if (goal == 2) {
            score_left++;
            ball_x = 80 / 2, ball_y = 25 / 2;
            ball_dx = reset_ball_dx(goal);
            ball_dy = reset_ball_dy(goal);
        }
        napms(50);
    }
    endwin();
    print_winner(score_left, score_right);
    return 0;
}

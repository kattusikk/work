#include <stdio.h>
#include <ncurses>

void clear_screen() { printf("\033[H\033[J"); }

int game_over(int score_left, int score_right) {
    int result = 0;
    if (score_left >= 21 || score_right >= 21) {
        result = 1;
    }
    return result;
}

void print_winner(int score_left, int score_right) {
    if (score_left > score_right) {
        printf("Win player 1\n");
    } else {
        printf("Win player 2\n");
    }
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

int move_paddle1(char move, int paddle_y) {
    int new_y = paddle_y;
    if ((move == 'a' || move == 'A') && paddle_y > 1) {
        new_y--;
    } else if ((move == 'z' || move == 'Z') && paddle_y < 25 - 3 - 1) {
        new_y++;
    }
    return new_y;
}

int move_paddle2(char move, int paddle_y) {
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
    if (ball_y <= 2 || ball_y >= 23) {
        new_dy = -ball_dy;
    }
    return new_dy;
}

int bounce_x(int ball_x, int ball_y, int ball_dx, int paddle1_y, int paddle2_y) {
    int new_dx = ball_dx;
    if (ball_x == 2 && ball_y >= paddle1_y && ball_y < paddle1_y + 3) {
        new_dx = -ball_dx;
    } else if (ball_x == 80 - 3 && ball_y >= paddle2_y && ball_y < paddle2_y + 3) {
        new_dx = -ball_dx;
    }
    return new_dx;
}

void draw_field(int ball_x, int ball_y, int paddle1_y, int paddle2_y, int score_left, int score_right) {
    clear_screen();
    for (int x = 0; x < 80; x++) {
        printf("-");
    }
    printf("\n");
    for (int y = 1; y < 25 - 1; y++) {
        for (int x = 0; x < 80; x++) {
            if (x == 0 || x == 80 - 1) {
                printf("|");
            } else if (x == 80 / 2) {
                printf("|");
            } else if (x == 2 && y >= paddle1_y && y < paddle1_y + 3) {
                printf("|");
            } else if (x == 80 - 3 && y >= paddle2_y && y < paddle2_y + 3) {
                printf("|");
            } else if (x == ball_x && y == ball_y) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    for (int x = 0; x < 80; x++) {
        printf("-");
    }
    printf("\n");
    printf("Player 1: %d (A/Z) | Player 2: %d (K/M)\n", score_left, score_right);
}

int reset_ball(int direction) {
    int d = -1;
    if (direction == 1) {
        d = 1;
    }
    return d;
}

int main() {
    int paddle1_y = 12, paddle2_y = 12;
    int ball_x = 40, ball_y = 12;
    int ball_dx = -1, ball_dy = 1;
    int score_left = 0, score_right = 0;
    char move;
    while (!game_over(score_left, score_right)) {
        draw_field(ball_x, ball_y, paddle1_y, paddle2_y, score_left, score_right);
        printf("(A/Z/K/M/Space):");
        scanf("%c", &move);
        paddle1_y = move_paddle1(move, paddle1_y);
        paddle2_y = move_paddle2(move, paddle2_y);
        ball_x = update_ball(ball_x, ball_dx);
        ball_y = update_ball(ball_y, ball_dy);
        ball_dy = bounce_y(ball_y, ball_dy);
        ball_dx = bounce_x(ball_x, ball_y, ball_dx, paddle1_y, paddle2_y);
        int goal = check_goal(ball_x);
        if (goal == 1) {
            score_right++;
            ball_x = 40, ball_y = 12;
            ball_dx = reset_ball(goal);
            ball_dy = reset_ball(goal);
        } else if (goal == 2) {
            score_left++;
            ball_x = 40, ball_y = 12;
            ball_dx = reset_ball(goal);
            ball_dy = reset_ball(goal);
        }
    }
    clear_screen();
    print_winner(score_left, score_right);
    return 0;
}

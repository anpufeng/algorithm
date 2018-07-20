#include <stdio.h>
#include <stdlib.h>

int total = 0;
int n = 8;
int c[16];

/*
 * 将八个皇后摆在一张8*8的国际象棋棋盘上，
 * 使每个皇后都无法吃掉别的皇后，
 * 一共有多少种摆法？
 */
int is_ok(int row) {
    for (int j = 0; j < row; j++) {
        if (c[row] == c[j]
            || row - c[row] == j - c[j]
            || row + c[row] == j + c[j]) {
            return 0;
        }
    }

    return 1;
}

void queen(int row) {
    if (row == n) {
        total++;
    } else {
        for (int col = 0; col != n; col++) {
            c[row] = col;
            if (is_ok(row)) {
                queen(row+1);
            }
        }
    }
}

int main() {
    queen(0);
    printf("n: %d, total = %d\n", n, total);
    return 0;
}
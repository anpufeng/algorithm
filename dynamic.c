#include <stdlib.h>
#include <stdio.h>

/**
 *
 * 给定n种物品和一背包。
 * 物品i的重量是wi，其价值为vi，背包的容量为C。
 * 问应如何选择装入背包的物品，使得装 入背包中物品的总价值最大
 *
 * 有编号分别为a,b,c,d,e的五件物品，
 * 它们的重量分别是2,2,6,5,4，它们的价值分别是6,3,5,4,6，
 * 现在给你个承重为10的背包，如何让背包里装入的物品具有最大的价值总和？
 */

typedef struct goods {
    int weight;
    int value;
} goods;

void choose(goods *g, int number, int capacity) {
    int (*dp)[capacity+1] = (int(*)[capacity+1])malloc((number + 1) * (capacity + 1) * sizeof(int));
    if (dp == NULL) {
        exit(1);
    }

    for (int i = 0; i <= number; i++) {
        dp[i][0] = 0;
    }
    for (int i = 0; i <= capacity; i++) {
        dp[0][i] = 0;
    }

    for (int i = 1; i <= number; i++) {
        for (int j = 1; j <= capacity; j++) {
            if(g[i-1].weight > j) {
                dp[i][j] = dp[i-1][j];
                continue;
            }
            if(dp[i-1][j] < dp[i-1][j-g[i-1].weight] + g[i-1].value)
                dp[i][j] = dp[i-1][j-g[i-1].weight] + g[i-1].value;
            else
                dp[i][j] = dp[i-1][j];
        }
    }

    for (int i = 0; i <= number; i++) {
        for (int j = 0; j <= capacity; j++) {
            printf(" [%2d, %2d]: %d", i, j, dp[i][j]);
        }
        printf("\n");
    }

    printf("========\n");


    int j= capacity;
    for (int i = number; i > 0; i--) {
        if (dp[i][j] > dp[i - 1][j]) {
            printf("index: %d\n", i);
            j = j - g[i - 1].weight;
            if (j < 0) {
                break;
            }
        }
    }

    free(dp);
}

int main() {
    int capacity = 10;
//    goods g[] = {{2, 6}, {2, 3}, {6, 5}, {5, 4}, {4, 6}};
    capacity = 12;
    goods g[] = {{4, 8}, {6, 10}, {2, 6}, {2, 3}, {5, 7}, {1, 2}};
    choose(g, sizeof(g)/ sizeof(goods), capacity);
    return 0;
}



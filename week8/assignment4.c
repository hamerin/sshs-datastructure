#include <limits.h>
#include <stdio.h>

#define MAX_VERTICES 7

int weight[MAX_VERTICES][MAX_VERTICES] = {
    {0, 7, INT_MAX, INT_MAX, 3, 10, INT_MAX},
    {7, 0, 4, 10, 2, 6, INT_MAX},
    {INT_MAX, 4, 0, 2, INT_MAX, INT_MAX, INT_MAX},
    {INT_MAX, 10, 2, 0, 11, 9, 4},
    {3, 2, INT_MAX, 11, 0, INT_MAX, 5},
    {10, 6, INT_MAX, 9, INT_MAX, 0, INT_MAX},
    {INT_MAX, INT_MAX, INT_MAX, 4, 5, INT_MAX, 0}};

void floyd(int V) {
    for (int i = 0; i < V; i++) weight[i][i] = 0;

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (weight[i][k] == INT_MAX || weight[k][j] == INT_MAX) continue;
                if (weight[i][j] > weight[i][k] + weight[k][j]) {
                    weight[i][j] = weight[i][k] + weight[k][j];
                }
            }
        }
    }
}

int main() {
    floyd(MAX_VERTICES);

    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            printf("%d ", weight[i][j]);
        }
        printf("\n");
    }

    return 0;
}
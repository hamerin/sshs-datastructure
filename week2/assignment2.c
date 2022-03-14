#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row;
    int col;
    int value;
} Term;

void smTranspose(Term *const lhs, Term *const rhs, unsigned int length) {
    for (int i = 0; i < length; i++) {
        rhs[i].row = lhs[i].col;
        rhs[i].col = lhs[i].row;
        rhs[i].value = lhs[i].value;
    }
}

int main() {
    Term a[11] = {{8, 7, 10},
                  {0, 2, 2},
                  {0, 6, 12},
                  {1, 4, 7},
                  {2, 0, 23},
                  {3, 3, 31},
                  {4, 1, 14},
                  {4, 5, 25},
                  {5, 6, 6},
                  {6, 0, 52},
                  {7, 4, 11}};
    Term b[11] = {{0, 0, 0}};
    smTranspose(a, b, 11);

    for (int i = 0; i < 11; i++) printf("%d %d %d\n", b[i].row, b[i].col, b[i].value);

    return 0;
}
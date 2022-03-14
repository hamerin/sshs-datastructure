#include <stdio.h>
#include <stdlib.h>

#define MAX_DEGREE 30

typedef struct {
    int degree;
    float coef[MAX_DEGREE + 1];
} Polynomial;

Polynomial addPoly(Polynomial lhs, Polynomial rhs) {
    Polynomial result;
    result.degree = lhs.degree > rhs.degree ? lhs.degree : rhs.degree;
    for (int i = 0; i <= result.degree; i++) result.coef[i] = 0;

    for (int i = 0; i <= lhs.degree; i++)
        result.coef[i + result.degree - lhs.degree] += lhs.coef[i];
    for (int i = 0; i <= rhs.degree; i++)
        result.coef[i + result.degree - rhs.degree] += rhs.coef[i];

    return result;
}

Polynomial mulPoly(Polynomial lhs, Polynomial rhs) {
    Polynomial result;
    result.degree = lhs.degree + rhs.degree;
    for (int i = 0; i <= result.degree; i++) result.coef[i] = 0;
    
    for (int i = 0; i <= lhs.degree; i++)
        for (int j = 0; j <= rhs.degree; j++)
            result.coef[i + j] += (lhs.coef[i] * rhs.coef[j]);

    return result;
}

void printPoly(Polynomial P) {
    for (int i = 0; i <= P.degree; i++)
        printf("%fx^%d\t", P.coef[i], P.degree - i);

    printf("\n");
}

int main() {
    Polynomial A = {3, {4, 3, 5, 0}};
    Polynomial B = {4, {3, 1, 0, 2, 1}};
    Polynomial C, D;
    C = addPoly(A, B);
    D = mulPoly(A, B);

    printf("\nA(x)=");
    printPoly(A);
    printf("\nB(x)=");
    printPoly(B);
    printf("\nC(x)=");
    printPoly(C);
    printf("\nD(x)=");
    printPoly(D);

    return 0;
}
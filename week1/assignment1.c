#include <stdio.h>

int fibo(int n) {
    return n <= 2 ? 1 : fibo(n - 1) + fibo(n - 2);
}

int main() {
    int n;

    scanf("%d", &n);
    printf("%d\n", fibo(n));

    return 0;
}
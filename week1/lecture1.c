#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct {
    int x, y;
    float val;
} st, *pSt;

void gugudan(int dan) {
    for (int i = 1; i < 10; i++)
        printf("%d X %d = %3d\n", dan, i, dan * i);
}

long fact(long n) {
    if (n < 2)
        return 1;
    return n * fact(n - 1);
}

int main() {
    printf("Hello World\n");

    char c = 'A';
    int a = 65;
    float f = 3.14;
    double d = 16180339887;

    printf("c = %d, a = %c, f = %.1f, d = %.3f\n", c, a + 32, f, d);

    printf("c = %c, a = %d, f = %f, d = %e\n", c, ++a, f, d);
    printf("\n");

    char str[80] = "SSHS";
    printf("str = %s\n", str);

    for (int i = 1; i < 10; i++) printf("2 X %d = %3d\n", i, 2 * i);

    for (int i = 2; i < 10; i++) {
        for (int j = 1; j < 10; j++) printf("%d X %d = %3d\n", i, j, i * j);
        printf("\n");
    }

    gugudan(5);
    for (int i = 2; i < 10; i++) {
        gugudan(i);
        printf("\n");
    }

    // printf("출력할 구구단을 입력하세요.\ndan = ");
    // scanf("%s", str);
    // int dan = atoi(str);
    // gugudan(dan);

    for (int i = 0; i < strlen(str); i++)
        printf("%c\t", str[i]);
    printf("\n");

    int A[2][3] = {{1, 2, 3}, {11, 22, 33}};
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            printf("%d\t", A[i][j]);
    printf("\n");

    char *p;
    for (p = str; *p; p++) {
        printf("%c\t", *p);
    }
    printf("\n");

    printf("배열 A의 원소 개수 : %ld, %ld\n", sizeof(A) / sizeof(int), sizeof(int));

    int(*pa)[3] = A;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            printf("%d\t", *(*(pa + i) + j));
    printf("\n");

    int *pa1 = (int *)A;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            printf("%d\t", *pa1++);
    printf("\n");

    pa1 = &A[0][0];
    for (int i = 0; i < 6; i++)
        printf("%d\t", *pa1++);
    printf("\n");

    st.x = 1;
    st.y = 2;
    st.val = 5.5;
    printf("ST(%d, %d, %.2f)\n", st.x, st.y, st.val);

    pSt = &st;
    pSt->x = 2;
    pSt->y = 3;
    pSt->val = 7.5;
    printf("ST(%d, %d, %.2f)\n", st.x, st.y, st.val);
    printf("size 비교 : %ld, %ld\n", sizeof(st), sizeof(pSt));

    long l, n = 25;
    l = fact(n);
    printf("size of long : %ld\n", sizeof(long));
    printf("factorial %ld: %ld\n", n, l);

    return 0;
}
#include <limits.h>
#include <stdio.h>

void selectionSort(int a[], int N) {
    for (int i = 0; i < N; i++) {
        int min = INT_MAX, pos = -1;
        for (int j = i; j < N; j++) {
            if(min > a[j]) {
                min = a[j];
                pos = j;
            }
        }

        int temp = a[i];
        a[i] = a[pos];
        a[pos] = temp;
    }
}

int main() {
    int list[8] = {69, 10, 30, 2, 16, 8, 31, 22};
    selectionSort(list, 8);

    for (int i = 0; i < 8; i++) printf("%d ", list[i]);
    printf("\n");

    return 0;
}

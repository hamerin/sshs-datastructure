#include <stdio.h>

void bubbleSort(int a[], int N) {
    for (int i = N - 1; i >= 0; i--) {
        for (int j = 0; j < i; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int main() {
    int list[8] = {69, 10, 30, 2, 16, 8, 31, 22};
    bubbleSort(list, 8);

    for (int i = 0; i < 8; i++) printf("%d ", list[i]);
    printf("\n");

    return 0;
}

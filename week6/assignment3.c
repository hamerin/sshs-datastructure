#include <stdio.h>

void insertionSort(int a[], int N) {
    for (int i = 1; i < N; i++) {
        int temp = a[i];
        int ins = i;

        while (ins && a[ins - 1] > temp) ins--;
        for (int j = i - 1; j >= ins; j--) a[j + 1] = a[j];
        a[ins] = temp;
    }
}

int main() {
    int list[8] = {69, 10, 30, 2, 16, 8, 31, 22};
    insertionSort(list, 8);

    for (int i = 0; i < 8; i++) printf("%d ", list[i]);
    printf("\n");

    return 0;
}

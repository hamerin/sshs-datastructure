#include <stdio.h>

void intervalSort(int a[], int l, int r, int itv) {
    for (int i = l + itv; i < r; i += itv) {
        int temp = a[i];
        int ins = i;

        while (ins > l && a[ins - itv] > temp) ins -= itv;
        for (int j = i - itv; j >= ins; j--) a[j + itv] = a[j];
        a[ins] = temp;
    }
}

void shellSort(int a[], int N) {
    int itv = N;
    while (itv >= 1) {
        itv >>= 1;
        for (int i = 0; i < itv; i++)
            intervalSort(a, i, N, itv);
    }
}

int main() {
    int list[8] = {69, 10, 30, 2, 16, 8, 31, 22};
    shellSort(list, 8);

    for (int i = 0; i < 8; i++) printf("%d ", list[i]);
    printf("\n");

    return 0;
}

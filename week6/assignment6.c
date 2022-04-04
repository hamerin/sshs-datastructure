#include <stdio.h>
#include <stdlib.h>

void merge(int a[], int l, int p, int r) {
    int *const res = (int *const)malloc(sizeof(int) * (r - l));
    int it1 = l, it2 = p, itr = 0;
    while (it1 < p || it2 < r) {
        while (it1 == p && it2 < r) res[itr++] = a[it2++];
        while (it1 < p && it2 == r) res[itr++] = a[it1++];
        res[itr++] = a[it1] < a[it2] ? a[it1++] : a[it2++];
    }
    for (int i = l; i < r; i++) a[i] = res[i - l];
    free(res);
}

void mergeSort(int a[], int l, int r) {
    if (r - l <= 1) return;

    int m = l + r >> 1;
    mergeSort(a, l, m);
    mergeSort(a, m, r);
    merge(a, l, m, r);
}

int main() {
    int list[8] = {69, 10, 30, 2, 16, 8, 31, 22};
    mergeSort(list, 0, 8);

    for (int i = 0; i < 8; i++) printf("%d ", list[i]);
    printf("\n");

    return 0;
}

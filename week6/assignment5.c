#include <stdio.h>
#include <stdlib.h>

int partition(int a[], int l, int r) {
    int p = l + r >> 1;
    int s = l, e = r - 1;

    while (s < e) {
        while (a[s] <= a[p] && s < e) s++;
        while (a[e] >= a[p] && s < e) e--;
        if (s < e) {
            int temp = a[s];
            a[s] = a[e];
            a[e] = temp;
        }
    }

    if (a[s] > a[p] && p < s) s--;

    int temp = a[p];
    a[p] = a[s];
    a[s] = temp;

    return s;
}

void quickSort(int a[], int l, int r) {
    if (r - l <= 1) return;

    int p = partition(a, l, r);

    quickSort(a, l, p);
    quickSort(a, p + 1, r);
}


int main() {
    int list[8] = {69, 10, 30, 2, 16, 8, 31, 22};
    quickSort(list, 0, 8);

    for (int i = 0; i < 8; i++) printf("%d ", list[i]);
    printf("\n");
    
    return 0;
}

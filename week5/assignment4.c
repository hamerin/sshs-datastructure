#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 100

typedef struct {
    int heap[MAX_ELEMENT + 1];
    int heap_size;
} Heap;

Heap *createHeap() {
    Heap *h = (Heap *)malloc(sizeof(Heap));
    h->heap_size = 0;
    return h;
}

void insertHeap(Heap *h, int item) {
    h->heap[++h->heap_size] = item;

    int cur = h->heap_size;
    int par = cur >> 1;

    while (cur) {
        if (h->heap[cur] <= h->heap[par]) break;

        int tmp = h->heap[cur];
        h->heap[cur] = h->heap[par];
        h->heap[par] = tmp;

        cur = par;
        par = par >> 1;
    }
}

int deleteHeap(Heap *h) {
    if (h->heap_size == 0) {
        printf("Heap is Empty!!");
        exit(1);
    }

    int ret = h->heap[1];
    h->heap[1] = h->heap[h->heap_size--];

    int cur = 1;
    while ((cur << 1) <= h->heap_size) {
        int li = (cur << 1), ri = (cur << 1) + 1;
        int left = li <= h->heap_size ? h->heap[li] : INT_MIN;
        int right = ri <= h->heap_size ? h->heap[ri] : INT_MIN;

        if (left >= right) {
            if (h->heap[cur] >= left) break;
            h->heap[li] = h->heap[cur];
            h->heap[cur] = left;
            cur = li;
        } else {
            if (h->heap[cur] >= right) break;
            h->heap[ri] = h->heap[cur];
            h->heap[cur] = right;
            cur = ri;
        }
    }

    return ret;
}

void printHeap(Heap *h) {
    printf("Heap : ");
    for (int i = 1; i <= h->heap_size; i++)
        printf("[%d] ", h->heap[i]);
}

int main() {
    Heap *heap = createHeap();
    insertHeap(heap, 10);
    insertHeap(heap, 45);
    insertHeap(heap, 19);
    insertHeap(heap, 11);
    insertHeap(heap, 96);

    printHeap(heap);

    int N = heap->heap_size;
    while (N--) {
        int item = deleteHeap(heap);
        printf("\n delete : [%d] ", item);
    }

    return 0;
}
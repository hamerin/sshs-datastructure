#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 7
typedef struct {
    int u, v, w;
} Edge;

typedef struct Heap {
    Edge *heap;
    int size;

    int (*compare)(const Edge *, const Edge *);
    void (*insert)(struct Heap *, const Edge);
    Edge (*delete)(struct Heap *);
} Heap;

void _internal_Heap_insert(Heap *this, const Edge item) {
    this->heap[++this->size] = item;

    int cur = this->size;
    int par = cur >> 1;

    while (cur) {
        if (this->compare(&this->heap[cur], &this->heap[par]) >= 0) break;

        Edge tmp = this->heap[cur];
        this->heap[cur] = this->heap[par];
        this->heap[par] = tmp;

        cur = par;
        par = par >> 1;
    }
}

Edge _internal_Heap_delete(Heap *this) {
    assert(this->size > 0);

    Edge ret = this->heap[1];
    this->heap[1] = this->heap[this->size--];

    int cur = 1;
    while ((cur << 1) <= this->size) {
        int li = (cur << 1), ri = (cur << 1) + 1;
        Edge *left = li <= this->size ? &this->heap[li] : NULL;
        Edge *right = ri <= this->size ? &this->heap[ri] : NULL;

        Edge tmp = this->heap[cur];
        if (this->compare(left, right) <= 0) {
            if (this->compare(&this->heap[cur], left) <= 0) break;

            this->heap[cur] = *left;
            *left = tmp;
            cur = li;
        } else {
            if (this->compare(&this->heap[cur], right) <= 0) break;

            this->heap[cur] = *right;
            *right = tmp;
            cur = ri;
        }
    }

    return ret;
}

void initHeap(Heap *heap, int maxsize, int (*comparator)(const Edge *, const Edge *)) {
    heap->size = 0;
    heap->heap = (Edge *)malloc(sizeof(Edge) * maxsize);
    heap->compare = comparator;
    heap->insert = _internal_Heap_insert;
    heap->delete = _internal_Heap_delete;
}

int lessWeightEdgeComparator(const Edge *lhs, const Edge *rhs) {
    if (lhs == NULL && rhs == NULL) return 0;
    if (lhs == NULL) return 1;
    if (rhs == NULL) return -1;
    if (lhs->w == rhs->w) return 0;
    if (lhs->w < rhs->w) return -1;
    return 1;
}

Edge createEdge(int u, int v, int w) {
    Edge e;
    e.u = u, e.v = v, e.w = w;
    return e;
}

int weight[MAX_VERTICES][MAX_VERTICES] = {
    {0, 3, 17, 6, INT_MAX, INT_MAX, INT_MAX},
    {3, 0, INT_MAX, 5, INT_MAX, INT_MAX, 12},
    {17, INT_MAX, 0, INT_MAX, 10, 8, INT_MAX},
    {6, 5, INT_MAX, 0, 9, INT_MAX, INT_MAX},
    {INT_MAX, INT_MAX, 10, 9, 0, 4, 2},
    {INT_MAX, INT_MAX, 8, INT_MAX, 4, 0, 14},
    {INT_MAX, 12, INT_MAX, INT_MAX, 2, 14, 0}};

void prim(int s, int V) {
    bool *vst = (bool *)malloc(sizeof(bool) * V);
    vst[s] = true;

    Heap *heap = (Heap *)malloc(sizeof(Heap));
    initHeap(heap, V * V, lessWeightEdgeComparator);

    int loop = V - 1, h = s;
    while (loop--) {
        for (int t = 0; t < V; t++) {
            if (weight[h][t] == INT_MAX) continue;
            heap->insert(heap, createEdge(h, t, weight[h][t]));
        }

        while (heap->size) {
            Edge e = heap->delete (heap);

            assert(vst[e.u]);

            if (!vst[e.v]) {
                printf("%d %d %d\n", e.u, e.v ,e.w);
                vst[e.v] = true;
                h = e.v;
                break;
            }
        }
    }
    
    free(vst);
    free(heap);
}

int main() {
    prim(0, 7);

    return 0;
}
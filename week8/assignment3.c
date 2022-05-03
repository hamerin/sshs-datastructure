#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 7

typedef struct {
    int u, v;
} Pair;

typedef struct Heap {
    Pair *heap;
    int size;

    int (*compare)(const Pair *, const Pair *);
    void (*insert)(struct Heap *, const Pair);
    Pair (*delete)(struct Heap *);
} Heap;

void _internal_Heap_insert(Heap *this, const Pair item) {
    this->heap[++this->size] = item;

    int cur = this->size;
    int par = cur >> 1;

    while (cur) {
        if (this->compare(&this->heap[cur], &this->heap[par]) >= 0) break;

        Pair tmp = this->heap[cur];
        this->heap[cur] = this->heap[par];
        this->heap[par] = tmp;

        cur = par;
        par = par >> 1;
    }
}

Pair _internal_Heap_delete(Heap *this) {
    assert(this->size > 0);

    Pair ret = this->heap[1];
    this->heap[1] = this->heap[this->size--];

    int cur = 1;
    while ((cur << 1) <= this->size) {
        int li = (cur << 1), ri = (cur << 1) + 1;
        Pair *left = li <= this->size ? &this->heap[li] : NULL;
        Pair *right = ri <= this->size ? &this->heap[ri] : NULL;

        Pair tmp = this->heap[cur];
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

void initHeap(Heap *heap, int maxsize, int (*comparator)(const Pair *, const Pair *)) {
    heap->size = 0;
    heap->heap = (Pair *)malloc(sizeof(Pair) * maxsize);
    heap->compare = comparator;
    heap->insert = _internal_Heap_insert;
    heap->delete = _internal_Heap_delete;
}

int lexicographicLessComparator(const Pair *lhs, const Pair *rhs) {
    if (lhs == NULL && rhs == NULL) return 0;
    if (lhs == NULL) return 1;
    if (rhs == NULL) return -1;

    if (lhs->u == rhs->u) {
        if (lhs->v == rhs->v) return 0;
        if (lhs->v < rhs->v) return -1;
        return 1;
    }

    if (lhs->u < rhs->u) return -1;
    return 1;
}

Pair createPair(int u, int v) {
    Pair e;
    e.u = u, e.v = v;
    return e;
}

int weight[MAX_VERTICES][MAX_VERTICES] = {
    {0, 7, INT_MAX, INT_MAX, 3, 10, INT_MAX},
    {7, 0, 4, 10, 2, 6, INT_MAX},
    {INT_MAX, 4, 0, 2, INT_MAX, INT_MAX, INT_MAX},
    {INT_MAX, 10, 2, 0, 11, 9, 4},
    {3, 2, INT_MAX, 11, 0, INT_MAX, 5},
    {10, 6, INT_MAX, 9, INT_MAX, 0, INT_MAX},
    {INT_MAX, INT_MAX, INT_MAX, 4, 5, INT_MAX, 0}};

int *dijkstra(int s, int V) {
    int *dist = (int *)malloc(sizeof(int) * V);
    memset(dist, 0x7f, sizeof(int) * V);

    dist[s] = 0;

    Heap *edges = (Heap *)malloc(sizeof(Heap));
    initHeap(edges, V * V, lexicographicLessComparator);
    edges->insert(edges, createPair(0, s));

    while (edges->size) {
        Pair p = edges->delete (edges);
        int W = p.u, h = p.v;

        if (dist[h] < W) continue;

        for (int t = 0; t < V; t++) {
            if (weight[h][t] == INT_MAX) continue;

            int w = weight[h][t];
            if (dist[t] > W + w) {
                dist[t] = W + w;
                edges->insert(edges, createPair(W + w, t));
            }
        }
    }

    return dist;
}

int main() {
    int *dist = dijkstra(0, MAX_VERTICES);

    for (int i = 0; i < MAX_VERTICES; i++) printf("%d ", i);
    printf("\n");

    return 0;
}
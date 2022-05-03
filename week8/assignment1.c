#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
            if(this->compare(&this->heap[cur], left) <= 0) break;
            
            this->heap[cur] = *left;
            *left = tmp;
            cur = li;
        } else {
            if(this->compare(&this->heap[cur], right) <= 0) break;
            
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

typedef struct DisjointSet {
    int *par;

    int (*find)(struct DisjointSet *, int);
    void (*merge)(struct DisjointSet *, int, int);
    bool (*isSameSet)(struct DisjointSet *, int, int);
} DisjointSet;

int _internal_DisjointSet_find(DisjointSet *this, int u) {
    return this->par[u] = this->par[u] == u ? u : this->find(this, this->par[u]);
}

void _internal_DisjointSet_merge(DisjointSet *this, int u, int v) {
    this->par[this->find(this, u)] = this->find(this, v);
}

bool _internal_DisjointSet_isSameSet(DisjointSet *this, int u, int v) {
    return this->find(this, u) == this->find(this, v);
}

void initDisjointSet(DisjointSet *dS, int size) {
    dS->par = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) dS->par[i] = i;

    dS->find = _internal_DisjointSet_find;
    dS->merge = _internal_DisjointSet_merge;
    dS->isSameSet = _internal_DisjointSet_isSameSet;
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

void kruskal(Heap *edges, int V) {
    DisjointSet *dS = (DisjointSet *)malloc(sizeof(DisjointSet));
    initDisjointSet(dS, V);

    while (edges->size) {
        Edge e = edges->delete (edges);

        if (!dS->isSameSet(dS, e.u, e.v)) {
            dS->merge(dS, e.u, e.v);
            printf("%d %d %d\n", e.u, e.v, e.w);
        }
    }

    free(dS);
}

int main() {
    Heap *edges = (Heap *)malloc(sizeof(Heap));
    initHeap(edges, 100, lessWeightEdgeComparator);

    edges->insert(edges, createEdge(0, 1, 3));
    edges->insert(edges, createEdge(0, 2, 17));
    edges->insert(edges, createEdge(0, 3, 6));
    edges->insert(edges, createEdge(1, 3, 5));
    edges->insert(edges, createEdge(1, 6, 12));
    edges->insert(edges, createEdge(2, 4, 10));
    edges->insert(edges, createEdge(2, 5, 8));
    edges->insert(edges, createEdge(3, 4, 9));
    edges->insert(edges, createEdge(4, 5, 4));
    edges->insert(edges, createEdge(4, 6, 2));
    edges->insert(edges, createEdge(5, 6, 14));

    kruskal(edges, 7);

    return 0;
}
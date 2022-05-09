#include <stdio.h>
#include <stdlib.h>

inline int max(int u, int v) {
    return u > v ? u : v;
}

typedef struct AvlNode {
    int v, h;
    struct AvlNode *l, *r;

    void (*updateHeight)(struct AvlNode *);
    int (*getBalanceFactor)(struct AvlNode *);

    struct AvlNode *(*leftRotate)(struct AvlNode *);
    struct AvlNode *(*rightRotate)(struct AvlNode *);
    struct AvlNode *(*rebalance)(struct AvlNode *);

    struct AvlNode *(*emplace)(struct AvlNode *, struct AvlNode *);
    struct AvlNode *(*find)(struct AvlNode *, int v);
} AvlNode;

void _internal_AvlNode_updateHeight(AvlNode *p) {
    if (p == NULL) return;

    p->h = 1 + max(p->l ? p->l->h : 0, p->r ? p->r->h : 0);
}

int _internal_AvlNode_getBalanceFactor(AvlNode *p) {
    return p && p->l && p->r ? p->l->h - p->r->h : 0;
}

AvlNode *_internal_AvlNode_leftRotate(AvlNode *p) {
    AvlNode *r = p->r;
    AvlNode *c = r->l;

    r->l = p;
    p->r = c;

    p->updateHeight(p);
    r->updateHeight(r);

    return r;
}

AvlNode *_internal_AvlNode_rightRotate(AvlNode *p) {
    AvlNode *r = p->l;
    AvlNode *c = r->r;

    r->r = p;
    p->l = c;

    p->updateHeight(p);
    r->updateHeight(r);

    return r;
}

AvlNode *_internal_AvlNode_rebalance(AvlNode *p) {
    int BF = p->getBalanceFactor(p);

    if (BF > 1) {
        if (p->l->getBalanceFactor(p->l) < 0) p->l = p->l->leftRotate(p->l);
        return p->rightRotate(p);
    }

    if (BF < -1) {
        if (p->r->getBalanceFactor(p->r) > 0) p->r = p->r->rightRotate(p->r);
        return p->leftRotate(p);
    }

    return p;
}

AvlNode *_internal_AvlNode_emplace(AvlNode *h, AvlNode *n) {
    if (h == NULL) return n;
    if (n->v == h->v) return h;

    if (n->v > h->v)
        h->r = _internal_AvlNode_emplace(h->r, n);
    else
        h->l = _internal_AvlNode_emplace(h->l, n);

    h->updateHeight(h);
    return h->rebalance(h);
}

AvlNode *_internal_AvlNode_find(AvlNode *h, int v) {
    if (h == NULL) return NULL;
    printf("%d ", h->v);

    if (v == h->v) return h;
    if (v < h->v) return _internal_AvlNode_find(h->l, v);
    return _internal_AvlNode_find(h->r, v);
}

AvlNode *createAvlNode(int v) {
    AvlNode *ret = (AvlNode *)malloc(sizeof(AvlNode));

    ret->v = v;
    ret->h = 1;
    ret->l = ret->r = NULL;

    ret->updateHeight = _internal_AvlNode_updateHeight;
    ret->getBalanceFactor = _internal_AvlNode_getBalanceFactor;

    ret->leftRotate = _internal_AvlNode_leftRotate;
    ret->rightRotate = _internal_AvlNode_rightRotate;
    ret->rebalance = _internal_AvlNode_rebalance;

    ret->emplace = _internal_AvlNode_emplace;
    ret->find = _internal_AvlNode_find;

    return ret;
}

int main() {
    AvlNode *r = NULL;

    int arr[9] = {7, 8, 9, 2, 1, 5, 3, 6, 4};
    for (int i = 0; i < 9; i++) r = r ? r->emplace(r, createAvlNode(arr[i])) : createAvlNode(arr[i]);

    r->find(r, 4);

    return 0;
}

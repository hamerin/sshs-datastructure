#include <stdio.h>
#include <stdlib.h>

typedef int Element;

typedef struct Node {
    Element data;
    struct Node *next, *prev;
} Node;

Node *createNode(Element data) {
    Node *ptr;
    ptr = (Node *)malloc(sizeof(Node));

    ptr->data = data;
    ptr->next = NULL;
    ptr->prev = NULL;

    return ptr;
}

typedef struct CircularDoublyLinkedList {
    Node *tail;

    void (*insert)(struct CircularDoublyLinkedList *this, Node *iter, Node *new);
    Node *(*remove)(struct CircularDoublyLinkedList *this, Node *iter);
} CircularDoublyLinkedList;

void _internal_CircularDoublyLinkedList_insert(CircularDoublyLinkedList *this, Node *iter, Node *new) {
    if (this->tail == NULL) {
        new->next = new;
        new->prev = new;
        this->tail = new;
    } else {
        new->next = iter->next;
        new->prev = iter;
        iter->next->prev = new;
        iter->next = new;

        if (this->tail == iter) this->tail = new;
    }
}

Node *_internal_CircularDoublyLinkedList_remove(CircularDoublyLinkedList *this, Node *iter) {
    if (iter->next == iter && iter->prev == iter) {
        this->tail = NULL;
        free(iter);
        return NULL;
    }

    iter->prev->next = iter->next;
    iter->next->prev = iter->prev;

    if (iter == this->tail) {
        this->tail = iter->prev;
    }

    Node *ret = iter->next;
    free(iter);
    return ret;
}

void initCircularDoublyLinkedList(CircularDoublyLinkedList *L) {
    L->tail = NULL;
    L->insert = _internal_CircularDoublyLinkedList_insert;
    L->remove = _internal_CircularDoublyLinkedList_remove;
}

void advance(Node **piter, int step) {
    while (step < 0) *piter = (*piter)->prev, ++step;
    while (step > 0) *piter = (*piter)->next, --step;
}

void josephus(int n, int m) {
    CircularDoublyLinkedList L;
    initCircularDoublyLinkedList(&L);
    for (int i = 1; i <= n; i++) L.insert(&L, L.tail, createNode(i));

    Node *iter = L.tail->next;
    int *const sequence = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        advance(&iter, m - 1);
        sequence[i] = iter->data;
        iter = L.remove(&L, iter);
    }

    for (int i = 0; i < n - 1; i++) printf("%d => ", sequence[i]);
    printf("%d\n", sequence[n - 1]);
}

int main() {
    josephus(41, 3);

    return 0;
}
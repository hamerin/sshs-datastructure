#include <stdio.h>
#include <stdlib.h>

typedef int Element;

typedef struct Node {
    Element data;
    struct Node *link;
} Node;

Node *createNode(Element data, Node *link) {
    Node *ptr;
    ptr = (Node *)malloc(sizeof(Node));

    ptr->data = data;
    ptr->link = link;

    return ptr;
}

typedef struct LinkedList {
    Node *head;

    void (*display)(struct LinkedList *this);
    void (*insert)(struct LinkedList *this, Node *pre, Node *new);
    void (*remove)(struct LinkedList *this, Node *pre);
    Node *(*search)(struct LinkedList *this, Element x);
    void (*concat)(struct LinkedList *this, struct LinkedList *rhs);
    void (*reverse)(struct LinkedList *this);
} LinkedList;

void _internal_LinkedList_display(LinkedList *this) {
    Node *cur = this->head;

    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->link;
    }
    printf("\n");
}

void _internal_LinkedList_insert(LinkedList *this, Node *pre, Node *new) {
    if (pre == NULL) {
        if (this->head == NULL) {
            this->head = new;
        } else {
            new->link = this->head;
            this->head = new;
        }
    } else {
        new->link = pre->link;
        pre->link = new;
    }
}

void _internal_LinkedList_remove(LinkedList *this, Node *pre) {
    Node *tar = pre == NULL ? this->head : pre->link;

    if (tar == NULL) return;

    if (tar == this->head) {
        this->head = tar->link;
    } else {
        pre->link = tar->link;
    }

    free(tar);
}

Node *_internal_LinkedList_search(LinkedList *this, Element x) {
    Node *cur = this->head;

    while (cur != NULL) {
        if (cur->data == x) {
            return cur;
        }
        cur = cur->link;
    }

    return NULL;
}

void _internal_LinkedList_concat(LinkedList *this, LinkedList *rhs) {
    if (this->head == NULL) {
        this->head = rhs->head;
    } else {
        Node *tail = this->head;
        while (tail->link != NULL) tail = tail->link;
        tail->link = rhs->head;
    }

    rhs->head = NULL;
}

void _internal_LinkedList_reverse(LinkedList *this) {
    Node *pre = NULL, *cur = this->head;

    while (cur != NULL) {
        Node *next = cur->link;

        cur->link = pre;
        if (next == NULL) this->head = cur;

        pre = cur;
        cur = next;
    }
}

void initLinkedList(LinkedList *L) {
    L->head = NULL;
    L->display = _internal_LinkedList_display;
    L->insert = _internal_LinkedList_insert;
    L->remove = _internal_LinkedList_remove;
    L->search = _internal_LinkedList_search;
    L->concat = _internal_LinkedList_concat;
    L->reverse = _internal_LinkedList_reverse;
}

void printSearchResult(Node *res) {
    if (res == NULL) {
        printf("탐색 실패\n");
    } else {
        printf("탐색 성공: %d, 주소값: %lld\n", res->data, (long long)res->link);
    }
}

int main() {
    LinkedList L1, L2;
    initLinkedList(&L1);
    initLinkedList(&L2);

    printf("\n[삽입]\n");
    L1.insert(&L1, NULL, createNode(10, NULL));
    L1.insert(&L1, NULL, createNode(20, NULL));
    L1.insert(&L1, NULL, createNode(30, NULL));
    printf("L1: ");
    L1.display(&L1);

    printf("\n[삭제]\n");
    L1.remove(&L1, NULL);
    printf("L1: ");
    L1.display(&L1);

    printf("\n[탐색]\n");
    printSearchResult(L1.search(&L1, 20));
    printSearchResult(L1.search(&L1, 90));

    printf("\n[삽입]\n");
    L2.insert(&L2, NULL, createNode(60, NULL));
    L2.insert(&L2, NULL, createNode(70, NULL));
    L2.insert(&L2, NULL, createNode(80, NULL));
    printf("L2: ");
    L2.display(&L2);

    printf("\n[concat]\n");
    L1.concat(&L1, &L2);
    printf("L1: ");
    L1.display(&L1);

    printf("\n[reverse]\n");
    L1.reverse(&L1);
    printf("L1: ");
    L1.display(&L1);

    return 0;
}
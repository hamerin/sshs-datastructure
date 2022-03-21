#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define Q_SIZE 3

typedef char Element;
typedef struct QNode {
    Element data;
    struct QNode *link;
} QNode;

typedef struct {
    QNode *front, *rear;
} LQueue;

LQueue *createLinkedQueue() {
    return (LQueue *)malloc(sizeof(LQueue));
}

bool isEmpty(LQueue *LQ) {
    return LQ->front == NULL && LQ->rear == NULL;
}

void enQueue(LQueue *LQ, Element item) {
    if (isEmpty(LQ)) {
        LQ->rear = (QNode *)malloc(sizeof(QNode));
        LQ->rear->data = item;
        LQ->front = LQ->rear;
    } else {
        LQ->rear->link = (QNode *)malloc(sizeof(QNode));
        LQ->rear = LQ->rear->link;
        LQ->rear->data = item;
    }
}

Element deQueue(LQueue *LQ) {
    if (isEmpty(LQ)) {
        printf("Linked Queue is Empty!!");
        exit(1);
    }

    QNode *del = LQ->front;
    int ret = del->data;

    if (del == LQ->rear) {
        LQ->front = NULL;
        LQ->rear = NULL;
    } else {
        LQ->front = del->link;
    }

    free(del);

    return ret;
}

Element peek(LQueue *LQ) {
    if (isEmpty(LQ)) {
        printf("Linked Queue is Empty!!");
        exit(1);
    }

    return LQ->front->data;
}

void printQ(LQueue *LQ) {
    printf("Linked Queue : [ ");
    for (QNode *ptr = LQ->front; ptr != NULL; ptr = ptr->link) printf("%c ", ptr->data);
    printf("]\n");
}

int main() {
    LQueue *LQ = createLinkedQueue();
    Element data;

    enQueue(LQ, 'A'), printQ(LQ);
    enQueue(LQ, 'B'), printQ(LQ);
    deQueue(LQ), printQ(LQ);
    data = peek(LQ), printf(" peek item : %c \n", data);
    deQueue(LQ), printQ(LQ);
    deQueue(LQ), printQ(LQ);

    return 0;
}
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define Q_SIZE 3

typedef char Element;
typedef struct {
    Element queue[Q_SIZE];
    int front, rear;
} Queue;

Queue *createQueue() {
    return (Queue *)malloc(sizeof(Queue));
}

inline int advance(int p) {
    return (p + 1) % Q_SIZE;
}

bool isEmpty(Queue *Q) {
    return Q->front == Q->rear;
}

bool isFull(Queue *Q) {
    return advance(Q->rear) == Q->front;
}

void enQueue(Queue *Q, Element item) {
    if (isFull(Q)) {
        printf("Circular Queue is Full!!");
        exit(1);
    }

    Q->queue[Q->rear] = item;
    Q->rear = advance(Q->rear);
}

Element deQueue(Queue *Q) {
    if (isEmpty(Q)) {
        printf("Circular Queue is Empty!!");
        exit(1);
    }

    int ret = Q->queue[Q->front];
    Q->front = advance(Q->front);
    return ret;
}

Element peek(Queue *Q) {
    return Q->queue[Q->front];
}

void printQ(Queue *Q) {
    printf("Circular Queue : [ ");
    for (int i = Q->front; i != Q->rear; i = advance(i)) printf("%c ", Q->queue[i]);
    printf("]\n");
}

int main() {
    Queue *Q = createQueue();
    Element data;

    enQueue(Q, 'A'), printQ(Q);
    enQueue(Q, 'B'), printQ(Q);
    deQueue(Q), printQ(Q);
    enQueue(Q, 'C'), printQ(Q);
    data = peek(Q), printf(" peek item : %c \n", data);
    deQueue(Q), printQ(Q);
    deQueue(Q), printQ(Q);

    return 0;
}
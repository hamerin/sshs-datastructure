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

bool isEmpty(Queue *Q) {
    return Q->front == Q->rear;
}

bool isFull(Queue *Q) {
    return Q->rear == Q_SIZE;
}

void enQueue(Queue *Q, Element item) {
    if (isFull(Q)) {
        printf("Queue is Full!!");
        exit(1);
    }

    Q->queue[Q->rear++] = item;
}

Element deQueue(Queue *Q) {
    if (isEmpty(Q)) {
        printf("Queue is Empty!!");
        exit(1);
    }

    return Q->queue[Q->front++];
}

Element peek(Queue *Q) {
    return Q->queue[Q->front];
}

void printQ(Queue *Q) {
    printf("Queue : [ ");
    for (int i = Q->front; i < Q->rear; i++) printf("%c ", Q->queue[i]);
    printf("]\n");
}

int main() {
    Queue *Q = createQueue();
    Element data;

    printf("삽입 A >> "), enQueue(Q, 'A'), printQ(Q);
    printf("삽입 B >> "), enQueue(Q, 'B'), printQ(Q);
    printf("삭제 >> "), deQueue(Q), printQ(Q);
    printf("삽입 C >> "), enQueue(Q, 'C'), printQ(Q);
    data = peek(Q), printf(" peek item : %c \n", data);
    printf("삭제 >> "), deQueue(Q), printQ(Q);
    printf("삭제 >> "), deQueue(Q), printQ(Q);

    return 0;
}
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *link;
} Node;

typedef struct Queue {
    Node *front, *rear;

    bool (*empty)(struct Queue *this);
    void (*emplace)(struct Queue *this, int item);
    int (*pop)(struct Queue *this);
} Queue;

bool _internal_Queue_empty(Queue *this) {
    return this->front == NULL && this->rear == NULL;
}

void _internal_Queue_emplace(Queue *this, int item) {
    if (this->empty(this)) {
        this->rear = (Node *)malloc(sizeof(Node));
        this->rear->data = item;
        this->front = this->rear;
    } else {
        this->rear->link = (Node *)malloc(sizeof(Node));
        this->rear = this->rear->link;
        this->rear->data = item;
    }
}

int _internal_Queue_pop(Queue *this) {
    if (this->empty(this)) exit(1);

    Node *del = this->front;
    int ret = del->data;

    if (del == this->rear) {
        this->front = NULL;
        this->rear = NULL;
    } else {
        this->front = del->link;
    }

    free(del);

    return ret;
}

void initQueue(Queue *Q) {
    Q->front = NULL;
    Q->rear = NULL;
    Q->empty = _internal_Queue_empty;
    Q->emplace = _internal_Queue_emplace;
    Q->pop = _internal_Queue_pop;
}

void radixSort(int a[], int N, unsigned int radix) {
    int max = INT_MIN;
    for (int i = 0; i < N; i++)
        if (max < a[i]) max = a[i];

    int digits = 0;
    {
        int temp = 1;
        while (max >= temp) {
            temp *= radix;
            digits++;
        }
    }

    int *const powers = (int *const)malloc(sizeof(int) * digits);
    powers[0] = 1;
    for (int i = 1; i < digits; i++) powers[i] = powers[i - 1] * radix;

    for (int exp = 0; exp < digits; exp++) {
        int power = powers[exp];
        Queue *const queues = (Queue *const)malloc(sizeof(Queue) * radix);
        for (int i = 0; i < radix; i++) initQueue(&queues[i]);
        
        for (int i = 0; i < N; i++) {
            Queue *target = &queues[(a[i] / power) % radix];
            target->emplace(target, a[i]);
        }

        int it = 0;
        for (int i = 0; i < radix; i++) {
            Queue *target = &queues[i];
            while (!target->empty(target)) a[it++] = target->pop(target);
        }

        free(queues);
    }

    free(powers);
}

int main() {
    int list[8] = {69, 10, 30, 2, 16, 8, 31, 22};
    radixSort(list, 8, 10);

    for (int i = 0; i < 8; i++) printf("%d ", list[i]);
    printf("\n");

    return 0;
}

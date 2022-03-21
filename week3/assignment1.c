#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define STACK_SIZE 3

typedef int Element;

Element stack[STACK_SIZE];
int top = -1;

bool isEmpty() {
    return top == -1;
}

bool isFull() {
    return top == STACK_SIZE - 1;
}

void printStack() {
    printf("STACK [ ");
    for (int i = 0; i <= top; i++) printf("%d ", stack[i]);
    printf("]\n");
}

void push(Element data) {
    if (isFull()) {
        printf("Stack is Full!!");
        exit(1);
    }

    stack[++top] = data;
}

Element pop() {
    if (isEmpty()) {
        printf("Stack is Empty!!");
        exit(1);
    }

    return stack[top--];
}

int main() {
    int item;
    printStack();
    push(1), printStack();
    push(2), printStack();
    push(3), printStack();

    item = pop();
    printf("   pop top=>%d\n", item), printStack();

    item = pop();
    printf("   pop top=>%d\n", item), printStack();

    item = pop();
    printf("   pop top=>%d\n", item), printStack();

    pop();

    return 0;
}
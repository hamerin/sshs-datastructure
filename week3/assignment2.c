#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int Element;

typedef struct StackNode {
    Element data;
    struct StackNode *link;
} StackNode;

StackNode *top;

bool isEmpty() {
    return top == NULL;
}

void __traverse(StackNode *cur) {
    if (cur == NULL) return;
    __traverse(cur->link);
    printf("%d ", cur->data);
}

void printStack() {
    printf("STACK [ ");
    __traverse(top);
    printf("]\n");
}

void push(Element data) {
    StackNode *apd = (StackNode *)malloc(sizeof(StackNode));
    apd->data = data;
    apd->link = top;
    top = apd;
}

Element pop() {
    if (isEmpty()) {
        printf("Stack is Empty!!");
        exit(1);
    }

    StackNode *del = top;
    Element popped = del->data;

    top = del->link;
    free(del);

    return popped;
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
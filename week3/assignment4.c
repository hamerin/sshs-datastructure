#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

Element evalPostfix(char *exp) {
    int len = strlen(exp);

    for (int i = 0; i < len; i++) {
        if ('0' <= exp[i] && exp[i] <= '9') push(exp[i] - '0');
        else {
            Element rhs = pop();
            Element lhs = pop();
            
            if(exp[i] == '+') push(lhs + rhs);
            if(exp[i] == '-') push(lhs - rhs);
            if(exp[i] == '*') push(lhs * rhs);
            if(exp[i] == '/') push(lhs / rhs);
        }
    }

    return top->data;
}

int main() {
    int result;
    char *expression = "35*62/-";
    printf("후위표기식 : %s", expression);

    result = evalPostfix(expression);
    printf("\n\n 연산결과 => %d \n", result);

    return 0;
}
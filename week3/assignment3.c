#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char Element;

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

bool testPair(char *exp) {
    int len = strlen(exp);

    for (int i = 0; i < len; i++) {
        if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[') push(exp[i]);
        if (exp[i] == ')' || exp[i] == '}' || exp[i] == ']') {
            if (isEmpty()) return false;

            char popped = pop();
            if ((exp[i] == ')' && popped != '(') || (exp[i] == '}' && popped != '{') || (exp[i] == ']' && popped != '['))
                return false;
        }
    }

    return isEmpty();
}

int main() {
    char *expression = "{(A+B)-3}*5+[{cos(x+y)+7}-1]*4";
    printf("%s", expression);
    if (testPair(expression))
        printf("\n\n 수식의 괄호가 맞게 사용되었습니다!\n");
    else
        printf("\n\n 수식의 괄호가 틀렸습니다!\n");

    return 0;
}
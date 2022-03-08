#include <stdio.h>

void hanoi(int n, char from, char to, char via) {
    if (n > 1) hanoi(n - 1, from, via, to);
    printf("%c -> %c\n", from, to);
    if (n > 1) hanoi(n - 1, via, to, from);
}

int main() {
    hanoi(3, 'A', 'C', 'B');
    
    return 0;
}
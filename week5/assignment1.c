#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    char data;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* makeRootNode(char data, TreeNode* left, TreeNode* right) {
    TreeNode* ptr = (TreeNode*)malloc(sizeof(TreeNode));
    ptr->data = data, ptr->left = left, ptr->right = right;
    return ptr;
}

void preorder(TreeNode* here) {
    if (here == NULL) return;
    printf("%c", here->data);
    preorder(here->left);
    preorder(here->right);
}

void inorder(TreeNode* here) {
    if (here == NULL) return;
    inorder(here->left);
    printf("%c", here->data);
    inorder(here->right);
}

void postorder(TreeNode* here) {
    if (here == NULL) return;
    postorder(here->left);
    postorder(here->right);
    printf("%c", here->data);
}

int main() {
    TreeNode* n7 = makeRootNode('D', NULL, NULL);
    TreeNode* n6 = makeRootNode('C', NULL, NULL);
    TreeNode* n5 = makeRootNode('B', NULL, NULL);
    TreeNode* n4 = makeRootNode('A', NULL, NULL);
    TreeNode* n3 = makeRootNode('/', n6, n7);
    TreeNode* n2 = makeRootNode('*', n4, n5);
    TreeNode* n1 = makeRootNode('-', n2, n3);

    printf(" \n preorder : ");
    preorder(n1);

    printf(" \n inorder : ");
    inorder(n1);

    printf(" \n postorder : ");
    postorder(n1);

    printf("\n");

    return 0;
}
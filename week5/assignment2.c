#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    int size;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* makeRootNode(int size, TreeNode* left, TreeNode* right) {
    TreeNode* ptr = (TreeNode*)malloc(sizeof(TreeNode));
    ptr->size = size, ptr->left = left, ptr->right = right;
    return ptr;
}

int folderSizeCalc(TreeNode* here) {
    return here == NULL ? 0 : folderSizeCalc(here->left) + folderSizeCalc(here->right) + here->size;
}

int main() {
    TreeNode* F11 = makeRootNode(120, NULL, NULL);
    TreeNode* F10 = makeRootNode(55, NULL, NULL);
    TreeNode* F9 = makeRootNode(100, NULL, NULL);
    TreeNode* F8 = makeRootNode(200, NULL, NULL);
    TreeNode* F7 = makeRootNode(68, F10, F11);
    TreeNode* F6 = makeRootNode(40, NULL, NULL);
    TreeNode* F5 = makeRootNode(15, NULL, NULL);
    TreeNode* F4 = makeRootNode(2, F8, F9);
    TreeNode* F3 = makeRootNode(10, F6, F7);
    TreeNode* F2 = makeRootNode(0, F4, F5);
    TreeNode* F1 = makeRootNode(0, F2, F3);

    printf(" \n C:\\의 용량 : %d M \n", folderSizeCalc(F2));
    printf(" \n D:\\의 용량 : %d M \n", folderSizeCalc(F3));
    printf(" \n 내 컴퓨터의 전체 용량 : %d M \n", folderSizeCalc(F1));

    return 0;
}
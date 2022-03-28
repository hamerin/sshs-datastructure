// 비재귀적 구현

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    char key;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode *insertNode(TreeNode *root, char x) {
    TreeNode *here = root, *par = NULL;

    while (here != NULL && here->key != x) {
        par = here;
        here = x < here->key ? here->left : here->right;
    }

    if (here != NULL) return NULL;

    TreeNode *new = (TreeNode *)malloc(sizeof(TreeNode));
    new->key = x;
    if (par != NULL) {
        if (x < par->key)
            par->left = new;
        else
            par->right = new;
    }

    return new;
}

TreeNode *maxNode(TreeNode *here) {
    while (here != NULL && here->right != NULL) here = here->right;
    return here;
}

TreeNode *deleteNode(TreeNode *root, char x) {
    TreeNode *here = root, *par = NULL;
    while (here != NULL && here->key != x) {
        par = here;
        here = x < here->key ? here->left : here->right;
    }

    if (here == NULL) return root;

    if (here->left == NULL && here->right == NULL) {
        if (par != NULL) {
            if (par->left == here) par->left = NULL;
            if (par->right == here) par->right = NULL;
        }

        if (here == root) root = NULL;
        free(here);
    } else if ((here->left == NULL) ^ (here->right == NULL)) {
        TreeNode *ret = NULL;
        if (here->left != NULL) ret = here->left;
        if (here->right != NULL) ret = here->right;

        if (par != NULL) {
            if (par->left == here) par->left = NULL;
            if (par->right == here) par->right = NULL;
        }

        if (here == root) root = ret;
        free(here);
    } else {
        TreeNode *candidate = maxNode(here->left);
        here->key = candidate->key;
        deleteNode(here->left, candidate->key);
    }

    return root;
}

TreeNode *searchNode(TreeNode *root, char x) {
    TreeNode *here = root, *par = NULL;

    while (here != NULL && here->key != x) {
        par = here;
        here = x < here->key ? here->left : here->right;
    }

    return here;
}

void displayInorder(TreeNode *here) {
    if (here == NULL) return;
    displayInorder(here->left);
    printf("%c", here->key);
    displayInorder(here->right);
}

void menu() {
    printf(" \n*---------------------------*");
    printf(" \n \t1 : 트리 출력");
    printf(" \n \t2 : 문자 삽입");
    printf(" \n \t3 : 문자 삭제");
    printf(" \n \t4 : 문자 검색");
    printf(" \n \t5 : 종료");
    printf(" \n*---------------------------*");
    printf(" \n메뉴입력 >> ");
}

int main() {
    TreeNode *root = NULL;
    TreeNode *foundedNode = NULL;

    char choice, key;
    root = insertNode(root, 'G');
    insertNode(root, 'I');
    insertNode(root, 'H');
    insertNode(root, 'D');
    insertNode(root, 'B');
    insertNode(root, 'M');
    insertNode(root, 'N');
    insertNode(root, 'A');
    insertNode(root, 'J');
    insertNode(root, 'E');
    insertNode(root, 'Q');

    while (1) {
        menu();
        choice = getchar();
        getchar();

        switch (choice) {
            case '1':
                printf(" \t[이진트리 출력] ");
                displayInorder(root);
                printf("\n");
                break;

            case '2':
                printf("삽입할 문자를 입력하세요 : ");
                key = getchar();
                getchar();
                insertNode(root, key);
                break;

            case '3':
                printf("삭제할 문자를 입력하세요 : ");
                key = getchar();
                getchar();
                root = deleteNode(root, key);
                break;

            case '4':
                printf("찾을 문자를 입력하세요 : ");
                key = getchar();
                getchar();
                foundedNode = searchNode(root, key);
                if (foundedNode != NULL)
                    printf(" \n %c 를 찾았습니다! \n", foundedNode->key);
                else
                    printf(" \n 문자를 찾지 못했습니다. \n");
                break;

            case '5':
                return 0;

            default:
                break;
        }
    }

    return 0;
}

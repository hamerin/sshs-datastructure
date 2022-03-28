// 재귀적 구현

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    char key;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode *insertNode(TreeNode *here, char x) {
    if (here == NULL) {
        TreeNode *ptr = (TreeNode *)malloc(sizeof(TreeNode));
        ptr->key = x;
        return ptr;
    }
    if (here->key == x) return NULL;

    if (x < here->key) {
        if (here->left == NULL)
            return here->left = insertNode(here->left, x);
        else
            return insertNode(here->left, x);
    } else {
        if (here->right == NULL)
            return here->right = insertNode(here->right, x);
        else
            return insertNode(here->right, x);
    }
}

TreeNode *maxNode(TreeNode *here) {
    if (here == NULL) return NULL;
    return here->right == NULL ? here : maxNode(here->right);
}

TreeNode *deleteNode(TreeNode *here, TreeNode *par, char x) {
    if (here == NULL) return NULL;
    if (x < here->key) {
        deleteNode(here->left, here, x);
        return here;
    }
    if (here->key < x) {
        deleteNode(here->right, here, x);
        return here;
    }

    if (here->left == NULL && here->right == NULL) {
        if (par != NULL) {
            if (par->left == here) par->left = NULL;
            if (par->right == here) par->right = NULL;
        }

        free(here);
        return NULL;
    } else if ((here->left == NULL) ^ (here->right == NULL)) {
        TreeNode *ret = NULL;
        if (here->left != NULL) ret = here->left;
        if (here->right != NULL) ret = here->right;

        if (par != NULL) {
            if (par->left == here) par->left = ret;
            if (par->right == here) par->right = ret;
        }

        free(here);
        return ret;
    } else {
        TreeNode *candidate = maxNode(here->left);
        here->key = candidate->key;
        deleteNode(here->left, here, candidate->key);
        
        return here;
    }
}

TreeNode *searchNode(TreeNode *here, char x) {
    if (here == NULL) return NULL;
    if (x < here->key) return searchNode(here->left, x);
    if (x > here->key) return searchNode(here->right, x);
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
                root = deleteNode(root, NULL, key);
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

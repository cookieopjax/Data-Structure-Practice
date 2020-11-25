#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#pragma warning (disable:4996)

typedef struct tree {
    int val;
    struct tree* left;
    struct tree* right;
}treeNode;

void addNode(treeNode** root, int num);
void inorder_traversal(treeNode* root);
void preorder_traversal(treeNode* root);
void postorder_traversal(treeNode* root);
void printLeaf(treeNode* root);
int treeMax(treeNode* root);
int treeMin(treeNode* root);

int main() {
    treeNode* root = NULL;
    char tempStr[5] = { 0 };
    FILE* input = fopen("input.txt", "r"); //input.txt包含每個節點的值，依序讀入
    if(input == NULL) {
        printf("開檔失敗!\n");
        return -1;
    }

    while (fscanf(input, "%s", tempStr) != EOF) {
        if (strcmp(tempStr, "0") == 0)break;
        printf("Insert a number : %d\n", atoi(tempStr));
        addNode(&root, atoi(tempStr));
    }

    printf("---------------------------------\n");
    printf("Preorder : ");
    preorder_traversal(root);
    printf("\n");
    printf("Inorder : ");
    inorder_traversal(root);
    printf("\n");
    printf("Postorder：");
    postorder_traversal(root);
    printf("\n");

    printf("MAX : %d\n", treeMax(root));
    printf("MIN : %d\n", treeMin(root));
    printf("LeafNodes : ");
    printLeaf(root);
}

void addNode(treeNode** root, int num) {
    treeNode* newNode = (treeNode*)malloc(sizeof(treeNode));
    newNode->val = num;
    newNode->left = NULL;
    newNode->right = NULL;

    if (!(*root)) {
        *root = newNode;
        return;
    }

    treeNode* current = *root;
    while (true) {
        if ((current->val) > (newNode->val)){
            if ((current->left) == NULL) {
                //printf("-左節點賦值\n");
                current->left = newNode;
                break;
            }
            else {
                //printf("-左移\n");
                current = current->left;
            }
        }
        else if ((current->val) < (newNode->val)) {
            if ((current->right) == NULL) {
                //printf("-右節點賦值\n");
                current->right = newNode;
                break;
            }
            else {
                //printf("-右移\n");
                current = current->right;
            }
        }
        else{
            printf("%d already exist.\n", current->val);
            return;
        }
    }
}

void inorder_traversal(treeNode* root) {
    if (root) {
        inorder_traversal(root->left);
        printf("%d ", (root)->val);
        inorder_traversal(root->right);
    }
}

void preorder_traversal(treeNode* root) {
    if (root) {
        printf("%d ", root->val);
        preorder_traversal(root->left);
        preorder_traversal(root->right);
    }
}

void postorder_traversal(treeNode* root) {
    if (root) {
        postorder_traversal(root->left);
        postorder_traversal(root->right);
        printf("%d ", root->val);
    }
}

void printLeaf(treeNode* root) {
    if (root) {
        printLeaf(root->left);
        printLeaf(root->right);
        if ((!root->left) && (!root->right))
            printf("%d ", root->val);
    }
}

int treeMax(treeNode* root) {
    while (root->right) {
        root = root->right;
    }
    return root->val;
}

int treeMin(treeNode* root) {
    while (root->left) {
        root = root->left;
    }
    return root->val;
}


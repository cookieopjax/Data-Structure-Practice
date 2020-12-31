#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define STACKMAX 200
#pragma warning(disable : 4996) //visual studio認為scanf不安全，故用此移除警告
// preorder : visit -> left -> right
// inorder : left -> visit -> right

typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
}treeNode;

//遞迴
void recur_preorder_traversal(treeNode* root); 
void recur_inorder_traversal(treeNode* root); 
void recur_postorder_traversal(treeNode* root);

//疊代
void iter_preorder_traversal(treeNode* root); 
void iter_inorder_traversal(treeNode* root);
void iter_postorder_traversal(treeNode* root); //目前還沒寫好

void push(treeNode** stack, int* top, treeNode* newTreeNode);
treeNode* pop(treeNode** stack, int* top);
bool isEmpty(int top);
void printStack(treeNode** stack, int* top);
void addNode(treeNode** root, int num); //創建樹

int main() {

    int input = 0;
    treeNode* root = NULL;
    printf("請輸入節點(0 結束輸入並輸出):\n");

    while (true) {
        scanf("%d", &input);
        if (input == 0)break;
        addNode(&root, input);
    }

    printf("遞迴前序追蹤 : ");
    recur_preorder_traversal(root);
    printf("\n");
	  printf("疊代前序追蹤 : ");
	  iter_preorder_traversal(root);
	  printf("\n");

    printf("遞迴中序追蹤 : ");
    recur_inorder_traversal(root);
	  printf("\n");
	  printf("疊代中序追蹤 : ");
	  iter_inorder_traversal(root);
    printf("\n");

    printf("遞迴後序追蹤 : ");
    recur_postorder_traversal(root);
    printf("\n");
    printf("疊代後序追蹤 : ");
    iter_postorder_traversal(root);
    printf("\n");

}
void recur_preorder_traversal(treeNode* root) {
    if (root) {
        printf("%d ", root->val);
        recur_preorder_traversal(root->left);
        recur_preorder_traversal(root->right);
    }
}

void recur_inorder_traversal(treeNode* root) {
    if (root) {
        recur_inorder_traversal(root->left);
        printf("%d ", root->val);
        recur_inorder_traversal(root->right);
    }
}

void recur_postorder_traversal(treeNode* root) {
    if (root) {
        recur_inorder_traversal(root->left);
        recur_inorder_traversal(root->right);
        printf("%d ", root->val);
    }
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
        if ((current->val) > (newNode->val)) {
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
        else {
            printf("%d already exist.\n", current->val);
            return;
        }
    }
}

void iter_preorder_traversal(treeNode* root) {
    // preorder : visit -> left -> right
    treeNode* stack[STACKMAX];
    int top = -1;
    int* topPtr = &top;

    push(stack, topPtr, root);
    while (!isEmpty(top)) {
        treeNode* current = pop(stack, topPtr);
        printf("%d ", current->val);

        //在堆疊內，先進後出，故先放right再放left
        if (current->right)
            push(stack, topPtr, current->right);
        if (current->left)
            push(stack, topPtr, current->left);
    }
}

void iter_inorder_traversal(treeNode* root) {
    treeNode* stack[STACKMAX];
    int top = -1;
    int* topPtr = &top;

    treeNode* current = root;
    while ((!isEmpty(top)) || current) {
        if (current) {
            push(stack, topPtr, current);
            current = current->left;
        }
        else {
            treeNode* temp = pop(stack, topPtr);
            printf("%d ", temp->val);
            current = temp->right;
        }
    }

}

void iter_postorder_traversal(treeNode* root) {
    treeNode* stack1[STACKMAX];
    treeNode* stack2[STACKMAX];
    int top1 = -1, top2 = -1;
    int* top1Ptr = &top1;
    int* top2Ptr = &top2;

    push(stack1, top1, root);
    while (!isEmpty(top1)) {
        treeNode* current = pop(stack1, top1Ptr);
        push(stack2, top2Ptr, current);

        if (current->left) {
            push(stack1, top1Ptr, current->left);
        }
        if (current->right) {
            push(stack1, top1Ptr, current->right);
        }
    }
}

void push(treeNode** stack, int* top, treeNode* newTreeNode) {
    (*top)++;
    stack[*top] = newTreeNode;
}

treeNode* pop(treeNode** stack, int* top) {
    if (isEmpty(*top)) {
        printf("錯誤!!!空堆疊卻POP，請重新檢查程式");
        return NULL;
    }

    treeNode* temp = stack[*top];
    stack[*top] = NULL;
    (*top)--;
    return temp;
}

bool isEmpty(int top) {
    if (top == -1)
        return true;
    return false;
}

void printStack(treeNode** stack, int* top) {
    printf("stack = [ ");
    for (int i = 0; i <= (*top); i++) {
        printf("(%p,%d,%p)", stack[i]->left, stack[i]->val, stack[i]->right);
        if (i != (*top))
            printf(" ,");
    }
    printf(" ]\n");
}

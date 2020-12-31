#include <stdio.h>
#include <stdbool.h>
#include <limits.h> 
#pragma warning (disable:4996)
//leetcode : https://leetcode.com/problems/merge-two-sorted-lists/

typedef struct ListNode {
    int val;
    struct ListNode* next;
}node;

node* mergeTwoLists(node* l1, node* l2);
void pushBack(int num, node** head);
void traversal(node* head);

int main() {
    int num = 0, newNum = INT_MIN;
    node* head1 = NULL;
    node* head2 = NULL;
    while (true) {
        scanf("%d", &num);
        if (num == -1)
            break;
        if (num < newNum) {
            printf("數字沒有按照大小排，請重新輸入\n");
            continue;
        }
        newNum = num;
        pushBack(num, &head1);
    }
    traversal(head1);

    newNum = INT_MIN;
    while (true) {
        scanf("%d", &num);
        if (num == -1)
            break;
        if (num < newNum) {
            printf("數字沒有按照大小排，請重新輸入\n");
            continue;
        }
        newNum = num;
        pushBack(num, &head2);
    }
    traversal(head2);

    traversal(mergeTwoLists(head1, head2));
   

}

node* mergeTwoLists(node* l1, node* l2) {

    node* head = (node*)malloc(sizeof(node));
    node* current = head;

    while ((l1 != NULL) && (l2 != NULL)) {
        if (l1->val > l2->val) {
            current->next = l2;
            l2 = l2->next;
        }
        else {
            current->next = l1;
            l1 = l1->next;  
        }

        current = current->next;
    }

    if (l1 == NULL) {
        current->next = l2;
    }
    else if (l2 == NULL) {
        current->next = l1;
    }

    return  head->next;
   
}


void pushBack(int num, node** head) {

    node* newNode = (node*)malloc(sizeof(node));
    newNode->val = num;
    newNode->next = NULL;
     
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    node* last = *head;
    while (last->next != NULL)
        last = last->next;
    last->next = newNode;
}

void traversal(node* head) {
    if (head == NULL) {
        printf("串聯為空\n");
        return;
    }

    node* current = head;
    printf("串列 : ");
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
    
}

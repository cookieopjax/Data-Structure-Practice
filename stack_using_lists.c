#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma warning (disable:4996)

typedef struct ListNode {
	int val;
	struct ListNode* next;
	struct ListNode* prev;
}node;

bool isEmpty(node** head);
void push(node** head, int num);
void pop(node** head);
void traversal(node** head);

int main() {
	int select = 0, tempNum = 0;
	node* head = NULL;
	while (true) {
		printf("1.插入 2.移除 3.印出 0.結束, 請輸入:");
		scanf("%d", &select);
		switch (select) {
		case 1:
			scanf("%d", &tempNum);
			push(&head, tempNum);
			break;
		case 2:
			pop(&head);
			break;
		case 3:
			traversal(&head);
			break;
		default:
			return 0;
		}
	}
}

bool isEmpty(node** head) {
	if ((*head) == NULL)
		return true;
	else
		return false;
}

void push(node** head, int num) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->val = num;
	newNode->next = NULL;
	newNode->prev = NULL;

	if (*head == NULL) {
		*head = newNode;
		return;
	}

	node* last = *head;
	while (last->next != NULL)
		last = last->next;

	newNode->prev = last;
	last->next = newNode;
	
}

void pop(node** head) {
	if (isEmpty(head)){
		printf("佇列為空!!\n");
		return;
	}
	if (((*head)->next) == NULL) {
		(*head) = NULL;
		return;
	}
	node* last = *head;
	while (last->next != NULL)
		last = last->next;
	last->prev->next = NULL;
	free(last);
}

void traversal(node** head) {
	if ((*head) == NULL) {
		printf("串聯為空\n");
		return;
	}

	node* current = (*head);
	while (current->next != NULL) {
		current = current->next;
	}
	printf("stack : ");
	while (current != NULL) {
		printf("%d ", current->val);
		current = current->prev;
	}
	printf("\n");
}

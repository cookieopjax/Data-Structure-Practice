#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

//最早放進去的東西會最先被取出來
//from rear push, from front pop
//0不放東西，起於0，只要有一個元素，rear = 1
//因為是循環的，要用%，例如0~8佇列，(8+1)%9=0 他會自己回到該有的位置
//當rear = front 佇列為空
//(Rear+1) % MAX = Front 佇列已滿 (因為有一格不放要+1)

int* create();
void push(int* Quene, int* Front, int* Rear, int num);
void pop(int* Quene, int* Front, int* Rear);
void show(int* Quene, int Front, int Rear);
bool isEmpty(int* Front, int* Rear);
bool isFull(int* Front, int* Rear);
int main() {
	int select = 0, tempNum = 0;
	int front = 0, rear = 0;
	int* frontPtr = &front;
	int* rearPtr = &rear;
	int* queue = create();
	while (true) {
		printf("[1]insert [2]delete [3]show [0]exit：");
		scanf("%d", &select);
		if (select == 1) {
			printf("請輸入欲增加之數 : ");
			scanf("%d", &tempNum);
			push(queue, frontPtr, rearPtr, tempNum);
		}
		else if (select == 2) {
			pop(queue, frontPtr, rearPtr);
		}
		else if (select == 3) {
			show(queue, frontPtr, rearPtr);
		}
		else {
			return 0;
		}
	}
}
int* create() {
	int* temp = (int*)calloc(MAX, sizeof(int));
	return temp;
}
void push(int* Quene, int* Front, int* Rear, int num) {
	if (isFull(Front,Rear)) {
		printf("佇列已滿\n");
		return;
	}
	(*Rear) = ((*Rear) + 1) % MAX;
	Quene[(*Rear)] = num;
}
void pop(int* Quene, int* Front, int* Rear) {
	if (isEmpty(Front, Rear)) {
		printf("佇列為空\n");
		return;
	}
	(*Front) = ((*Front) + 1) % MAX;
	printf("%d is deleted\n", Quene[(*Front)]);
	Quene[(*Front)] = 0;
}
void show(int* Quene, int* Front, int* Rear) {
	int Fronts = (*Front);
	int Rears = (*Rear);
	if (!isEmpty(Front, Rear)) {
		printf("佇列 : ");
		while (Fronts != Rears) {
			Fronts = (Fronts + 1) % MAX;
			printf("%d ", Quene[Fronts]);
		}
		printf("\n");
	}
	else {
		printf("佇列為空\n");
	}
}
bool isEmpty(int* Front, int* Rear) {
	return ((*Front) == (*Rear));
}
bool isFull(int* Front, int* Rear) {
	return ((*Rear + 1) % MAX == (*Front));
}

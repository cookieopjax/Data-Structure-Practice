#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#pragma warning (disable:4996)
#define TREEMAX 200

/*heap tree - node index(i)
樹中每一節點之鍵值必大於其子樹之鍵值
其left child必定位在index(2i)；
其right child必定位在index(2i + 1)；
其parent必定位在index(⌊i / 2⌋)。
isEmpty() -> 若樹為空時操作Show、Search，需顯示Tree is empty！
Insert()  -> 將讀入的鍵值新增至樹中，若樹中已存在該鍵值，輸出XX already exist！
Delete()  -> 將讀入的鍵值從樹中刪除，若樹不存在該鍵值，輸出XX does not exist！
Show()    -> 印出目前樹的狀態，包括後序追蹤、總節點數量、最大鍵值
Search()  -> 輸入一個數字，找出樹中此鍵值擁有的子樹有哪些鍵值 (不須按照順序)
若該鍵值沒有子節點則顯示NULL，若樹中不存在該鍵值則顯示XX does not exist！*/

void swap(int* x, int* y);
int get_left_child(int index, int last);
int get_right_child(int index, int last);
void insertNode(int tree[], int* last, int newNum);
void deleteNode(int tree[], int* last, int delNum);
void printArr(int arr[], int len);
void searchPostOrder(int tree[], int index, int last, int origin);
void postOrder(int tree[], int index, int last);
void searchNode(int tree[], int last, int searchNode);
int findMax(int tree[], int index);

int main() {
	int heapTree[TREEMAX] = { 0 };
	int select = 0, num = 0;
	int len = 0;
	int* lenPtr = &len;
	FILE* input = fopen("input_1.txt", "r");
	if (input == NULL) {
		printf("讀檔失敗!\n");
		return -1;
	}

	while (fscanf(input, "%d", &select) != EOF) {
		printf("[1] Insert [2] Delete [3] Show [4] Search ： %d\n", select);

		switch (select) {
		case 1: //insert
			fscanf(input, "%d", &num);
			printf("Insert the number: %d\n", num);
			insertNode(heapTree, lenPtr, num);
			break;
		case 2: //delete
			fscanf(input, "%d", &num);
			printf("Delete the number: %d\n", num);
			deleteNode(heapTree, lenPtr, num);
			break;
		case 3: //show
			printf("postorder : ");
			postOrder(heapTree, 1, len);
			printf("\n");
			printf("Total : %d\n", len);
			printf("Max : %d\n", findMax(heapTree, len));

			//printArr(heapTree, len);

			break;
		case 4: //search
			fscanf(input, "%d", &num);
			printf("Search the number: %d\n", num);
			printf("child : ");
			searchNode(heapTree, len, num);
			printf("\n");
			break;
		default:
			break;
		}
	}
}

void swap(int* x, int* y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

int get_left_child(int index, int last) {
	if ((2 * index) <= last) {
		return (2 * index);
	}
	return -1;

}

int get_right_child(int index, int last) {
	if ((2 * index + 1) <= last) {
		return (2 * index + 1);
	}
	return -1;
}

void insertNode(int tree[], int* last, int newNum) {
	for (int i = 1; i < *last; i++) {
		if (tree[i] == newNum) {
			printf("此節點已存在\n");
			return;
		}
	}
	(*last) += 1;
	tree[(*last)] = newNum; //先放入最後一位

	int current = (*last);
	int parent = (*last) / 2;
	
	//不斷向上與父節點進行比較，若較大則交換位置，較小則不動
	while (tree[current] > tree[parent]) {
		if (current == 1)
			return;
		swap(&tree[current], &tree[parent]);
		current = parent;
		parent = parent / 2;
	}
	
}

void deleteNode(int tree[], int* last, int delNum) {
	int current, child;
	
	//先尋找欲刪除節點位置
	for (current = 1; current <= *last; current++) {
		if (delNum == tree[current])
			break;
		if (current == *last) {
			printf("查不到此數\n");
			return;
		}
	}

	swap(&tree[current], &tree[*last]);
	(*last)--;
	
	if (tree[current * 2] > tree[current * 2 + 1]) {
		child = current * 2;
	}
	else {
		child = current * 2 + 1;
	}

	while (tree[current] < tree[child]) {
		if (child > (*last))
			break;
		swap(&tree[current], &tree[child]);
		current = child;
		if (tree[current * 2] > tree[current * 2 + 1]) {
			child = current * 2;
		}
		else {
			child = current * 2 + 1;
		}
	}

}

void printArr(int arr[], int len) {
	printf("Tree : [");
	for (int i = 0; i <= len; i++) {
		printf("%d ", arr[i]);
	}
	printf("]\n");
}

void searchPostOrder(int tree[], int index, int last, int origin) {
	if (index > 0) {
		searchPostOrder(tree, get_left_child(index, last), last, origin);
		searchPostOrder(tree, get_right_child(index, last), last, origin);
		if (tree[index] != origin)
			printf("%d ", tree[index]);
	}
}

void searchNode(int tree[], int last, int searchNode) {
	int current;
	for (current = 1; current <= last; current++) {
		if (searchNode == tree[current])
			break;
		if (current == last) {
			printf("查不到此數");
			return;
		}
	}
	searchPostOrder(tree, current, last, searchNode);

}

void postOrder(int tree[], int index, int last) {
	if (index > 0) {
		postOrder(tree, get_left_child(index, last), last);
		postOrder(tree, get_right_child(index, last), last);
		printf("%d ", tree[index]);
	}
}

int findMax(int tree[], int index) {
	int max = INT_MIN;
	for (int i = 1; i <= index; i++) {
		if (tree[i] > max) {
			max = tree[i];
		}
	}
	return max;
}


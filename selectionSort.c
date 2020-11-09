#include <stdio.h>
#include <limits.h>

void selectionSort(int* arr);
int main() {
	int sort[10] = { 0 };
	printf("請輸入要進行選擇排序的十個數字:\n");
	for (int i = 0; i < 10; i++) {
		scanf("%d", &sort[i]);
	}
	selectionSort(sort);
	printf("排序後陣列:\n");
	for (int i = 0; i < 10; i++) {
		printf("%d ", sort[i]);
	}
}

void selectionSort(int* arr) {
	int minIndex = 0;
	int hasSort = 0;
	while (hasSort < 10) {
		int min = INT_MAX;

		for (int i = hasSort; i < 10; i++) {
			if (arr[i] < min) {
				min = arr[i];
				minIndex = i;
			}
		}

		int temp = arr[hasSort];
		arr[hasSort] = arr[minIndex];
		arr[minIndex] = temp;

		hasSort++;
	}
}

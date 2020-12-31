#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define STACKMAX 50 //stack大小上限

////////////////求前置值///////////////////////
//由後往前讀
//準備好一個stack，存放operands
//遇到operands push進stack
//遇到operaters 取stack上方兩個運算
//以除法為例為 stack[top]/stack[top-1] (如果是求後置值則相反)
//最後的stack頂端即是答案
//////////////////////////////////////////////

float getPrefixValue(char* prefix, float* stack, int* top);
void push(float* stack, int* top, float num);
float pop(float* stack, int* top);
bool isFull(int top);
bool isEmpty(int top);

int main() {

	float stack[STACKMAX] = { 0 };  //型態皆用float
	int top = -1;
	int* topPtr = &top;
	char prefix[50] = { 0 };
	while (true) {
		//initialization
		memset(prefix, 0, sizeof(prefix));
		memset(stack, 0, sizeof(stack));
		top = -1;

		printf("請輸入前置字串 : ");
		scanf("%s", prefix);

		if (strcmp(prefix, "0") == 0)return 0; //輸入0結束輸入

		printf("值 = %.2f\n\n", getPrefixValue(prefix, stack, topPtr));

	}

}

float getPrefixValue(char* prefix, float* stack, int* top) {
	for (int i = strlen(prefix) - 1; i >= 0; i--) { //由後往前
		//運算元直接存進stack
		if (isdigit(prefix[i])) {
			push(stack, top, prefix[i] - 48.0); //char轉進float 根據ascii -48
		}
		else {
			float TopNum = 0, secondaryNum = 0, NewNum = 0;
			//運算子 pop兩個運算元去運算
			TopNum = pop(stack, top);
			secondaryNum = pop(stack, top);
			switch (prefix[i]) { //注意postfix和prefix的運算先後是相反的
				case '+':
					NewNum = TopNum + secondaryNum;
					break;
				case '-':
					NewNum = TopNum - secondaryNum;
					break;
				case '*':
					NewNum = TopNum * secondaryNum;
					break;
				case '/':
					NewNum = TopNum / secondaryNum;
					break;
				case '%':
					NewNum = (int)TopNum % (int)secondaryNum; // % 僅能用整數
					break;
				default:
					printf("讀取運算子錯誤 ! 請重新檢查程式\n");
					break;
			}
			push(stack, top, NewNum); //push運算後的結果
		}
	}
	return stack[(*top)];//stack最頂端即是答案
}

void push(float* stack, int* top, float num) {
	(*top)++;
	stack[(*top)] = num;
}

float pop(float* stack, int* top) {
	float tempNum = stack[(*top)];
	stack[(*top)] = 0.0;
	(*top)--;
	return tempNum;
}

bool isFull(int top) {
	if (top == STACKMAX)
		return true;
	else
		return false;
}

bool isEmpty(int top) {
	if (top <= -1)
		return true;
	else
		return false;
}

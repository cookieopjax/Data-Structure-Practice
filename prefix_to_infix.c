#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define STACKMAX 50 //stack大小上限

void prefix_to_infix(char* infix, char* prefix);
float getPrefixValue(char* prefix);
void push(char** stack, int* top, char* str);
void pushF(float* stack, int* top, float num);
char* pop(char** stack, int* top);
float popF(float* stack, int* top);
bool isFull(int top);
bool isEmpty(int top);
void showAllStack(char** stack, int top);
int precedence(char op);

int main() {
	FILE* input = fopen("input_1.txt", "r");
	if (input == NULL) {
		printf("開檔失敗!\n");
		return -1;
	}
	char tmpStr[50] = { 0 };
	char infix[50] = { 0 };
	char prefix[50] = { 0 };
	while (fscanf(input, "%s", prefix) != EOF) {
		printf("輸入前置式:%s\n", prefix);
		prefix_to_infix(infix, prefix);
		printf("輸出中置式:%s\n", infix);
		printf("值:%.2f", getPrefixValue(prefix));
		printf("\n\n------------------------------------------\n");
	}
}

float getPrefixValue(char* prefix) {
	float stack[STACKMAX] = { 0 };  //型態皆用float
	int top = -1;
	int* topPtr = &top;
	for (int i = strlen(prefix) - 1; i >= 0; i--) { //由後往前
		//運算元直接存進stack
		if (isdigit(prefix[i])) {
			pushF(stack, topPtr, prefix[i] - 48.0); //char轉進float 根據ascii -48
		}
		else {
			float TopNum = 0, secondaryNum = 0, NewNum = 0;
			//運算子 pop兩個運算元去運算
			TopNum = popF(stack, topPtr);
			secondaryNum = popF(stack, topPtr);
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
			pushF(stack, topPtr, NewNum); //push運算後的結果
		}
	}
	return stack[top];//stack最頂端即是答案
}
void prefix_to_infix(char* infix, char* prefix) {
	char** stack = (char**)calloc(50, sizeof(char*));
	for (int i = 0; i < 50; i++)
		stack[i] = (char*)calloc(50, sizeof(char));
	int top = -1;
	int* topPtr = &top;

	for (int i = strlen(prefix) - 1; i >= 0; i--) {
		//printf("解析[%c] , ", prefix[i]);
		if (precedence(prefix[i]) == 0) { //數字 
			char tempStr[2] = { prefix[i] , '\0' };
			push(stack, topPtr, tempStr);
		}
		else {
			char* topStr = pop(stack, topPtr);
			char* secondStr = pop(stack, topPtr);
			char newStr[50] = "\0";
			char operatorStr[2] = { prefix[i], '\0' };

			strcat(newStr, "(");
			strcat(newStr, topStr);
			strcat(newStr, operatorStr);
			strcat(newStr, secondStr);
			strcat(newStr, ")");

			push(stack, topPtr, newStr);
		}
		//showAllStack(stack, top);
	}

	int len = 0;
	while (!isEmpty(top)) {
		strcpy(infix, pop(stack, topPtr));
		len++;
	}
}
void push(char** stack, int* top, char* str) {
	(*top)++;
	strcpy(stack[(*top)], str);
}
void pushF(float* stack, int* top, float num) {
	(*top)++;
	stack[(*top)] = num;
}
char* pop(char** stack, int* top) {
	char* tempStr = (char*)calloc(50, sizeof(char));
	strcpy(tempStr, stack[(*top)]);
	strcpy(stack[(*top)], "0");
	(*top)--;

	return tempStr;
}
float popF(float* stack, int* top) {
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
void showAllStack(char** stack, int top) {
	printf("stack = [");
	for (int i = 0; i <= top; i++) {
		printf("%s,", stack[i]);
	}
	printf("]\n");
}
int precedence(char op) {
	switch (op) {
	case '+': case '-':
		return 1;
	case '*': case '/': case '%':
		return 2;
	default:
		return 0;
	}
}

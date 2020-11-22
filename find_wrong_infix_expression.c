#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define STACKMAX 100

bool isOperator(char op);
bool isParenthesis(char op);
int infixJudge(char* infix);
void push(char* stack, int* top, char ch);
void pop(char* stack, int* top);
bool isFull(int top);
bool isEmpty(int top);

int main() {
	char infix[STACKMAX] = { 0 };
	FILE* input = fopen("input_2.txt", "r");
	if (input == NULL) {
		printf("開檔失敗!\n");
		return -1;
	}
	else {
		printf("File read success\n\n");
		printf("----------------------------\n");
	}
	while (fscanf(input, "%s", infix) != EOF) {
		printf("%s	", infix);
		switch (infixJudge(infix)) {
			case 0:
				printf("Pass\n");
				break;
			case 1:
				printf("Fail：Symbol of operation errors \n");
				break;
			case 2:
				printf("Fail：The number of symbol errors\n");
				break;
			case 3:
				printf("Fail：Parentheses error\n");
				break;
			default:
				break;
		}
	}
	printf("----------------------------\n");
	printf("finsish");
}


bool isOperator(char op){
	if ((op == '+') || (op == '-') || (op == '*') || (op == '/') || (op == '^'))
		return true;
	else
		return false;
}
bool isParenthesis(char op) {
	if ((op == '(') || (op == ')'))
		return true;
	else
		return false;
}
int infixJudge(char* infix) {
	//return 0 -> Pass
	//return 1 -> Symbol of operation errors
	//return 2 -> The number of symbol errors
	//return 3 -> Parentheses errors 
	char stack[STACKMAX] = { 0 };
	int top = -1;
	int* topPtr = &top;
	int lens = (int)strlen(infix);

	for (int i = 0; i < lens; i++) {
		if ((!isOperator(infix[i])) && (!isdigit(infix[i])) && (!isParenthesis(infix[i])))
			return 1;
		else if(isOperator(infix[i])){
			if (i == 0)
				return 2;
			else {
				if (!((isdigit(infix[i - 1])||isParenthesis(infix[i - 1])) && (isdigit(infix[i + 1])||isParenthesis(infix[i + 1]))))
					return 2;
			}
		}
		else if (isParenthesis(infix[i])) {
			if (infix[i] == '(')
				push(stack, topPtr, '(');
			else {
				if ((!isEmpty(top)) && (stack[top] == '('))
					pop(stack, topPtr);
				else
					return 3;
			}

		}
	}
	return 0;
}

void push(char* stack, int* top, char ch) {
	(*top)++;
	stack[(*top)] = ch;
}

void pop(char* stack, int* top) {
	stack[(*top)] = '0';
	(*top)--;
}

bool isFull(int top) {
	if ((top) == STACKMAX) {
		//printf("Stack is full！\n");
		return true;
	}
	else {
		return false;
	}
}

bool isEmpty(int top) {
	if ((top) == -1) {
		//printf("Stack is Empty！\n");
		return true;
	}
	else {
		return false;
	}
}


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define STACKMAX 50

////////////////中置轉後置之方法/////////////////
//準備好一個stack，存放operater                      
//由左至右讀取infix(中置)字串                         
//遇到operands直接輸出                             
//遇到'('直接pop進去stack                         
//遇到')'不斷pop出stack中的operater輸出，直到遇到')'
//除此之外其他運算子:將讀進去的跟stack頂端比較優先度    
//如果>，直接push;如果<= 要pop，而且要pop至>才停	  
//做完以上後，將stack內的pop出來輸出               
////////////////求後置值///////////////////////
//準備好一個stack，存放operands
//遇到operands push進stack
//遇到operaters 取stack上方兩個運算
//以除法為例為 stack[top-1]/stack[top] (如果是求前置值則相反)
//最後的stack頂端即是答案
//////////////////////////////////////////////

void push(char* stack, int* to, char op);
char pop(char* stack, int* top);
bool isFull(int top);
bool isEmpty(int top);
void showAllStack(char* stack, int top);
void infix_to_postfix(char* infix, char* postfix, char* stack, int* top);
int getPostfixValue(char* postfix);
int precedence(char op);

int main() {
	char stack[STACKMAX] = { 0 };
	int top = -1;
	int* topPtr = &top;
	char infix[50] = { 0 };
	char postfix[50] = { 0 };
	while (true) {
		memset(infix, 0, sizeof(infix));
		memset(postfix, 0, sizeof(postfix));
		memset(stack, 0, sizeof(stack));
		top = -1;

		printf("請輸入中置式字串 : ");
		scanf("%s", infix);
		if (strcmp(infix, "0") == 0)return 0;
		infix_to_postfix(infix, postfix, stack, topPtr);
		printf("後置結果 : %s\n", postfix);
		printf("後置數值 : %d\n\n", getPostfixValue(postfix));

	}

}

void infix_to_postfix(char* infix, char* postfix, char* stack, int* top) {
	int postCount = 0;
	for (int i = 0; i < strlen(infix); i++) {
		switch (infix[i]) {
		case '(':
			push(stack, top, infix[i]);
			break;
		case '+': case '-': case '*': case '/': case '%':
			while (precedence(stack[(*top)]) >= precedence(infix[i])) {
				postfix[postCount] = pop(stack, top);
				postCount++;
			}
			push(stack, top, infix[i]);
			break;
		case ')':
			while (stack[(*top)] != '(') { // 遇 ) 輸出至 ( 
				postfix[postCount] = pop(stack, top);
				postCount++;
			}
			(*top)--;  // 不輸出 ( 
			break;
		default:  // 運算元直接輸出 
			postfix[postCount] = infix[i];
			postCount++;
		}
	}
	while (!(isEmpty((*top)))) {
		postfix[postCount] = pop(stack, top);
		postCount++;
	}


}
int getPostfixValue(char* postfix) {
	//初始化
	int stack[STACKMAX] = { 0 };
	int top = -1;

	for (int i = 0; i < strlen(postfix); i++) {
		if (isdigit(postfix[i])) {
			top++;
			stack[top] = postfix[i] - 48;
		}
		else {
			int TopNum = 0, secondaryNum = 0, NewNum = 0;
			TopNum = stack[top];
			top--;
			secondaryNum = stack[top];
			top--;
			switch (postfix[i]) {
				case '+':
					NewNum = TopNum + secondaryNum;
					break;
				case '-':
					NewNum = secondaryNum - TopNum;
					break;
				case '*':
					NewNum = TopNum * secondaryNum;
					break;
				case '/':
					NewNum = secondaryNum / TopNum;
					break;
				case '%':
					NewNum = secondaryNum % TopNum;
					break;
				default:
					printf("讀取運算子錯誤 ! 請重新檢查程式\n");
					break;
			}
			top++;
			stack[top] = NewNum;
		}
	}
	return stack[top];
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
void push(char* stack, int* top, char op) {
	(*top)++;
	stack[(*top)] = op;
}
char pop(char* stack, int* top) {
	char tempCh = stack[(*top)];
	stack[(*top)] = '\0';
	(*top)--;
	return tempCh;
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
void showAllStack(char* stack, int top) {
	printf("stack = [");
	for (int i = 0; i <= top; i++) {
		printf("%c ", stack[i]);
	}
	printf("]\n");
}

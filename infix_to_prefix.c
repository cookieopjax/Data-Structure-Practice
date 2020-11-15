#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define STACKMAX 50 //stack大小上限

//中置轉前置之方法
//準備好兩個stack，stack1存放operater stack2暫存結果                 
//由右至左讀取infix(中置)字串                         
//遇到operands push to stack2                             
//遇到')' push to stack1                     
//遇到'(' 不斷pop出stack1中元素push至stack2
//除此之外其他運算子:將讀進去的跟stack頂端比較優先度    
//如果>，push stack1 ; 如果<= pop stack1，push stack2直到>才停，然後infix[i]再push stack1
//將第二個stack pop所有值出來即為答案      
       
void infix_to_prefix(char* infix, char* prefix, char* stack, int* top);
void push(char* stack, int* to, char op);
char pop(char* stack, int* top);
bool isFull(int top);
bool isEmpty(int top);
int precedence(char op); //return operater precedence

int main() {
	char stack[STACKMAX] = { 0 };
	int top = -1;
	int* topPtr = &top;
	char infix[50] = { 0 };
	char prefix[50] = { 0 };

	while (true) {
		//initialization
		memset(infix, 0, sizeof(infix));
		memset(prefix, 0, sizeof(prefix));
		memset(stack, 0, sizeof(stack));
		top = -1;

		printf("請輸入中置式字串 : ");
		scanf("%s", infix);

		if (strcmp(infix, "0") == 0)return 0; //輸入0結束輸入

		infix_to_prefix(infix, prefix, stack, topPtr);
		printf("後置式 : %s\n\n", prefix);

	}
}


void infix_to_prefix(char* infix, char* prefix, char* stack, int* top) {
	int postCount = 0;
	char preStack[STACKMAX] = { 0 }; //第二個stack，儲存運算後之數字
	int preTop = -1;//針對preStack的top
	int* preTopPtr = &preTop;

	for (int i = strlen(infix) - 1; i >= 0; i--) { //由後往前
		switch (infix[i]) {
			case ')':
				push(stack, top, infix[i]);
				break;
			case '+': case '-': case '*': case '/': case '%':
				//輸入的優先度小於stack頂的
				while ( precedence(infix[i]) <= precedence(stack[(*top)]) ) {
					//pop第一個stack，push至第二個stack
					push(preStack, preTopPtr, pop(stack, top));
				}
				push(stack, top, infix[i]);
				break;
			case '(':
				while (stack[(*top)] != ')') { // 遇 ( 輸出至 )
					push(preStack, preTopPtr, pop(stack, top));
				}
				(*top)--;  // 不輸出 (
				break;
			default:  // 運算元直接存入第二個stack
				push(preStack, preTopPtr, infix[i]);
		}
	}

	//stack中剩餘的存入第二個stack
	while (!(isEmpty((*top)))) {
		push(preStack, preTopPtr, pop(stack, top));
	}

	//將第二個stack pop所有值出來即為答案
	while (!(isEmpty(preTop))) {
		prefix[postCount] = pop(preStack, preTopPtr);
		postCount++;
	}
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

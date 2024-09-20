#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 3
#define MAX_STR_SIZE 100
typedef struct {
	int num;
	char num_str[MAX_STR_SIZE];
}ArrType;

ArrType data[MAX_STACK_SIZE];
int top = -1;

void init(){
	top = -1;
}	// 스택 초기화 함수

int is_empty(){
	return (top == -1);
}	// 공백 상태 검출 함수

int is_full(){
	return (top == (MAX_STACK_SIZE - 1));
}	// 포화 상태 검출 함수

void push(ArrType item){
	if (is_full()) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else
		data[++top] = item;
}	// 삽입 함수

ArrType pop(){
	if (is_empty()) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		return data[top--];
}	//삭제 함수

ArrType peek(){
	if (is_empty()) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		return data[top];
}	//피크 함수

void stack_print(){
	int i;
	if (is_empty())
		printf("<empty>\n");
	else {
		printf("[%d, %s] <- top\n", peek().num, peek().num_str);

		for (i = top - 1; i >= 0; i--)
			printf("[%d, %s]\n", data[i].num, data[i].num_str);
	}
	printf("--\n");
}

int main(void){
	ArrType a = { "" };

	init(a);
	stack_print();
	ArrType a1 = { 10,"ten" };
	push(a1);
	stack_print();
	ArrType a2 = { 20,"twenty" };
	push(a2);
	stack_print();
	ArrType a3 = { 30,"thirty" };
	push(a3);
	stack_print();
	ArrType a4 = { 40,"forty" };
	push(a4);
	stack_print();
	pop();
	stack_print();
	ArrType a5 = { 50,"fifty" };
	push(a5);
	stack_print();
	pop();
	stack_print();
	pop();
	stack_print();
	pop();
	stack_print();
}
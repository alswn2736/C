#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 3
#define MAX_STR_SIZE 100
typedef struct {
	int num;
	char num_str[MAX_STR_SIZE];
}element;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

void init(StackType* s){
	s->top = -1;
}	// 스택 초기화 함수

int is_empty(StackType* s){
	return (s->top == -1);
}	// 공백 상태 검출 함수

int is_full(StackType* s){
	return (s->top == (MAX_STACK_SIZE - 1));
}	// 포화 상태 검출 함수

void push(StackType* s, element item){
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else
		s->data[++(s->top)] = item;
}	// 삽입 함수

element pop(StackType* s){
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		return s->data[(s->top)--];
}	//삭제 함수

element peek(StackType* s){
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		return s->data[s->top];
}	//피크 함수

void stack_print(StackType* s){
	int i;
	if (is_empty(s))
		printf("<empty>\n");
	else {
		printf("[%d, %s] <- top\n", peek(s).num, peek(s).num_str);

		for (i = s->top - 1; i >= 0; i--)
			printf("[%d, %s]\n", s->data[i].num, s->data[i].num_str);
	}
	printf("--\n");
}

int main(void){
	StackType s;
	element e;

	init(&s);
	stack_print(&s);

	e.num = 10;
	strcpy(e.num_str, "ten");
	push(&s, e);
	stack_print(&s);

	e.num = 20;
	strcpy(e.num_str, "twenty");
	push(&s, e);
	stack_print(&s);

	e.num = 30;
	strcpy(e.num_str, "thirty");
	push(&s, e);
	stack_print(&s);

	e.num = 40;
	strcpy(e.num_str, "forty");
	push(&s, e);
	stack_print(&s);

	pop(&s);
	stack_print(&s);

	e.num = 50;
	strcpy(e.num_str, "fifty");
	push(&s, e);
	stack_print(&s);

	pop(&s);
	stack_print(&s);

	pop(&s);
	stack_print(&s);

	pop(&s);
	stack_print(&s);
}
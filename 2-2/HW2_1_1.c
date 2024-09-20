#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 3
typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;
void init_stack(StackType* s) {
	s->top = -1;
}	// 스택 초기화 함수

int is_empty(StackType* s){
	return (s->top == -1);
}	// 공백 상태 검출 함수

int is_full(StackType* s){
	return (s->top == (MAX_STACK_SIZE - 1));
}	//포화 상태 검출 함수

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
}	// 삭제 함수

element peek(StackType* s){
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		return s->data[s->top];
}	// 피크 함수

void stack_print(StackType* s){

	if (is_empty(s))
		printf("<empty>\n");
	else {
		printf("%d <- top\n", peek(s)); // peek(s) 대신 s->data[s->top] 가능

		for (int i = s->top - 1; i >= 0; i--)
			printf("%d\n", s->data[i]);
	}
	printf("--\n");
}

int main(void) {
	StackType s;

	init_stack(&s);
	stack_print(&s);
	push(&s, 10);
	stack_print(&s);
	push(&s, 20);
	stack_print(&s);
	push(&s, 30);
	stack_print(&s);
	push(&s, 40);
	stack_print(&s);
	pop(&s);
	stack_print(&s);
	push(&s, 50);
	stack_print(&s);
	pop(&s);
	stack_print(&s);
	pop(&s);
	stack_print(&s);
	pop(&s);
	stack_print(&s);
}
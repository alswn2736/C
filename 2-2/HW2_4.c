#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STRING 100
typedef char element;
typedef struct {
	element data[MAX_STRING];
	int top;
} StackType;

void init(StackType* s) {
	s->top = -1;
}

int is_empty(StackType* s) {
	return (s->top == -1);
}

int is_full(StackType* s) {
	return(s->top == (MAX_STRING - 1));
}

void push(StackType* s, element item) {
	if (is_full(s)) {
		printf(stderr, "스택 포화 에러\n");
		return;
	}
	else
		s->data[++(s->top)] = item;
}

element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		return s->data[(s->top)--];
}

element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		return s->data[s->top];
}

int palindrom(char str[]) {
	StackType s;
	
	init(&s);

	for (int i = 0; str[i] != '\0'; i++)
		push(&s, str[i]);

	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] != pop(&s))
			return 0;
	}
	return 1;
}
int main(void) {
	char word[MAX_STRING];

	printf("Enter a word to check palindrom: ");
	scanf("%s", word);

	if (palindrom(word))
		printf("palindrom입니다.\n");
	else
		printf("palindrom이 아닙니다.\n");
}
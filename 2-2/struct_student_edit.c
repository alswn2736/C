#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct Student {
	char name[20];
	int midterm;
	int final;
} Student;
int main(void) {
	Student* sp = (Student*)malloc(sizeof(Student));

	printf("Enter student name: ");
	scanf("%s", (*sp).name);	// 도트 연산자 사용

	printf("Enter midterm and final score: ");
	scanf("%d %d", &(*sp).midterm, &(*sp).final);

	printf("\n이름\t중간\t학기말\n");
	printf("%s\t%d\t%d\n", (*sp).name, (*sp).midterm, (*sp).final);

	free(sp);
}
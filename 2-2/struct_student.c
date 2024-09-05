#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
struct student {
	char name[20];
	int midterm;
	int final;
};
int main(void) {
	struct student aStudent;	// 구조체 변수
	struct student* sp = &aStudent;		// 포인터

	printf("Enter student name: ");
	scanf("%s", sp->name);		// 화살표 연산자 사용 

	printf("Enter midterm and final score: ");
	scanf("%d %d", &sp->midterm, &sp->final); 

	printf("\n이름\t중간\t학기말\n");
	printf("%s\t%d\t%d\n", sp->name, sp->midterm, sp->final);
}
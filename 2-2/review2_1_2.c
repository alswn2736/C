#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct Score {
	int midterm;
	int final;
} Score;
void printScore(Score* p) {
	printf("중간고사 성적은 %d\n", p->midterm);
	printf("학기말고사 성적은 %d\n", p->final);
}
Score* biggerScore(Score* p1, Score* p2) {
	int p1Sum = p1->midterm + p1->final;
	int p2Sum = p2->midterm + p2->final;

	if (p1Sum > p2Sum)
		return p1;
	else
		return p2;
}
Score* totalScore(Score* p1, Score* p2) {
	Score* pSum = (Score*)malloc(sizeof(Score));

	pSum->midterm = p1->midterm + p2->midterm;
	pSum->final = p1->final + p2->final;

	return pSum;
}
Score* createScore(int m, int f) {
	Score* newP = (Score*)malloc(sizeof(Score));
	newP->midterm = m;
	newP->final = f;

	return newP;
}
int main(void) {
	Score s1, s2;
	Score* p3;

	s1.midterm = 50, s1.final = 100;
	s2.midterm = 70, s2.final = 70;

	printScore(&s1);
	printScore(&s2);

	printf("-----------------------------\n");
	printf("둘중 성적이 좋은 점수:\n");

	printScore(biggerScore(&s1, &s2));

	printf("-----------------------------\n");
	printf("두 성적의 총 합:\n");
	printScore(totalScore(&s1, &s2));

	printf("-----------------------------\n");
	p3 = createScore(100, 100);
	printScore(p3);

	free(p3);
}
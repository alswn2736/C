#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void) {
	int row, col, i, j;
	int sum = 0;
	
	printf("2차원 배열의 크기? :");
	scanf("%d %d", &row, &col);	//r행 c열 2차원 배열

	int** p = (int**)malloc(row * sizeof(int*));	// r행 동적 할당
	for (int i = 0; i < row; i++)
		p[i] = (int*)malloc(col * sizeof(int));	// 각 행마다 c열 할당

	srand(time(NULL));

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			p[i][j] = rand() % 100;
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			printf("%d\t", p[i][j]);

		printf("\n");
	}

	for (int i = 0; i < row; i++)
		free(p[i]);
	free(p);

	return 0;
}
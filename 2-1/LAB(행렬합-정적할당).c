#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
void readMatrix(int a[][3]) {
	for (int i = 0; i < 3; i++)
		scanf("%d %d %d", &a[i][0], &a[i][1], &a[i][2]);
}
void matrixAdd(int a[][3], int b[][3], int x[][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			x[i][j] = a[i][j] + b[i][j];
	}
}
void printMatrix(int a[][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			printf("%d ", a[i][j]);

		printf("\n");
	}
}
int main(void) {
	int A[3][3], B[3][3], X[3][3];

	printf("(3 x 3) 행렬 A 입력: ");
	readMatrix(A);

	printf("(3 x 3) 행렬 B 입력: ");
	readMatrix(B);

	matrixAdd(A, B, X);

	printf("행렬합: \n");
	printMatrix(X);
}
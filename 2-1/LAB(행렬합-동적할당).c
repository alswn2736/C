#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
void readMatrix(int** a, int r, int c) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			scanf("%d", &a[i][j]);
		}
	}
}
void matrixAdd(int** a, int** b, int** x, int r, int c) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++)
			x[i][j] = a[i][j] + b[i][j];
	}
}
void printMatrix(int** a, int r, int c) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++)
			printf("%d ", a[i][j]);

		printf("\n");
	}
}
int main(void) {
	int** A,** B;
	int** X;	// A + B
	int row, col;

	printf("Enter 행렬 A의 행과 열의 개수: ");
	scanf("%d %d", &row, &col);

	A = (int**)malloc(row * sizeof(int*));
	for (int i = 0; i < row; i++)
		A[i] = (int*)malloc(col * sizeof(int));

	B = (int**)malloc(row * sizeof(int*));
	for (int i = 0; i < row; i++)
		B[i] = (int*)malloc(col * sizeof(int));

	X = (int**)malloc(row * sizeof(int*));
	for (int i = 0; i < row; i++)
		X[i] = (int*)malloc(col * sizeof(int));

	printf("(%d x %d) 행렬 A 입력: \n", row, col);
	readMatrix(A, row, col);

	printf("(%d x %d) 행렬 B 입력: \n", row, col);
	readMatrix(B, row, col);

	matrixAdd(A, B, X, row, col);

	printf("행렬합: \n");
	printMatrix(X, row, col);

	for (int i = 0; i < row; i++) {
		free(A[i]);
		free(B[i]);
		free(X[i]);
	}
	free(A);
	free(B);
	free(X);

	return 0;
}
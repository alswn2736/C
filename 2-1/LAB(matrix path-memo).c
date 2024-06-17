#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int matrixPath(int** m, int r, int c) {
	int a, b;

	if (r == 0 && c == 0)
		return m[r][c];
	else if (r == 0)
		return matrixPath(m, r, c - 1) + m[r][c];
	else if (c == 0)
		return matrixPath(m, r - 1, c) + m[r][c];
	else {
		a = matrixPath(m, r, c - 1);
		b = matrixPath(m, r - 1, c);
		return ((a < b) ? a : b) + m[r][c];
	}
}
int main(void)
{
	int** m;
	int i, j, r, c;
	r = c = 4;

	m = (int**)malloc(sizeof(int*) * r);
	for (i = 0; i < r; i++)
		m[i] = (int*)malloc(sizeof(int) * c);
	for (i = 0; i < r; i++)
		for (j = 0; j < c; j++)
			scanf("%d", &m[i][j]);

	printf("%d\n", matrixPath(m, r - 1, c - 1));
}
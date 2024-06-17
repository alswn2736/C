#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int comb(int n, int r, int* m)
{
	if (r == 0 || r == n)
		return 1;
	if (r == n - 1) {
		if (m[r] == 0)
			m[r] = comb(n - 1, r - 1, m) + comb(n - 1, r, m);
		return m[r];
	}
	return comb(n - 1, r - 1, m) + comb(n - 1, r, m);

	/*if (r == 0 || r == n) {
		m[n][r] = 1;
		return 1;
	}
	else {
		if (m[n - 1][r - 1] == 0)
			m[n - 1][r - 1] = comb(n - 1, r - 1, m);
		if (m[n - 1][r] == 0)
			m[n - 1][r] = comb(n - 1, r, m);

		m[n][r] = m[n - 1][r - 1] + m[n - 1][r];

		return m[n][r];
	}*/
	/*if (m[n][r] > 0)
		return m[n][r];
	if (r == 0 || r == n)
		return m[n][r] = 1;
	return m[n][r] = comb(n - 1, r - 1, m) + comb(n - 1, r);*/
}
int main(void)
{
	int n, r, i;
	int* m;

	printf("Enter n, r: ");
	scanf("%d %d", &n, &r);

	m = (int*)malloc(sizeof(int) * (r + 1));
	for (i = 0; i <= r; i++)
		m[i] = 0;

	printf("%d\n", comb(n, r, m));

	free(m);
}
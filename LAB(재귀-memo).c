#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
long long combinationRepetition(int n, long long* arr) {
	if (n == 0 || n == 1)
		return 1;

	if (arr[n] > 1)
		return arr[n];

	for (int i = 1; i < n; i++)
		arr[n] += (combinationRepetition(i, arr) * combinationRepetition(n - i, arr));

	return arr[n];
}
int main(void) {
	int n;
	scanf("%d", &n);

	long long* arr = (long long*)malloc(sizeof(long long) * (n + 1));

	for (int i = 0; i <= n; i++)
		arr[i] = 0;

	long long rslt = combinationRepetition(n, arr);
	printf("%lld", rslt);
}
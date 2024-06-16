#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
void merge(int list[], int sorted[], int left, int mid, int right) {
	int i = left;
	int j = mid + 1;
	int k = left;

	while (i <= mid && j <= right) {
		if (list[i] < list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}

	if (i > mid) {
		for (int l = j; l <= right; l++)
			sorted[k++] = list[l];
	}
	else {
		for (int l = i; l <= mid; l++)
			sorted[k++] = list[l];
	}

	for (int l = left; l <= right; l++) {
		list[l] = sorted[l];
	}
}
void merge_sort(int list[], int sorted[], int left, int right) {
	int mid;

	if (left < right) {
		mid = (left + right) / 2;

		merge_sort(list, sorted, left, mid);
		merge_sort(list, sorted, mid + 1, right);
		merge(list, sorted, left, mid, right);
	}
}
int main(void) {
	int n;
	scanf("%d", &n);

	srand(time(NULL));
	int* list = (int*)malloc(n * sizeof(int));
	int* sorted = (int*)malloc(n * sizeof(int));

	for (int i = 0; i < n; i++)
		list[i] = rand() % 100;

	merge_sort(list, sorted, 0, n-1);

	for (int i = 0; i < n; i++)
		printf("%d\t", list[i]);
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
//int sorted[8];
void merge(int list[], int sorted[], int left, int mid, int right) {
	int i = left;	//정렬된 왼쪽 리스트에 대한 인덱스
	int j = mid + 1;	//정렬된 오른쪽 리스트에 대한 인덱스
	int k = left;	//정렬될 리스트에 대한 인덱스

	// 분리한 배열들 크기 비교 후 sorted에 삽입
	while (i <= mid && j <= right) {
		if (list[i] < list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}

	// 남은 값들 일괄 복사
	if (i > mid) {
		for (int l = j; l <= right; l++)
			sorted[k++] = list[l];
	}
	else {
		for (int l = i; l <= mid; l++)
			sorted[k++] = list[l];
	}

	// list 로 재복사
	for (int l = left; l <= right; l++) {
		list[l] = sorted[l];
	}
}
void merge_sort(int list[], int sorted[], int left, int right) {
	int mid;

	if (left < right) {
		mid = (left + right) / 2;

		merge_sort(list, sorted, left, mid);	// 왼쪽 정렬 전부 분해 후
		merge_sort(list, sorted, mid + 1, right);	// 오른쪽 정렬 전부 분해
		merge(list, sorted, left, mid, right);		// 가장 나중에 실행됨(배열 전부 분해된 후)
	}
}
int main(void) {
	int list[8] = { 21, 10, 12, 20, 25, 13, 15, 22 };
	int* sorted = (int*)malloc(8 * sizeof(int));
	merge_sort(list, sorted, 0, 7);

	for (int i = 0; i < 8; i++) {
		printf("%d\t", list[i]);
	}
	return 0;
}
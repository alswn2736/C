#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int partition(int list[], int left, int right) {
    int pivot = list[left];
    int low = left;
    int high = right + 1;

    do { 
        do { 
            low++;
        } while (low <= right && list[low] < pivot);

        do { 
            high--;
        } while (high >= left && list[high] > pivot);

        if (low < high) { 
            swap(&list[low], &list[high]);
        }
    } while (low < high);

    swap(&list[left], &list[high]);

    return high;
}

void quick_sort(int list[], int left, int right) {
    if (left < right) {
        int q = partition(list, left, right);

        quick_sort(list, left, q - 1);
        quick_sort(list, q + 1, right);
    }
}
int main(void) {
	int n;
	scanf("%d", &n);

	srand(time(NULL));
	int* list = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        list[i] = rand() % 100;
    quick_sort(list, 0, n - 1);


    for (int i = 0; i < n; i++)
        printf("%d\t", list[i]);

    return 0;
}
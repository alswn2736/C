#include <stdio.h>
#include <stdlib.h>

// 피벗기준 리스트 숫자 정렬
void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// 피벗 기준 리스트 숫자 정렬
int partition(int list[], int left, int right) {
    int pivot = list[left]; // 정렬할 리스트의 가장 왼쪽 데이터를 피벗으로 선택(임의의 값을 피벗으로 선택)
    int low = left;
    int high = right + 1;

    do { // low와 high가 교차할 때까지 반복(low < high)
        do { // list[low]가 피벗보다 작으면 계속 low 증가
            low++;
        } while (low <= right && list[low] < pivot);

        do { // list[high]가 피벗보다 크면 계속 high를 감소
            high--;
        } while (high >= left && list[high] > pivot);

        if (low < high) { // 만약 low와 high가 교차하지 않았으면 list[low]와 list[high] 교환
            swap(&list[low], &list[high]);
        }
    } while (low < high);

    swap(&list[left], &list[high]); // low와 high가 교차했으면 반복문을 빠져나와 list[left]와 list[high]를 교환

    return high;
}

// 퀵 정렬
void quick_sort(int list[], int left, int right) {
    // 리스트 원소가 2개 이상이면
    if (left < right) {
        int q = partition(list, left, right);

        quick_sort(list, left, q - 1);
        quick_sort(list, q + 1, right);
    }
}

int main(void) {
    int list[9] = { 5, 3, 8, 4, 9, 1, 6, 2, 7 };

    quick_sort(list, 0, 8);

    for (int i = 0; i < 9; i++)
        printf("%d\t", list[i]);

    return 0;
}

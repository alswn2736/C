#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

typedef struct {
	int key;	// 히프의 요소(노드값)
} element;

typedef struct {
	element heap[MAX_ELEMENT];	// 배열로 구현
	int heap_size;	// 히프 안에 저장된 요소 개수(최대 인덱스)
} HeapType;

HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h) {
	h->heap_size = 0;
}

// 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입한다.
// 삽입 함수
void insert_max_heap(HeapType* h, element item) {
	int i = ++(h->heap_size);

	while ((i != 1) && item.key > h->heap[i / 2].key) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}	// item 키가 heap[i / 2]보다 커지면 빠져나옴
	h->heap[i] = item;	// 새로운 노드 삽입
}

element delete_max_heap(HeapType* h) {
	int parent, child;
	element item, temp;		// item 노드를 루트에 할당시켜 삭제해야 함

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];	// 루트를 삭제시키면 말단 temp를 사장으로 승진
	parent = 1, child = 2;

	while (child <= h->heap_size) {
		// 현재 노드의 자식 노드 중 더 큰 자식 노드를 찾는다.
		if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key))	// 자식 노드 중 왼쪽 노드가 오른쪽 노드보다 작으면
			child++;
		if (temp.key >= h->heap[child].key) break;	// child가 가리키는 노드가 말단 노드보다 작아지게 되면 반복문 탈출
		// 한 단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

int main(void) {
	element e1 = { 10 }, e2 = { 5 }, e3 = { 30 };
	element e4, e5, e6;
	HeapType* heap;

	heap = create();
	init(heap);

	// 삽입
	insert_max_heap(heap, e1);
	insert_max_heap(heap, e2);
	insert_max_heap(heap, e3);

	// 삭제
	e4 = delete_max_heap(heap);
	printf("< %d > ", e4.key);
	e5 = delete_max_heap(heap);
	printf("< %d > ", e5.key);
	e6 = delete_max_heap(heap);
	printf("< %d > ", e6.key);

	free(heap);
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
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

void preorder(HeapType* h, int root) {
	if(root <= h->heap_size){
		printf("%d\t", h->heap[root].key);
		preorder(h, root * 2);
		preorder(h, root * 2 + 1);
	}
}

void print_heap(HeapType* h) {
	int level = 0;
	int count = 1;
	int idx = 1;

	while (idx <= h->heap_size) {
		for (int i = 0; i < count && idx <= h->heap_size; i++) {
			printf("%d ", h->heap[idx++].key);
		}
		printf("\n");

		level++;
		count *= 2;
	}
}

int find(HeapType* h, int root, int key) {
	int level = 0;
	int count = 1;
	int idx = 1;

	while (idx <= h->heap_size) {
		for (int i = 0; i < count && idx <= h->heap_size; i++,idx++) {
			if (key == h->heap[idx].key) {
				return idx;
			}
		}
		level++;
		count *= 2;
	}
	return 0;
}

void print_sorted_value(HeapType* h) {
	HeapType* temp = (HeapType*)malloc(sizeof(HeapType));
	temp->heap_size = h->heap_size;

	for (int i = 1; i <= h->heap_size; i++) {
		temp->heap[i] = h->heap[i];
	}

	while (temp->heap_size > 0) {
		element del = delete_max_heap(temp);
		printf("%d ", del.key);
	}
	printf("\n");

	free(temp);

}

void modify_priority(HeapType* h, int oldkey, int newkey) {
	int idx = 0;

	for (int i = 1; i <= h->heap_size; i++) {
		if (h->heap[i].key == oldkey) {
			idx = i;
			break;
		}
	}

	if (idx == 0) return; // oldkey를 찾을 수 없으면 종료

	h->heap[idx].key = newkey;
	while (idx > 1 && h->heap[idx].key > h->heap[idx / 2].key) {
		element temp = h->heap[idx];
		h->heap[idx] = h->heap[idx / 2];
		h->heap[idx / 2] = temp;
		idx /= 2;
	}

	if (h->heap[idx].key < newkey) {
		h->heap[idx].key = newkey;
		return;
	}

	int parent = idx, child = 2 * parent;

	while (child <= h->heap_size) {
		if (child + 1 <= h->heap_size && h->heap[child].key < h->heap[child + 1].key) {
			child++;
		}
		if (h->heap[parent].key > h->heap[child].key) break;

		element temp = h->heap[parent];
		h->heap[parent] = h->heap[child];
		h->heap[child] = temp;

		parent = child;
		child = 2 * parent;
	}

}


int main(void) {
	element e1 = { 10 }, e2 = { 5 }, e3 = { 30 }, eA = { 9 }, eB = { 19 }, eC = { 39 };
	element e4, e5, e6;
	int index;
	int key, oldKey, newKey;
	HeapType heap; // 히프 생성
	init(&heap); // 초기화

	printf("Step1: 삽입된 10, 5, 30 에 추가적으로 9, 19, 39 를 <삽입> 한다");
	insert_max_heap(&heap, e1);
	insert_max_heap(&heap, e2);
	insert_max_heap(&heap, e3);
	insert_max_heap(&heap, eA);
	insert_max_heap(&heap, eB);
	insert_max_heap(&heap, eC);

	printf("\nStep2: preorder, print_heap 함수 테스트\n");
	preorder(&heap, 1);
	printf("\n\n");
	print_heap(&heap);

	e4 = delete_max_heap(&heap);
	printf("\n 삭제: 루트가 삭제됨\n", e4.key);
	print_heap(&heap);

	printf("\nStep3: find 함수 테스트\n");
	printf("찾을 key 입력(-1 for exit):");
	scanf("%d", &key);
	while (key != -1) {
		if ((index = find(&heap, 1, key)) == 0)
			printf("%d 는 없음\n", key);
		else
			printf("%d 은 [%d]에 있음\n", key, index);
		printf("찾을 key 입력(-1 for exit):");
		scanf("%d", &key);
	}

	printf("\nStep4: print_sorted_value 함수 테스트\n");
	print_sorted_value(&heap);

	printf("\nStep5: modify_priority 함수 테스트\n");
	printf("바꿀 key 입력(-1 for exit):");
	scanf("%d", &oldKey);
	while (oldKey != -1) {
		printf("새 key 입력:");
		scanf("%d", &newKey);
		modify_priority(&heap, oldKey, newKey);
		print_heap(&heap);
		printf("바꿀 key 입력(-1 for exit):");
		scanf("%d", &oldKey);
	}

}
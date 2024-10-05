#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DListNode {
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
} DListNode;

// 이중 연결 리스트 초기화
void init(DListNode* phead) {
	phead->llink = phead;
	phead->rlink = phead;
}

// 이중 연결 리스트의 노드를 출력
void print_dlist(DListNode* phead) {
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink)
		printf("<-| |%d| |-> ", p->data);

	printf("\n");
}

// 새로운 데이터를 노드 before의 오른쪽에 삽입
void dinsert(DListNode* before, element data) {
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));

	newnode->data = data;
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}

// 노드 removed 삭제
void ddelete(DListNode* head, DListNode* removed) {
	if (removed == head) return;

	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}

// 역순 순회 출력
void print_reverse_dlist(DListNode* head) {
	DListNode* p;

	for (p = head->llink; p != head; p = p->llink)
		printf("<-| |%d| |-> ", p->data);

	printf("\n");
}

// data를 갖는 노드 반환
DListNode* search(DListNode* head, element data) {
	DListNode* p;

	for (p = head->rlink; p != head; p = p->rlink) {
		if (p->data == data) {
			printf("해당 데이터인 %d은 리스트 안에 존재합니다.\n", p->data);
			return p;
		}
	}
	printf("해당 데이터는 리스트 안에 존재하지 않습니다.\n");
	return NULL;
}

// 이중 연결 리스트 테스트 프로그램
int main(void) {
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	init(head);
	printf("추가 단계\n");

	// 맨 앞에 노드 삽입
	dinsert(head, 10);
	print_dlist(head);
	dinsert(head, 20);
	print_dlist(head);
	dinsert(head, 30);
	print_dlist(head);

	printf("\n역순 출력\n");
	print_reverse_dlist(head);

	int d;
	printf("\n찾고자 하는 data를 입력하세요: ");
	scanf("%d", &d);
	search(head, d);

	printf("\n삭제 단계\n");
	ddelete(head, head->rlink);
	print_dlist(head);

	free(head);
	return 0;
}
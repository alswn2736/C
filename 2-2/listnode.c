#include <stdio.h>
#include <stdlib.h>

typedef int element;	// 자료형으로 저장 시 모든 변수를 일일이 수정해야 함... but element 타입으로 저장하면 처음 지정한 변수형만 바꾸면 됨
typedef struct ListNode {
	element data;	// 데이터 저장
	struct ListNode* link;	// 다음 노드의 주소를 가리키는 포인터가 저장된 필드
}ListNode;	// 노드 타입

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}	// 오류 처리 함수

ListNode* insert(ListNode* head, ListNode* pre, element value) {	// 헤드 포인터, 추가할 데이터
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link;	// p->link와 pre->link가 가리키는 다음 노드가 같음
	pre->link = p;	// 이 시점에서 p가 pre 뒤로 삽입
	
	return head;
}	// 노드 pre 뒤에 새로운 노드 삽입

ListNode* insert_first(ListNode* head, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));

	p->data = value;
	p->link = head;
	head = p;

	return head;
}

ListNode* insert_last(ListNode* head, element value) {
	ListNode* temp = head;
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	
	p->data = value;
	p->link = NULL;

	if (head == NULL)
		head = p;
	else {
		while (temp->link != NULL) {
			temp = temp->link;
		}
		temp->link = p;
	}
	return head;	// 변경된 헤드 포인터 반환
}

ListNode* delete(ListNode* head, ListNode* pre) {
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);

	return head;
}	// pre가 가리키는 노드의 다음 노드를 삭제

ListNode* delete_first(ListNode* head) {
	ListNode* removed;

	if (head == NULL) error("삭제할 항목이 없음");

	removed = head;
	head = removed->link;	// head가 다음 필드로 이동
	free(removed);

	return head;
}

ListNode* delete_last(ListNode* head) {
	ListNode* temp = head;
	ListNode* prevTemp = NULL;
	ListNode* removed = NULL;
	if (head == NULL) error("삭제할 항목이 없음");
	else if (head->link == NULL) {
		removed = head;
		head = NULL;
	}
	else {
		while (temp->link != 0) {
			prevTemp = temp;
			temp = temp->link;
		}
		removed = temp;
		prevTemp->link = NULL;
	}
	free(removed);
	return head;
}
}

void print_list(ListNode* head) {
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("NULL \n");
}

ListNode* search(ListNode* head, element x) {
	ListNode* p = head;

	while (p != NULL) {
		if (p->data == x)
			return p;
	}
	return NULL;
}	// 노드값 탐색 연산

ListNode* concat(ListNode* head1, ListNode* head2) {
	ListNode* p;

	if (head1 == NULL)
		return head2;
	else if (head2 == NULL)
		return head1;
	else {
		p = head1;
		while (p->link != NULL)
			p = p->link;
		p->link = head2;	// 두 연결리스트 합침
		return head1;
	}
}

ListNode* reverse(ListNode* head) {
	ListNode* p, * q, * r;	// 순회 포인터로 p, q, r 사용

	p = head;	// p는 역순으로 만들 리스트
	q = NULL;	// q는 역순으로 만들 노드
	
	while (p != NULL) {
		r = q;	//r은 역순으로 된 리스트
				// r은 q, q는 p를 차례로 따라감
		q = p;
		p = p->link;
		q->link = r;	// q의 링크 방향을 바꿈
	}
	return q;
}

int main(void) {
	ListNode* head1 = NULL, * head2;
	
	for (int i = 0; i < 5; i++) {
		head1 = insert_last(head1, i * 10);
		print_list(head1);
	}

	head2 = reverse(head1);
	print_list(head2);
	head2 = insert(head2, 1, 99);
	print_list(head2);

	head2 = delete_last(head2);
	print_list(head2);

	head1 = NULL;
	head1 = insert_first(head1, 100);
	head1 = insert_first(head1, 200);
	print_list(head1);

	head1 = concat(head1, head2);
	print_list(head1);
}
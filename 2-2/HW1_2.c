#define _CRT_SECURE_NO_WARNINGS
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

int is_in_list(ListNode* head, element item) {
	for (ListNode* p = head; p != NULL; p = p->link) {
		if (p->data == item)
			return 1;
	}
	return 0;
}

int get_length(ListNode* head) {
	int len = 1;
	for (ListNode* p = head; p->link != NULL; p = p->link)
		len++;

	return len;
}

int get_total(ListNode* head) {
	int total = 0;
	for (ListNode* p = head; p != NULL; p = p->link) {
		total += p->data;
	}
	return total;
}

element get_entry(ListNode* head, int pos) {
	ListNode* p = head;
	for (int i = 0; i < pos; i++)
		p = p->link;

	return p->data;
}

ListNode* delete_by_key(ListNode* head, int key) {
	ListNode* temp = head;
	ListNode* prevTemp = NULL;
	if (head->data == key)
		head = delete_first(head);
	else {
		while (temp != NULL) {
			if (temp->data == key) {
				prevTemp->link = temp->link;
				temp->link = NULL;
				free(temp);
				return head;
			}
			prevTemp = temp;
			temp = temp->link;
		}
	}
	return head;
}

ListNode* insert_pos(ListNode* head, int pos, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	ListNode* temp = head;
	ListNode* prevTemp = NULL;

	p->data = value;
	if (pos == 0)
		head = insert_first(head, value);
	else {
		for (int i = 0; i < pos; i++) {
			prevTemp = temp;
			temp = temp->link;
		}
		p->link = temp;
		prevTemp->link = p;
	}
	return head;
}

ListNode* delete_pos(ListNode* head, int pos) {
	ListNode* temp = head;
	ListNode* prevTemp = NULL;

	if (pos == 0)
		head = delete_first(head);
	for (int i = 0; i < pos; i++) {
		prevTemp = temp;
		temp = temp->link;
	}
	prevTemp->link = temp->link;
	temp->link = NULL;
	free(temp);
	return head;
}
int main(void) {
	ListNode* list1 = NULL, * list2 = NULL;
	ListNode* list3;

	list1 = insert_first(list1, 10);
	list1 = insert_first(list1, 20);
	list1 = insert_first(list1, 30);
	printf("list1 = ");
	print_list(list1);

	list1 = delete_first(list1);
	printf("list1 = ");
	print_list(list1);

	list2 = insert_last(list2, 11);
	list2 = insert_last(list2, 22);
	list2 = insert_last(list2, 33);
	list2 = insert_last(list2, 44);
	printf("list2 = ");
	print_list(list2);

	list2 = delete_last(list2);
	printf("list2 = ");
	print_list(list2);

	list3 = reverse(list2);
	printf("list3 = ");
	print_list(list3);

	list1 = concat(list1, list3);
	printf("list1 = ");
	print_list(list1);

	// 여기서부터는 새로 만든 함수

	int s;
	printf("찾으려 하는 숫자를 입력하시오: ");
	scanf("%d", &s);

	if (is_in_list(list1, s))
		printf("%d는 리스트 안에 있습니다.\n");
	else
		printf("%d는 리스트 안에 없습니다.\n");

	printf("리스트에 존재하는 노드의 수는 %d개 입니다.\n", get_length(list1));

	printf("리스트에 존재하는 모든 데이터 합은 %d 입니다.\n", get_total(list1));

	int p;
	printf("찾으려 하는 데이터의 위치를 입력하시오: ");
	scanf("%d", &p);
	printf("해당 위치에 있는 데이터는 %d 입니다.\n", get_entry(list1, p));

	int d;
	printf("지우려 하는 데이터를 입력하시오: ");
	scanf("%d", &d);
	delete_by_key(list1, d);
	printf("list1 : ");
	print_list(list1);

	int a;
	printf("추가하고자 하는 위치를 입력하시오: ");
	scanf("%d", &a);
	insert_pos(list1, a, 30);
	printf("list1 = ");
	print_list(list1);

	int e;
	printf("삭제하고자 하는 위치를 입력하시오: ");
	scanf("%d", &e);
	delete_pos(list1, e);
	printf("list1 = ");
	print_list(list1);
}

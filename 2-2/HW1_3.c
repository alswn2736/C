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

void display(ListNode* head) {
	printf("<");
	for (ListNode* p = head; p != NULL; p = p->link)
		printf(" %d", p->data);
	printf(" >\n");
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

	if (head != NULL && head->data == key) {
		temp = head;
		head = head->link;
		return head;
	}

	while (temp != NULL) {
		if (temp->data == key) {
			prevTemp->link = temp->link;
			return head;
		}
		prevTemp = temp;
		temp = temp->link;
	}
	printf("아이템 %d는 보유하고 있지 않습니다.\n", key);
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

ListNode* add_item(ListNode* head, element new_item) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	int total = 0;
	p->data = new_item;
	p->link = NULL;

	ListNode* temp = head;
	while (temp != NULL) {
		total += temp->data;
		temp = temp->link;
	}
	total += new_item;

	if (total > 100) {
		printf("최대 무게(100kg) 초과로 아이템 %d를 추가할 수 없음\n", new_item);
		return head;
	}

	p->link = head;
	head = p;

	return head;
}


int main(void) {
	ListNode* list = NULL;
	char answer;
	int weight;

	do {
		printf("enter a(dd), d(elete) or q(uit): ");
		scanf("%c", &answer);

		if (answer == 'a') {
			printf("enter the weight of the item: ");
			scanf("%d", &weight);
			list = add_item(list, weight);
			display(list);
		}
		else if (answer == 'd') {
			printf("enter the weight of the item: ");
			scanf("%d", &weight);
			list = delete_by_key(list, weight);
			display(list);
		}
	} while (answer != 'q');
	
}

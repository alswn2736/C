#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct ListNode{
	element data;
	struct ListNode* link;
} ListNode;
void print_list(ListNode* head){
	ListNode* p;
	if (head == NULL)
		return;
	p = head->link;

	while (p != head) {
		printf("%d->", p->data);
		p = p->link;
	}
	printf("%d->", p->data);
	printf("\n");
}
ListNode* insert_first(ListNode* head, element data) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;

	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link;
		head->link = node;
	}
	return head;
}

ListNode* insert_last(ListNode* head, element data){
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;

	if (head == NULL) {
		head = node;
		node->link = head;  
	}
	else {
		node->link = head->link;
		head->link = node;
		head = node;
	}
	return head;
}

ListNode* delete_first(ListNode* head){
	ListNode* temp;

	if (head == NULL) {
		printf("리스트가 비어 삭제를 못함\n");
		return NULL;
	}
	else {
		temp = head->link;
		head->link = temp->link;
		free(temp);
	}
	return head;
}

ListNode* delete_last(ListNode* head){
	ListNode* temp;
	ListNode* p = head->link;

	if (head == NULL) {
		printf("리스트가 비어 삭제를 못함\n");
		return NULL;
	}
	else {
		temp = head;
		while (p->link != head)
			p = p->link;
		p->link = head->link;
		head = p;
		free(temp);
	}
	return head;
}

ListNode* search(ListNode* head, element data){
	ListNode* p;

	if (head == NULL) {
		printf("리스트가 비어 있어 찾는 데이터 없음\n");
		return NULL;
	}
	p = head;

	do {
		if (p->data == data)
			return p;
		p = p->link;
	} while (p != head);

	return NULL;
}

int get_size(ListNode* head){
	ListNode* p = head->link;
	int count = 0;
	
	if (head == NULL) {
		printf("리스트가 비어 있어 반환할 수 없음\n");
		return 0;
	}
	do {
		p = p->link;
		count++;
	} while (p != head->link);

	return count;
}
int main(void){
	ListNode* head = NULL;
	
	head = insert_last(head, 20); 
	print_list(head);
	head = insert_last(head, 30); 
	print_list(head);
	head = insert_last(head, 40);
	print_list(head);
	head = insert_first(head, 10); 
	print_list(head);

	head = delete_first(head); 
	print_list(head);

	int s;
	printf("검색하고 싶은 데이터를 입력하시오: ");
	scanf("%d", &s);

	ListNode* p = search(head, s);
	if (p == NULL)
		printf("data 없음\n");
	else
		printf("data 있음\n");
	printf("list size: %d\n", get_size(head));

	return 0;
}
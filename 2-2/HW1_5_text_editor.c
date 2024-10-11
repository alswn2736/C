#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_CHAR_PER_LINE 100

typedef struct {
	char line[MAX_CHAR_PER_LINE];
}element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// a
ListNode* insert_last(ListNode* head, element value) {
	ListNode* temp = head;
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));

	p->data = value;
	p->link = NULL;

	if (head == NULL)
		head = p;
	else {
		while (temp->link != NULL)
			temp = temp->link;
		temp->link = p;
	}
	return head;
}

// i
ListNode* insert_first(ListNode* head, element value) {
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));

	temp->data = value;
	temp->link = head;
	head = temp;

	return head;
}

ListNode* insert(ListNode* head, int pos, element value) {
	if (pos == 1)
		head = insert_first(head, value);
	else {
		ListNode* p = (ListNode*)malloc(sizeof(ListNode));
		ListNode* temp = head;
		ListNode* prevTemp = NULL;
		p->data = value;
		
		for (int i = 0; i < pos - 1; i++) {
			prevTemp = temp;
			temp = temp->link;
		}
		p->link = temp;
		prevTemp->link = p;
	}
	return head;
}

// d
ListNode* delete_first(ListNode* head) {
	ListNode* removed;

	if (head == NULL) error("삭제할 항목이 없음");

	removed = head;
	head = removed->link;
	free(removed);

	return head;
}

ListNode* delete(ListNode* head, int pos) {
	if (pos == 1)
		head = delete_first(head);
	else {
		ListNode* temp = head;
		ListNode* prevTemp = NULL;
		for (int i = 0; i < pos - 1; i++) {
			prevTemp = temp;
			temp = temp->link;
		}
		prevTemp->link = temp->link;
		temp->link = NULL;
		free(temp);
		return head;
	}
}

//v
void display_line(ListNode* head, int line) {
	ListNode* temp = head;

	for (int i = 1; temp != NULL; temp = temp->link, i++) {
		if (i == line) {
			printf("(%d) %s", i, temp->data.line);
			break;
		}
	}
}

void display(ListNode* head) {
	ListNode* temp = head;

	printf("----------text edited--------- \n");
	for (int i = 1; temp != NULL; temp = temp->link)
		printf("(%d) %s", i++, temp->data.line);
}

char askChoice(void) {
	char choice;
	printf("------------------------------\n");
	printf("a: 텍스트 끝에 라인 추가\n");
	printf("i: 라인 번호로 라인 추가\n");
	printf("d: 라인 번호로 라인 삭제\n");
	printf("v: 라인 번호로 해당 라인 출력\n");
	printf("p: 전체 텍스트 출력\n");
	printf("q: 끝\n");

	printf("메뉴 선택:");
	scanf(" %c", &choice);
	return choice;
}

int main(void) {
	ListNode* list = NULL;
	char choice;
	int lineNb;
	element newElement;

	while ((choice = askChoice()) != 'q') {
		switch(choice) {
			case 'a':
				printf("텍스트 끝에 삽입할 라인: ");
				while (getchar() != '\n');
				fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);
				list = insert_last(list, newElement);
				display(list);
				break;
			case 'i':
				printf("삽입할 라인 번호: ");
				scanf("%d", &lineNb);

				printf("삽입할 라인: ");
				while (getchar() != '\n');
				fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);
				list = insert(list, lineNb, newElement);
				display(list);
				break;

			case 'd': 
				printf("삭제할 라인 번호: ");
				scanf("%d", &lineNb);
				list = delete(list, lineNb);
				display(list);
				break;

			case 'v':
				printf("출력할 라인 번호: ");
				scanf("%d", &lineNb);
				display_line(list, lineNb);

				break;

			case 'p':
				display(list);
				break;
		}
	}
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 3
#define MAX_NAME_SIZE 100

typedef struct {
	char name[MAX_NAME_SIZE];
} element;

typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
} Queue;

void error(char* message){
	fprintf(stderr, "%s\n", message);
}

void init(Queue* q){
	q->front = q->rear = 0;
}

int is_empty(Queue* q){
	return (q->front == q->rear);
}

int is_full(Queue* q){
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(Queue* q, char* name){
	element item;
	strcpy(item.name, name);

	if (is_full(q))
		error("아직 대상자가 없습니다. 대기자가 꽉 찼으니 담기회를 이용");
	else {
		q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
		q->queue[q->rear] = item;
	}
}

element dequeue(Queue* q){
	if (is_empty(q))
		error("큐가 공백상태입니다.\n");
	else {
		q->front = (q->front + 1) % MAX_QUEUE_SIZE;
		return q->queue[q->front];
	}
}

element peek(Queue* q){
	if (is_empty(q))
		error("큐가 공백상태입니다.\n");
	return q->queue[(q->front + 1) % MAX_QUEUE_SIZE];
}

int get_count(Queue* q){
	if (is_empty(q))
		return 0;
	else if (is_full(q))
		return MAX_QUEUE_SIZE - 1;
	else
		return (q->rear) - (q->front);
}

void print_queue(Queue* q){
	int size = get_count(q);
	int index = (q->front + 1) % MAX_QUEUE_SIZE;

	for (int i = 0; i < size; i++) {
		printf("%s ", q->queue[index].name);
		index = (index + 1) % MAX_QUEUE_SIZE;
	}
	printf("\n");
}

void match(Queue* mq, Queue* fq){
	if (!is_empty(mq) && !is_empty(fq)) {
		printf("커플이 탄생했습니다! %s과 %s\n", mq->queue[mq->front + 1].name, fq->queue[fq->front + 1].name);
		dequeue(mq);
		dequeue(fq);
	}
	else if (is_empty(mq) || is_empty(fq))
		printf("아직 대상자가 없습니다. 기다려주십시오. \n");
}
int main(void){
	Queue m, f;
	element name[MAX_NAME_SIZE] = { 0 };
	char answer, sex;

	init(&m);
	init(&f);

	printf("미팅 주선 프로그램 입니다\n");

	while (1) {
		printf("i(nsert, 고객입력), c(heck, 대기자 체크), q(uit): ");
		scanf("%c", &answer);

		if(answer == 'i'){
			printf("이름을 입력: ");
			scanf("%s", name);
			getchar();
			printf("성별을 입력(m or f): ");
			scanf("%c", &sex);

			if (sex == 'm') {
				enqueue(&m, name);
				if (!is_full(&m))
					match(&m, &f);
			}
			else if (sex == 'f') {
				enqueue(&f, name);
				if (!is_full(&f))
					match(&m, &f);
			}
		}
		else if(answer == 'c'){
			printf("남성 대기자 %d명: ", get_count(&m));
			print_queue(&m);
			printf("여성 대기자 %d명: ", get_count(&f));
			print_queue(&f);
		}
		else if(answer == 'q')
			return 0;
		getchar();
	}
}
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

typedef int element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void error(char* message) {
	printf(stderr, "%s\n", message);
	exit(1);
}	// 오류 함수

void init(QueueType* q) {
	q->front = q->rear = 0;
}	// 초기화 함수

int is_empty(QueueType* q) {
	return(q->front == q->rear);
}	// 공백 상태 검출 함수

int is_full(QueueType* q) {
	return((q->front + 1) % MAX_QUEUE_SIZE == q->rear);
}	// 포화 상태 검출 함수

void enqueue(QueueType* q, element item) {
	if (is_full(q))
		error("큐가 포화상태입니다.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;	// rear 값 증가
	q->data[q->rear] = item;	// item 삽입
}	// 삽입 함수

element dequeue(QueueType* q) {
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}	// 삭제 함수

element peek(QueueType* q) {
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}	// 엿보기 함수

int main(void) {
	QueueType q;

	init(&q);
	printf("front = %d rear = %d\n", q.front, q.rear);
	enqueue(&q, 1);
	enqueue(&q, 2);
	enqueue(&q, 3);
	printf("deqeue() = %d\n", dequeue(&q));
	printf("deqeue() = %d\n", dequeue(&q));
	printf("deqeue() = %d\n", dequeue(&q));
	printf("front = %d rear = %d\n", q.front, q.rear);
}
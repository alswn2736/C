#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICS 50

typedef int element;
typedef struct GraphNode {
	int vertex;	// 무슨 정점인지
	struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
	int n;	// 정점의 개수
	GraphNode* adj_list[MAX_VERTICS];
} GraphType;

// 그래프 초기화
void init(GraphType* g) {
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICS; v++)
		g->adj_list[v] = NULL;
}

// 정점 삽입 연산
void insert_vertex(GraphType* g, int v) {
	if (((g->n) + 1 > MAX_VERTICS)) {	// 50개보다 정점이 많아지면
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}	// 프로그램 종료
	// 프로그램 종료될 이유가 없다면(정상 작동)
	g->n++;
}

// 간선 삽입 연산, v를 u의 인접 리스트에 삽입함
void insert_edge(GraphType* g, int u, int v) {
	GraphNode* node;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	// 프로그램 종료될 이유가 없다면(정상 작동)
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

void print_adj_list(GraphType* g) {
	for (int i = 0; i < g->n; i++) {
		GraphNode* p = g->adj_list[i];
		printf("정점 %d의 인접 리스트 ", i);
		while (p != NULL) {
			printf("-> %d ", p->vertex);
			p = p->link;
		}
		printf("\n");
	}
}

GraphNode* remove_node(GraphNode* head, element item) {
	GraphNode* p, * prevp;

	if (head == NULL) printf("리스트는 비어있습니다.\n");
	else if (head->vertex == item) {
		p = head;
		head = head->link;
		free(p);
	}
	else {
		p = head;
		do {
			prevp = p;
			p = p->link;
		} while (p != NULL && p->vertex != item);
		if (p != NULL) {
			prevp->link = p->link;
			free(p);
		}
		else
			printf("%d은 리스트에 없음\n", item);
	}
	return head;
}

void delete_edge(GraphType* g, int u, int v) {
	GraphNode* node;
	if (u >= g->n || v >= g->n) {		// 간선 위치가 행렬 번호보다 커지면
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}	// 프로그램 종료
	g->adj_list[u] = remove_node(g->adj_list[u], v);
	g->adj_list[v] = remove_node(g->adj_list[v], u);
}
void read_graph(GraphType* g, char* filename) {
	int number, u, v;
	GraphNode* node;
	FILE* fp;
	fp = fopen(filename, "rt");

	if (fp == NULL) {
		printf("file open error!\n");
		return;
	}
	fscanf(fp, "%d", &number);
	g->n = number;
	while (fscanf(fp, "%d %d", &u, &v) != EOF)
		insert_edge(g, u, v);
}

void write_graph(GraphType* g, char* filename) {
	int u;
	GraphNode* ptr;
	FILE* fp;

	if (filename == NULL) fp = stdout;
	else {
		fp = fopen(filename, "wt");
		if (fp == NULL) {
			printf("file open error!\n");
			return;
		}
	}

	fprintf(fp, "%d\n", g->n);
	for (u = 0; u < g->n; u++) {
		ptr = g->adj_list[u];
		while (ptr != NULL) {
			if (u <= ptr->vertex)
				fprintf(fp, "%d %d\n", u, ptr->vertex);
			ptr = ptr->link;
		}
	}
	if (filename != NULL) fclose(fp);
}

int main(void) {
	GraphType g;
	init(&g);

	read_graph(&g, "input.txt");
	write_graph(&g, NULL);

	insert_edge(&g, 1, 3);
	write_graph(&g, NULL);

	insert_edge(&g, 2, 0);
	write_graph(&g, NULL);

	write_graph(&g, "output.txt");
}
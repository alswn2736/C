#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>2
#include "queue.h"

#define TRUE 1
#define FALSE 0
#define MAX_VERTICS 50

int visited[MAX_VERTICS];

typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
}GraphNode;

typedef struct GraphType {
	int n;
	GraphNode* adj_list[MAX_VERTICS];
}GraphType;

void graph_init(GraphType* g) {
	g->n = 0;
	for (int v = 0; v < MAX_VERTICS; v++)
		g->adj_list[v] = NULL;
}

void insert_vertex(GraphType* g, int v) {
	if (((g->n) + 1) > MAX_VERTICS) {
		fprintf(stderr, "그래프: 정점 개수 초과");
		return;
	}
	g->n++;
}

void insert_edge(GraphType* g, int u, int v) {
	GraphNode* node;

	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = u;
	node->link = g->adj_list[v];
	g->adj_list[v] = node;

	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

void bfs_list(GraphType* g, int v) {
	GraphNode* w;
	QueueType q;
	init(&q);
	visited[v] = TRUE;
	//printf("%d ", v);
	enqueue(&q, v);

	while (!is_empty(&q)) {
		v = dequeue(&q);
		for (w = g->adj_list[v]; w; w = w->link) {
			if (!visited[w->vertex]) {
				visited[w->vertex] = TRUE;
				printf("(%d %d)\n", v, w->vertex);
				enqueue(&q, w->vertex);
			}
		}
	}
}

void read_graph(GraphType* g, char* filename) {
	int number, u, v;
	FILE* fp;
	fp = fopen(filename, "rt");

	if (fp == NULL) {
		printf("file %s open error!\n", filename);
		return;
	}

	fscanf(fp, "%d", &number);
	g->n = number;

	while (fscanf(fp, "%d %d", &u, &v) != EOF) {
		insert_edge(g, u, v);
	}
	fclose(fp);
}

int main(void) {
	GraphType g;
	graph_init(&g);
	read_graph(&g, "input.txt");

	int vertex;
	printf("Enter 정점: ");
	scanf("%d", &vertex);

	bfs_list(&g, vertex);

	return 0;
}
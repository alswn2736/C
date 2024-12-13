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
}

void dfs_list(GraphType* g, int v) {
	GraphNode* w;
	visited[v] = TRUE;
	printf("%d ", v);

	for (w = g->adj_list[v]; w; w = w->link) {
		if (!visited[w->vertex])
			dfs_list(g, w->vertex);
	}
}

void bfs_list(GraphType* g, int v) {
	GraphNode* w;
	QueueType q;
	init(&q);
	visited[v] = TRUE;
	printf("%d ",v);
	enqueue(&q, v);

	while (!is_empty(&q)) {
		v = dequeue(&q);
		for (w = g->adj_list[v]; w; w = w->link) {
			if (!visited[w->vertex]) {
				visited[w->vertex] = TRUE;
				printf("%d ", w->vertex);
				enqueue(&q, w->vertex);
			}
		}
	}
}

void visited_init() {
	for (int i = 0; i < MAX_VERTICS; i++)
		visited[i] = 0;
}

int main(void) {
	GraphType g;
	graph_init(&g);

	insert_vertex(&g, 0);
	insert_vertex(&g, 1);
	insert_vertex(&g, 2);
	insert_vertex(&g, 3);


	insert_edge(&g, 0, 1);
	insert_edge(&g, 1, 2);
	insert_edge(&g, 2, 3);
	insert_edge(&g, 3, 0);
	insert_edge(&g, 0, 2);


	printf("\n 깊이 우선 탐색\n");
	dfs_list(&g, 0); printf("\n");

	visited_init();
	dfs_list(&g, 1); printf("\n");

	visited_init();
	dfs_list(&g, 2); printf("\n");

	visited_init();
	dfs_list(&g, 3); printf("\n");

	printf("\n 넓이 우선 탐색\n");

	visited_init();
	bfs_list(&g, 0); printf("\n");

	visited_init();
	bfs_list(&g, 1); printf("\n");

	visited_init();
	bfs_list(&g, 2); printf("\n");

	visited_init();
	bfs_list(&g, 3); printf("\n");

	return 0;
}
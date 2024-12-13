#include <stdio.h>
#include "queue.h"

#define MAX_VERTICS 50
#define TRUE 1
#define FALSE 0

int visited[MAX_VERTICS];
typedef struct GraphType {
	int n;
	int adj_mat[MAX_VERTICS][MAX_VERTICS];
} GraphType;

void graph_init(GraphType* g) {
	int r, c;
	g->n = 0;

	for (r = 0; r < MAX_VERTICS; r++) {
		for (c = 0; c < MAX_VERTICS; c++)
			g->adj_mat[r][c] = 0;
	}
}

void insert_edge(GraphType* g, int start, int end) {
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프:  정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

void insert_vertex(GraphType* g, int v) {
	if (((g->n) + 1) > MAX_VERTICS){
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

void dfs_mat(GraphType* g, int v) {
	visited[v] = TRUE;
	printf("%d ", v);

	for (int w = 0; w < g->n; w++) {
		if (g->adj_mat[v][w] && !visited[w])
			dfs_mat(g, w);
	}
}

void bfs_mat(GraphType* g, int v) {
	QueueType q;
	init(&q);
	visited[v] = TRUE;
	printf("%d ", v);
	enqueue(&q, v);

	while (!is_empty(&q)) {
		v = dequeue(&q);
		for (int w = 0; w < g->n; w++) {
			if (g->adj_mat[v][w] && !visited[w]) {
				visited[w] = TRUE;
				printf("%d ", w);
				enqueue(&q, w);
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
	dfs_mat(&g, 0); 
	printf("\n");
	visited_init();

	dfs_mat(&g, 1); 
	printf("\n");
	visited_init();

	dfs_mat(&g, 2); 
	printf("\n");
	visited_init();

	dfs_mat(&g, 3); 
	printf("\n");
	visited_init();


	printf("\n 넓이 우선 탐색\n");
	bfs_mat(&g, 0); 
	printf("\n");
	visited_init();

	bfs_mat(&g, 1); 
	printf("\n");
	visited_init();

	bfs_mat(&g, 2); 
	printf("\n");
	visited_init();

	bfs_mat(&g, 3);
	printf("\n");

	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
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
	//printf("%d ", v);

	for (int w = 0; w < g->n; w++) {
		if (g->adj_mat[v][w] && !visited[w]) {
			printf("(%d %d)\n", v, w);
			dfs_mat(g, w);
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

	dfs_mat(&g, vertex);

	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICS 50
typedef struct GraphType {
	int n;	// 정점의 개수
	int adj_mat[MAX_VERTICS][MAX_VERTICS];	// 인접 행렬
} GraphType;

// 그래프 초기화
void init(GraphType* g) {
	int r, c;
	g->n = 0;	// 정점 0개
	for (r = 0; r < MAX_VERTICS; r++) {
		for (c = 0; c < MAX_VERTICS; c++)
			g->adj_mat[r][c] = 0;
	}
}

// 정접 삽입 연산
void insert_vertex(GraphType* g, int v) {
	if (((g->n) + 1) > MAX_VERTICS) {	// 50개보다 정점이 많아지면
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}	// 프로그램 종료
	// 프로그램 종료될 이유가 없다면(정상 작동)
	g->n++;
}

// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end) {
	if (start >= g->n || end >= g->n) {		// 간선 위치가 행렬 번호보다 커지면
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}	// 프로그램 종료
	// 프로그램 종료될 이유가 없다면(정상 작동)
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

// 인접 행렬 출력 함수
void print_adj_mat(GraphType* g) {
	for (int i = 0; i < g->n; i++) {
		for (int j = 0; j < g->n; j++)
			printf("%2d", g->adj_mat[i][j]);
		printf("\n");
	}
}

// 간선 삭제 연산
void delete_edge(GraphType* g, int start, int end) {
	if (start >= g->n || end >= g->n) {		// 간선 위치가 행렬 번호보다 커지면
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}	// 프로그램 종료
	// 프로그램 종료될 이유가 없다면(정상 작동)
	g->adj_mat[start][end] = 0;
	g->adj_mat[end][start] = 0;
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

void write_graph(GraphType* g, char* filename) {
	int i, j;
	FILE* fp;

	if (filename == NULL) fp = stdout;
	else {
		fp = fopen(filename, "wt");
		if (fp == NULL) {
			printf("file %s open error!\n", filename);
			return;
		}
	}

	fprintf(fp, "%d\n", g->n);
	for (i = 0; i < g->n; i++) {
		for (j = i; j < g->n; j++) {
			if (g->adj_mat[i][j] == 1) {
				fprintf(fp, "%d %d\n", i, j);
			}
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
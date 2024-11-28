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

int main(void) {
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);

	for (int i = 0; i < 4; i++) {
		insert_vertex(g, i);
	}

	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 2);
	insert_edge(g, 2, 3);

	print_adj_mat(g);

	free(g);
	return 0;
}
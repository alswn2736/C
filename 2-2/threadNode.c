#include <stdio.h>
#define TRUE 1
#define FALSE 0

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
	int is_thread;	// 스레드이면 TRUE
}TreeNode;

TreeNode n1 = { '1', NULL, NULL, 1 }; // 스레드
TreeNode n2 = { '2', NULL, NULL, 1 }; // 스레드
TreeNode n3 = { '3', &n1, &n2, 0 };
TreeNode n4 = { '4', NULL, NULL, 1 }; // 스레드
TreeNode n5 = { '5', NULL, NULL, 0 }; // 스레드이지만 중위 순회의 마지막 노드이므로 0으로
TreeNode n6 = { '6', &n4, &n5, 0 };
TreeNode n7 = { '7', &n3, &n6, 0 };
TreeNode* exp = &n7;

TreeNode* find_thread_successor(TreeNode* p) {
	// q는 p의 오른쪽 포인터
	TreeNode* q = p->right;

	//만약 오른쪽 포인터가 NULL이거나 스레드이면 오른쪽 포인터 반환
	if (q == NULL || p->is_thread == TRUE)
		return q;

	// 만약 오른쪽 자식이면 다시 가장 왼쪽 노드로 이동
	while (q->left != NULL)
		q = q->left;

	return q;
}

void thread_inorder(TreeNode* t) {
	TreeNode* q;
	q = t;
	while (q->left)
		q = q->left;		// 중위 순회 첫 노드(가장 왼쪽 노드)로 이동

	do {
		printf("%c->", q->data);	// 데이터 출력
		q = find_thread_successor(q);	// 후속자 함수 호출
	} while (q);	// NULL이 아니면
}

int main(void) {
	n1.right = &n3;
	n2.right = &n7;
	n4.right = &n6;

	thread_inorder(exp);
	printf("\n");

	return 0;
}
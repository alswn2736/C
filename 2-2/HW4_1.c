#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define TRUE 1
#define FALSE 0
#define MAX_TREE_SIZE 20

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

TreeNode n1 = { 15, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 15, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode* root1 = &n6;

TreeNode m1 = { 15, NULL, NULL };
TreeNode m2 = { 4, &m1, NULL };
TreeNode m3 = { 16, NULL, NULL };
TreeNode m7 = { 28, NULL, NULL };
TreeNode m4 = { 25, NULL, &m7 };
TreeNode m5 = { 15, &m3, &m4 };
TreeNode m6 = { 15, &m2, &m5 };
TreeNode* root2 = &m6;

// 중위 순회 LVR 
void inorder(TreeNode* root) {
	if (root != NULL) {
		inorder(root->left);	// 왼쪽 서브트리 순회
		printf("[%d] ", root->data);	// 노드 방문
		inorder(root->right);	// 오른쪽 서브트리 순회
	}
}

// 전위 순회 VLR
void preorder(TreeNode* root) {
	if (root != NULL) {
		printf("[%d] ", root->data);	// 노드 방문
		preorder(root->left);	// 왼쪽 서브트리 순회
		preorder(root->right);	// 오른쪽 서브트리 순회
	}
}

// 후위 순회 LRV
void postorder(TreeNode* root) {
	if (root != NULL) {
		postorder(root->left);	// 왼쪽 서브트리 순회
		postorder(root->right);	// 오른쪽 서브트리 순회
		printf("[%d] ", root->data);	// 노드 방문
	}
}

// 비단말 노드 개수 구하기
int get_nonleaf_count(TreeNode* node) {
	int count = 0;  // Initialize count to 0

	if(node != NULL){
		if (node->left != NULL || node->right != NULL) 
			count = 1;
		count += (get_nonleaf_count(node->left) + get_nonleaf_count(node->right));
	}

	return count;
}	

// 자식이 하나인 노드 개수 구하기
int get_oneleaf_count(TreeNode* node) {
	int count = 0;
	if (node != NULL) {
		if ((node->left != NULL && node->right == NULL) || (node->left == NULL && node->right != NULL))
			count = 1;
		count += (get_oneleaf_count(node->left) + get_oneleaf_count(node->right));
	}
	return count;
}

// 자식이 두 개인 노드 개수 구하기
int get_twoleaf_count(TreeNode* node) {
	int count = 0;
	if (node != NULL) {
		if (node->left != NULL && node->right != NULL)
			count = 1;
		count += (get_twoleaf_count(node->left) + get_twoleaf_count(node->right));
	}
	return count;
}

// 노드값 중 최댓값 반환
int get_max(TreeNode* node) {
	TreeNode* max = node;
	while (max->right != NULL)
		max = max->right;
	return max->data;
}

// 노드값 중 최솟값 반환
int get_min(TreeNode* node) {
	TreeNode* min = node;

	while (1) {
		if (min->data >= min->left->data)
			min = min->left;
		else
			break;
	}
	return min->data;
}

void node_increase(TreeNode* node) {
	if (node != NULL) {
		node->data += 1;
		preorder(node->left);
		preorder(node->right);
	}
}

int equal(TreeNode* n, TreeNode* m) {
	if (n != NULL || m != NULL) {
		if (n->data != m->data)
			return FALSE;
		equal(n->right, m->right);
		equal(n->left, m->left);
	}
	return TRUE;
}

TreeNode* copy(TreeNode* node) {
	TreeNode* copy = node;
	return copy;
}

int main(void) {
	TreeNode* result[MAX_TREE_SIZE];
	TreeNode* clone;
	int i, num;

	printf("가)\n");
	printf("트리 root 중 비단말노드의 개수는 %d.\n", get_nonleaf_count(root1));
	printf("트리 root2 중 비단말노드의 개수는 %d.\n", get_nonleaf_count(root2));

	printf("트리 root 중 자식이 하나만 있는 노드의 개수는 %d.\n", get_oneleaf_count(root1));
	printf("트리 root2 중 자식이 하나만 있는 노드의 개수는 %d.\n", get_oneleaf_count(root2));

	printf("트리 root 중 자식이 둘이 있는 노드의 개수는 %d.\n", get_twoleaf_count(root1));
	printf("트리 root2 중 자식이 둘이 있는 노드의 개수는 %d.\n", get_twoleaf_count(root2));

	printf("트리 root 에서 가장 큰 수는 %d.\n", get_max(root1));
	printf("트리 root2 에서 가장 큰 수는 %d.\n", get_max(root2));

	printf("트리 root 에서 가장 작은 수는 %d.\n", get_min(root1));
	printf("트리 root2 에서 가장 작은 수는 %d.\n", get_min(root2));

	printf("\n 다)\n");
	preorder(root1);
	node_increase(root1);
	printf("\n");
	preorder(root1);
	printf("\n");
	printf("%s\n", equal(root1, root1) ? "같다" : "다르다");
	printf("%s\n", equal(root2, root2) ? "같다" : "다르다");
	printf("%s\n", equal(root1, root2) ? "같다" : "다르다");
	
	printf("\n 라)\n");
	clone = copy(root1);
	preorder(root1);
	printf("\n");
	preorder(clone);
	printf("\n");

	return 0;
}
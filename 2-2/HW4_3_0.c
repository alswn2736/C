#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#define MAX_STRING 100

typedef struct {
	int id;
	char name[MAX_STRING];
	char tel[MAX_STRING];
	char dept[MAX_STRING];
} element;

typedef struct TreeNode {
	element data;
	struct TreeNode* left, * right;
}TreeNode;

TreeNode* insert_node(TreeNode* node, int id, char name[], char tel[], char dept[])
{
    if (node == NULL) {
        TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
        temp->data.id = id;
        strcpy(temp->data.name, name);
        strcpy(temp->data.tel, tel);
        strcpy(temp->data.dept, dept);
        temp->left = temp->right = NULL;
        return temp;
    }
    if (id < node->data.id)
        node->left = insert_node(node->left, id, name, tel, dept);
    else if (id > node->data.id)
        node->right = insert_node(node->right, id, name, tel, dept);

    return node;
}

TreeNode* delete_min(TreeNode* node)
{
    TreeNode* temp = node;
    while (temp->left != NULL)
        temp = temp->left;
    return temp;
}

TreeNode* delete_node(TreeNode* root, int id)
{
    if (root == NULL) return root;
    if (id < root->data.id)
        root->left = delete_node(root->left, id);
    else if (id > root->data.id)
        root->right = delete_node(root->right, id);
    else {
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        TreeNode* temp = delete_min(root->right);
        root->data = temp->data;
        root->right = delete_node(root->right, temp->data.id);
    }
    return root;
}

TreeNode* search(TreeNode* node, int id) {
    if (node == NULL) return NULL;
    if (id == node->data.id) return node;
    else if (id < node->data.id)
        return search(node->left, id);
    else
        return search(node->right, id);
}

int get_count(TreeNode* root)
{
    int count = 0;
    if (root != NULL)
        count = 1 + get_count(root->left) + get_count(root->right);
    return count;
}

void inorder(TreeNode* root) {
    if (root != NULL) {
        inorder(root->left);

        printf("--------------------\n");
        printf("학번: %d\n", root->data.id);
        printf("이름: %s\n", root->data.name);
        printf("전화번호: %s\n", root->data.tel);
        printf("학과: %s\n", root->data.dept);

        inorder(root->right);
    }
}

int main(void)
{
    TreeNode* root = NULL;
    char button;
    int id;
    char name[MAX_STRING] = "";
    char tel[MAX_STRING] = "";
    char dept[MAX_STRING] = "";

    while (1) {
        printf("Enter i<nsert>,d<elete>,s<earch>,p<rint>,h<eight>,c<ount>,m<ax>,n<min>,q<uit>:");
        scanf("%c", &button);

        switch (button) {
        case 'i':
            printf("학번 입력:");
            scanf("%d", &id);
            printf("이름 입력:");
            scanf("%s", name);
            printf("전화번호 입력:");
            scanf("%s", tel);
            printf("학과 입력:");
            scanf("%s", dept);
            root = insert_node(root, id, name, tel, dept);
            break;
            
        case 'd':
            printf("삭제할 학번 입력:");
            scanf("%d", &id);
            root = delete_node(root, id);
            break;
            
        case 's':
            printf("탐색할 학번 입력:");
            scanf("%d", &id);
            if (search(root, id) == NULL)
                printf("아이디가 %d인 학생은 없습니다.\n", id);
            else {
                TreeNode* temp = search(root, id);
                printf("--------------------\n");
                printf("학번: %d\n", temp->data.id);
                printf("이름: %s\n", temp->data.name);
                printf("전화번호: %s\n", temp->data.tel);
                printf("학과: %s\n", temp->data.dept);
            }
            break;
            
        case 'p':
            inorder(root);
            printf("\n");
            break;
            
        case 'c':
            printf("현재 저장된 학생의 총 수는 %d\n", get_count(root));
            break;

        case 'q':
            return;

        default:
            printf("잘못된 입력값.");
            break;
        }
        while (getchar() != '\n');
    }
}
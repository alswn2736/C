#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

TreeNode* insert_node(TreeNode* node, int key)
{
    if (node == NULL) { 
        TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
        temp->data = key;
        temp->left = temp->right = NULL;
        return temp;
    }
    if (key < node->data)
        node->left = insert_node(node->left, key);
    else if (key > node->data)
        node->right = insert_node(node->right, key);

    return node;
}
TreeNode* delete_min(TreeNode* node)
{
    TreeNode* temp = node;
    while (temp->left != NULL)
        temp = temp->left;
    return temp;
}
TreeNode* delete_node(TreeNode* root, int key)
{
    if (root == NULL) return root;
    if (key < root->data)
        root->left = delete_node(root->left, key);
    else if (key > root->data)
        root->right = delete_node(root->right, key);
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
        root->right = delete_node(root->right, temp->data);
    }
    return root;
}
TreeNode* search(TreeNode* node, int key)
{
    if (node == NULL) return NULL;
    if (key == node->data) return node;
    else if (key < node->data)
        return search(node->left, key);
    else
        return search(node->right, key);
}
int get_height(TreeNode* root)
{
    int height = 0;
    if (root != NULL)
        height = 1 + max(get_height(root->left), get_height(root->right));
    return height;
}
int get_count(TreeNode* root)
{
    int count = 0;
    if (root != NULL)
        count = 1 + get_count(root->left) + get_count(root->right);
    return count;
}
int get_maximum(TreeNode* root)
{
    TreeNode* temp = root;
    while (temp->right != NULL)
        temp = temp->right;
    return temp->data;
}
int get_minimum(TreeNode* root)
{
    TreeNode* temp = root;
    while (temp->left != NULL)
        temp = temp->left;
    return temp->data;
}
void preorder(TreeNode* root)
{
    if (root != NULL) {
        printf("[%d] ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}
int main(void)
{
    TreeNode* root = NULL;
    char button;
    int key;

    while (1) {
        printf("Enter i<nsert>,d<elete>,s<earch>,p<rint>,h<eight>,c<ount>,m<ax>,n<min>,q<uit>:");
        scanf("%c", &button);

        switch (button) {
        case 'i':
            printf("삽입할 key값 입력:");
            scanf("%d", &key);
            root = insert_node(root, key);
            break;
        case 'd':
            printf("삭제할 key값 입력:");
            scanf("%d", &key);
            root = delete_node(root, key);
            break;
        case 's':
            printf("탐색할 key값 입력:");
            scanf("%d", &key);
            if (search(root, key) == NULL)
                printf("없음\n");
            else
                printf("있음\n");
            break;
        case 'p':
            preorder(root);
            printf("\n");
            break;
        case 'h':
            printf("트리의 높이는 %d\n", get_height(root));
            break;
        case 'c':
            printf("노드의 개수는 %d\n", get_count(root));
            break;
        case 'm':
            printf("가장 큰 값은 %d\n", get_maximum(root));
            break;
        case 'n':
            printf("가장 작은 값은 %d\n", get_minimum(root));
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
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

// 创建节点
struct TreeNode* createNode(int data) {
    struct TreeNode *newnode = malloc(sizeof(struct TreeNode));
    if (newnode == NULL) {
        printf("内存分配失败\n");
        return NULL;
    }
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

// 插入（BST：左小右大）
struct TreeNode* insert(struct TreeNode *root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    // 相等不插入，BST 不允许重复

    return root;
}

// 查找
struct TreeNode* search(struct TreeNode *root, int data) {
    if (root == NULL) return NULL;

    if (data == root->data) {
        return root;
    } else if (data < root->data) {
        return search(root->left, data);
    } else {
        return search(root->right, data);
    }
}

// 找子树最小值：一路往左走到底
struct TreeNode* findMin(struct TreeNode *root) {
    if (root == NULL) return NULL;
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// 删除节点
struct TreeNode* deleteNode(struct TreeNode *root, int data) {
    if (root == NULL) {
        printf("未找到 %d\n", data);
        return NULL;
    }

    // 1. 先找到要删的节点
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        // 找到了，分三种情况

        // 情况 1：叶子节点
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        // 情况 2：只有一个孩子
        else if (root->left == NULL) {
            struct TreeNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct TreeNode *temp = root->left;
            free(root);
            return temp;
        }

        // 情况 3：有两个孩子
        else {
            struct TreeNode *minNode = findMin(root->right);
            root->data = minNode->data;
            root->right = deleteNode(root->right, minNode->data);
        }
    }

    return root;
}

// 前序遍历：根 → 左 → 右
void preorder(struct TreeNode *root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

// 中序遍历：左 → 根 → 右
void inorder(struct TreeNode *root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

// 后序遍历：左 → 右 → 根
void postorder(struct TreeNode *root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

// 释放整棵树（后序：先释放孩子，再释放自己）
void freeTree(struct TreeNode *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

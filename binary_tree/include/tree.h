#ifndef TREE_H
#define TREE_H

struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* createNode(int data);
struct TreeNode* insert(struct TreeNode *root, int data);
struct TreeNode* search(struct TreeNode *root, int data);
struct TreeNode* deleteNode(struct TreeNode *root, int data);
struct TreeNode* findMin(struct TreeNode *root);
void preorder(struct TreeNode *root);
void inorder(struct TreeNode *root);
void postorder(struct TreeNode *root);
void freeTree(struct TreeNode *root);

#endif

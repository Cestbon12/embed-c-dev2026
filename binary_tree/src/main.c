#include <stdio.h>
#include "tree.h"

int main(void) {
    struct TreeNode *root = NULL;

    int values[] = {5, 3, 8, 1, 4, 7, 9};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
    }

    printf("初始树的中序遍历：");
    inorder(root);
    printf("\n");

    // 测试 1：删除叶子节点 1
    printf("\n删除叶子节点 1：\n");
    root = deleteNode(root, 1);
    printf("中序遍历：");
    inorder(root);
    printf("\n");

    // 测试 2：删除只有一个孩子的节点 3
    // 原树 3 有左孩子 4（删掉1后，3只有右孩子4）
    printf("\n删除只有一个孩子的节点 3：\n");
    root = deleteNode(root, 3);
    printf("中序遍历：");
    inorder(root);
    printf("\n");

    // 测试 3：删除有两个孩子的节点 5（根）
    printf("\n删除有两个孩子的根节点 5：\n");
    root = deleteNode(root, 5);
    printf("中序遍历：");
    inorder(root);
    printf("\n");

    // 测试 4：删除不存在的节点
    printf("\n删除不存在的节点 100：\n");
    root = deleteNode(root, 100);
    printf("中序遍历：");
    inorder(root);
    printf("\n");

    freeTree(root);
    return 0;
}

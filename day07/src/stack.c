#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

struct Node* push(struct Node *top, int value) {
    struct Node *newnode = createNode(value);
    newnode->next = top;
    return newnode;
}

struct Node* pop(struct Node *top, int *value) {
    if (top == NULL) {
        printf("栈为空\n");
        *value = -1;
        return NULL;
    }
    struct Node *temp = top;
    *value = top->data;
    top = top->next;
    free(temp);
    return top;
}

int peek(struct Node *top) {
    if (top == NULL) {
        printf("栈为空\n");
        return -1;
    }
    return top->data;
}

int isEmpty(struct Node *top) {
    return top == NULL;
}

void freeStack(struct Node *top) {
    freeList(top);   // 复用 list.c 里的 freeList
}

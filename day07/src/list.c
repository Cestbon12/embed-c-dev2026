#include "list.h"
#include <stdio.h>
#include <stdlib.h>

struct Node* createNode(int value) {
    struct Node *newnode = malloc(sizeof(struct Node));
    if (newnode == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    newnode->data = value;
    newnode->next = NULL;
    return newnode;
}

struct Node* insertAtHead(struct Node *head, int value) {
    struct Node *newnode = createNode(value);
    newnode->next = head;
    return newnode;
}

struct Node* deleteNode(struct Node *head, int value) {
    if (head == NULL) return NULL;

    if (head->data == value) {
        struct Node *temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    struct Node *prev = head;
    struct Node *current = head->next;
    while (current != NULL) {
        if (current->data == value) {
            prev->next = current->next;
            free(current);
            return head;
        }
        prev = current;
        current = current->next;
    }
    printf("未找到 %d\n", value);
    return head;
}

struct Node* reverseList(struct Node *head) {
    struct Node *prev = NULL;
    struct Node *current = head;
    while (current != NULL) {
        struct Node *next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

void printList(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void freeList(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        struct Node *temp = current->next;
        free(current);
        current = temp;
    }
}

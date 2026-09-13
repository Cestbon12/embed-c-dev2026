#ifndef LIST_H
#define LIST_H

struct Node {
    int data;
    struct Node *next;
};

struct Node* createNode(int value);
struct Node* insertAtHead(struct Node *head, int value);
struct Node* deleteNode(struct Node *head, int value);
struct Node* reverseList(struct Node *head);
void printList(struct Node *head);
void freeList(struct Node *head);

#endif

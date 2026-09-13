#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

struct Queue* createQueue(void) {
    struct Queue *q = malloc(sizeof(struct Queue));
    if (q == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void enqueue(struct Queue *q, int value) {
    struct Node *newnode = createNode(value);
    if (q->rear == NULL) {
        q->front = newnode;
        q->rear = newnode;
    } else {
        q->rear->next = newnode;
        q->rear = newnode;
    }
}

int dequeue(struct Queue *q) {
    if (q->front == NULL) {
        printf("队列为空\n");
        return -1;
    }
    struct Node *temp = q->front;
    int value = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return value;
}

int front(struct Queue *q) {
    if (q->front == NULL) {
        printf("队列为空\n");
        return -1;
    }
    return q->front->data;
}

int isEmptyQueue(struct Queue *q) {
    return q->front == NULL;
}

void freeQueue(struct Queue *q) {
    freeList(q->front);
    free(q);
}

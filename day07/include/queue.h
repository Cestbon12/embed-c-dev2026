#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

struct Queue {
    struct Node *front;
    struct Node *rear;
};

struct Queue* createQueue(void);
void enqueue(struct Queue *q, int value);
int dequeue(struct Queue *q);
int front(struct Queue *q);
int isEmptyQueue(struct Queue *q);
void freeQueue(struct Queue *q);

#endif

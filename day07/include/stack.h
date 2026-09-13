#ifndef STACK_H
#define STACK_H

#include "list.h"

struct Node* push(struct Node *top, int value);
struct Node* pop(struct Node *top, int *value);
int peek(struct Node *top);
int isEmpty(struct Node *top);
void freeStack(struct Node *top);

#endif

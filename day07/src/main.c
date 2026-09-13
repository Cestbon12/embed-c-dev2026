#include <stdio.h>
#include "list.h"
#include "stack.h"
#include "queue.h"

int main(void) {
    // 测试链表
    printf("=== 链表 ===\n");
    struct Node *head = NULL;
    head = insertAtHead(head, 10);
    head = insertAtHead(head, 20);
    head = insertAtHead(head, 30);
    printList(head);

    head = deleteNode(head, 20);
    printList(head);

    head = reverseList(head);
    printList(head);

    freeList(head);

    // 测试栈
    printf("\n=== 栈 ===\n");
    struct Node *stack = NULL;
    stack = push(stack, 1);
    stack = push(stack, 2);
    stack = push(stack, 3);
    int val;
    stack = pop(stack, &val);
    printf("pop: %d\n", val);
    printf("peek: %d\n", peek(stack));
    freeStack(stack);

    // 测试队列
    printf("\n=== 队列 ===\n");
    struct Queue *q = createQueue();
    enqueue(q, 100);
    enqueue(q, 200);
    printf("dequeue: %d\n", dequeue(q));
    printf("front: %d\n", front(q));
    freeQueue(q);

    return 0;
}

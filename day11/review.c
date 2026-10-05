
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

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

struct Queue {
    struct Node *front;
    struct Node *rear;
};

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

int isEmptyQueue(struct Queue *q) {
    return q->front == NULL;
}

void freeQueue(struct Queue *q) {
    freeList(q->front);
    free(q);
}

int main(void) {
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

    printf("\n=== 栈 ===\n");
    struct Node *stack = NULL;
    stack = push(stack, 1);
    stack = push(stack, 2);
    stack = push(stack, 3);

    printf("栈顶：%d\n", peek(stack));

    int val;
    stack = pop(stack, &val);
    printf("弹出：%d\n", val);

    stack = pop(stack, &val);
    printf("弹出：%d\n", val);

    freeList(stack);

    printf("\n=== 队列 ===\n");
    struct Queue *q = createQueue();
    enqueue(q, 100);
    enqueue(q, 200);
    enqueue(q, 300);

    printf("出队：%d\n", dequeue(q));
    printf("出队：%d\n", dequeue(q));

    if (isEmptyQueue(q)) {
        printf("队列已空\n");
    }

    freeQueue(q);

    return 0;
}


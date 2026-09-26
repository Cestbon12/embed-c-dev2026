#include<stdio.h>
#include<stdlib.h>

struct Node{
int data;
struct Node *next;
};
struct Queue {
    struct Node *front;   // 队头，出队位置
    struct Node *rear;    // 队尾，入队位置
};
struct Node* createNode(int value)
{
	struct Node *newnode=malloc(sizeof(struct Node));
	if(newnode ==NULL)
	{
		printf("fail");
		exit(1);
	}
	newnode->data=value;
	newnode->next=NULL;
	return newnode;
}
struct Node* insertAtHead(struct Node *head, int value)
{
	struct Node*newnode=createNode(value);
	newnode->next=head;
	return newnode;
}
struct Node* deleteNode(struct Node *head, int value)
{
if(head==NULL)
{
return NULL;
}
struct Node *current =head->next;
struct Node *prev=head;
if(head->data==value)
{
struct Node *temp=head;
head=head->next;
free(temp);
return head;
}
while(current!=NULL)
{
if(current->data==value)
{
prev->next=current->next;
free(current);
return head;
}
prev=current;
current=current->next;
return head;
}printf("未找到 %d\n", value);
return head;}
struct Node* reverseList(struct Node *head)
{
struct Node*prev=NULL;
struct Node *current=head;
while(current!=NULL)
{
struct Node *next=current->next;
current->next=prev;
prev=current;
current=next;
}
return prev;
}
void freeList(struct Node *head)
{
struct Node *current=head;
while(current!=NULL)
{
struct Node *temp=current->next;
free(current);
current=temp;
}}
struct Node* push(struct Node *top, int value)
{
struct Node *newnode=createNode(value);
newnode->next=top;
return newnode;
}
struct Node* pop(struct Node *top, int *value)
{
if(top==NULL)
{
printf("fail");
*value=-1;
return NULL;
}

struct Node *temp=top;
*value=top->data;
top=top->next;
free(temp);
return top;
}
void enqueue(struct Queue*q,int value)
{
struct Node *newnode=createNode(value);
if(q->rear==NULL)
{
q->rear=newnode;
q->front=newnode;
}
else{
q->rear->next=newnode;
q->rear=newnode;
}
}
int dequeue(struct Queue*q)
{
if(q->front==NULL)
{
printf("fail");
return -1;
}
struct Node *temp=q->front;
int value=temp->data;
q->front=q->front->next;
if(q->front==NULL)
{
q->rear=NULL;
}
free(temp);
return value;
}
void freeQueue(struct Queue *q) {
    freeList(q->front);
    free(q);
}
void printList(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
int main(void) {
    // ===== 链表 =====
    printf("=== 链表 ===\n");
    struct Node *head = NULL;
    head = insertAtHead(head, 10);
    head = insertAtHead(head, 20);
    head = insertAtHead(head, 30);
    printList(head);              // 30 20 10

    head = deleteNode(head, 20);
    printList(head);              // 30 10

    head = reverseList(head);
    printList(head);              // 10 30

    freeList(head);

    // ===== 栈 =====
    printf("=== 栈 ===\n");
    struct Node *stack = NULL;
    stack = push(stack, 1);
    stack = push(stack, 2);
    stack = push(stack, 3);

    int val;
    stack = pop(stack, &val);
    printf("pop: %d\n", val);     // 3

    stack = pop(stack, &val);
    printf("pop: %d\n", val);     // 2

    freeList(stack);

    // ===== 队列 =====
    printf("=== 队列 ===\n");
    struct Queue *q = malloc(sizeof(struct Queue));
    q->front = NULL;
    q->rear = NULL;

    enqueue(q, 100);
    enqueue(q, 200);
    enqueue(q, 300);

    printf("%d\n", dequeue(q));   // 100
    printf("%d\n", dequeue(q));   // 200

    freeQueue(q);

    return 0;

}


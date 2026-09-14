#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node* createNode(int value) {
    struct Node *newnode = malloc(sizeof(struct Node));
    if (newnode == NULL) {
        printf("fail\n");
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

struct Node* insertAtTail(struct Node *head, int value) {
    struct Node *newnode = createNode(value);
    if (head == NULL) return newnode;
    struct Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newnode;
    return head;
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
        printf("list is %d\n", current->data);
        current = current->next;
    }
}

void freeList(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        struct Node *temp = current->next;
        free(current);
        current = temp;
    }
}


//栈部分
struct Node *push (struct Node *top,int value){
struct Node *newnode =malloc(sizeof(struct Node));
if(newnode ==NULL){
printf("fail");
exit(1);
}
newnode ->data=value;
newnode->next=top;
return newnode;
}

struct Node *pop(struct Node *top,int *value)
{
if(top==NULL){
printf("kong,fail");
*value=-1;
return NULL;
}
struct Node *temp=top;
*value=top->data;
top=top->next;
free(temp);
return top;
}

int peek(struct Node *top){
if(top==NULL){
printf("kong");
return -1;
}
return top->data;
}

int isEmpty(struct Node *top){
return top==NULL;}

void freeStack(struct Node*top){
struct Node *current=top;
while(current!=NULL){
struct Node *temp=current->next;
free(temp);
current=temp;
}
}

//队列部分
struct Queue{
struct Node *front;
struct Node*rear;
};
struct Queue *createQueue(){
struct Queue *q =malloc(sizeof(struct Node ));
if(q ==NULL){
printf("fail");
exit(1);
}
q->front=NULL;
q->rear=NULL;
return q;
}

struct Node *enqueue(struct Queue *q,int value){
struct Node *newnode=malloc(sizeof(struct Node));
if(newnode==NULL){
printf("fail");
exit(1);
}
newnode->data=value;
newnode->next=NULL;
if(q->rear==NULL){
q->front=newnode;
q->rear=newnode;}
else{
q->rear->next=newnode;
q->rear=newnode;
}}

int dequeue(struct Queue *q){
if(q->front==NULL){
printf("kong ");
return -1;
}
struct Node *temp=q->front;
int value=temp->data;
q->front=q->front->next;
if(q->front==NULL){
q->rear=NULL;}
free(temp);
return value;}

int front(struct Queue*q){
if(q->front==NULL){
printf("fail");
return -1;
}
return q->front->data;
}
int isEmptyQueue(struct Queue*q){
return q->front==NULL;
}
void freeQueue(struct Queue*q){
struct Node *current=q->front;
while(current!=NULL){
struct Node *temp=current->next;
free(current);
current=temp;
}
free(q);
}

int main(void) {
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

	struct Node *stack = NULL;
    stack = push(stack, 1);
    stack = push(stack, 2);
    int val;
    stack = pop(stack, &val);
    printf("pop: %d\n", val);   // 2
    freeStack(stack);
    return 0;
}



#include<stdio.h>
#include<stdlib.h>
struct Queue{
struct Node*front;
struct Node*rear;
};
struct Node{
int data;
struct Node *next;
};
struct Queue*createQueue(){
struct Queue*q=malloc(sizeof(struct Queue));
if(q==NULL){
printf("fail");
exit(1);
}
q->front=NULL;
q->rear=NULL;
return q;
}

void enqueue(struct Queue *q,int value){
struct Node *newnode=malloc(sizeof(struct Node));
if(newnode==NULL){
printf("fail");
exit(1);
}
newnode->data=value;
newnode->next=NULL;

if(q->rear==NULL){
q->front=newnode;
q->rear=newnode;
}else{
q->rear->next=newnode;
q->rear=newnode;
}
}

int dequeue(struct Queue *q){
if(q->front==NULL){
printf("fail");
return -1;
}
struct Node *temp=q->front;
int value=temp->data;
q->front = q->front->next;
if(q->front==NULL){
q->rear=NULL;
}
free(temp);
return value;
}


int front(struct Queue *q){
if(q->front==NULL){
printf("kong");
return -1;
}
return q->front->data;
}
int isEmpty(struct Queue *q){
return q->front==NULL;
}
void freeQueue(struct Queue *q){
struct Node*current=q->front;
while(current!=NULL)
{
struct Node *temp=current->next;
free(current);
current=temp;
}
free(q);
}
int main(void) {
    struct Queue *q = createQueue();

    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);

    printf("队头元素：%d\n", front(q));   // 10

    printf("出队：%d\n", dequeue(q));     // 10
    printf("出队：%d\n", dequeue(q));     // 20

    printf("队头元素：%d\n", front(q));   // 30

    enqueue(q, 40);
    printf("出队：%d\n", dequeue(q));     // 30
    printf("出队：%d\n", dequeue(q));     // 40

    if (isEmpty(q)) {
        printf("队列已空\n");
    }

    freeQueue(q);
    return 0;
}

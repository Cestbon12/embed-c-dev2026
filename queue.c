#include<stdio.h>
#define MAX_SIZE 6//实际最多存5个元素

typedef struct{
	int date[MAX_SIZE];
	int front;
	int rear;
}CircularQueue;

void initQueue(CircularQueue*q){
	q->front=0;
	q->rear=0;
} 
int isEmpty(CircularQueue*q){
	return q->front==q->rear;
}
//判满 
int isFull(CircularQueue*q){
	return(q->rear+1)%MAX_SIZE==q->front;
}
//入队 
int enqueue(CircularQueue*q,int value){
	if(isFull(q)){
		printf("队列已满,无法入队%d\n",value);
		return 0;
	}
	q->date[q->rear]=value;//存入元素 
	q->rear=(q->rear+1)%MAX_SIZE;//rear后移 
	return 1;//成功 
}
//出队
int dequeue(CircularQueue*q,int *value){
	if(isEmpty(q)){
		printf("队列为空,无法出队\n");
		return 0;
	}
	*value=q->date[q->front];//取出首元素 
	q->front=(q->front+1)%MAX_SIZE;//front后移 
	return 1;
} 
int main(){
	CircularQueue q;
	initQueue(&q);
	printf("依次入队1,2,3,4,5:\n");
	enqueue(&q,1);
	enqueue(&q,2);
	enqueue(&q,3);
	enqueue(&q,4);
	enqueue(&q,5);
	
	printf("出队两个元素\n");
	int val;
	dequeue(&q,&val);
	printf("出队:%d\n",val);
	dequeue(&q,&val);
	printf("出队:%d\n",val);
	printf("再入队6,7:\n");
	enqueue(&q,6);
	enqueue(&q,7);
	
	printf("队列剩余元素全部出队:\n");
	while(!isEmpty(&q)){
		dequeue(&q,&val);
		printf("%d",val);
	}
	printf("\n");
	return 0;	
}

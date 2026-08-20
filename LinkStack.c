#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
int date;
struct Node*next;
}Node;
Node*push(Node*top,int value){
	Node*newNode=(Node*)malloc(sizeof(Node));
	newNode->date=value;
	newNode->next=top;
	top=newNode;
	return top;
}
Node *pop(Node*top,int *value){
	if(top==NULL){
		printf("栈为空");
		return NULL;
	}
	Node*temp=top;
	*value=top->date;
	top=top->next;
	free(temp);
	return top;
}
int isEmpty(Node*top){
	return top==NULL;
}
void printStack(Node*top){
	Node*p=top;
	while(p!=NULL){
		printf("%d ",p->date);
		p=p->next;
	}
	printf("\n");
}
int main(){
Node*stack=NULL;
printf("入栈 10 20 30:\n");
stack=push(stack, 10);
stack=push(stack, 20);
stack=push(stack, 30);
printf("当前栈(从栈顶到栈底:)");
printStack(stack);
int val;
printf("\n出栈一个元素:\n");
stack =pop(stack,&val);
printf("出栈的值:%d\n",val);
printf("当前栈:");
printStack(stack);
	return 0;
}

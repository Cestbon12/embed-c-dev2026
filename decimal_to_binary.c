#include<stdio.h>
#define MAX 100
int stack[MAX];
int top = -1;
void push(int x){
	if(top<MAX - 1)stack[++top]=x; 
}
int pop(){
	if(top==-1)return -1;
	return stack[top--];
}
int isEmpty(){
	return top==-1;
}
int main(){
	int n;
	while(1)
{
	printf("请输入一个十进制整数:");
	scanf("%d",&n);
	if(n==0){
		printf("二进制:0\n");
		return 0;
	}
	while (n>0){
		push(n%2);
		n=n/2;
	}
	printf("二进制:");
	while(!isEmpty()){
		printf("%d",pop());
	}
	printf("\n");}
	return 0;
}


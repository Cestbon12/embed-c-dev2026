#include<stdio.h>
#include<stdlib.h>
struct Stack{
struct Node *top;
int size;
};
struct Node{
int data;
struct Node*next;
};
struct Node *push(struct Node * top,int value){
struct Node *newnode=malloc(sizeof(struct Node));
if(newnode==NULL){
printf("fail");
exit(1);
}
newnode->data=value;
newnode->next=top;
return newnode;
}

struct Node *pop(struct Node *top,int *value){
if(top==NULL){
printf("fail");
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

int isempty(struct Node *top){
return top==NULL;}

void freestack(struct Node *top){
struct Node *current=top;
while(current!=NULL){
struct Node *temp=current->next;
free(current);
current=temp;
}
}

int main(){
 struct Node *stack = NULL;   // 空栈

    // 入栈
    stack = push(stack, 10);
    stack = push(stack, 20);
    stack = push(stack, 30);

    printf("栈顶元素：%d\n", peek(stack));   // 30

    // 出栈
    int value;
    stack = pop(stack, &value);
    printf("弹出：%d\n", value);   // 30

    stack = pop(stack, &value);
    printf("弹出：%d\n", value);   // 20

    printf("栈顶元素：%d\n", peek(stack));   // 10

    // 继续出栈
    stack = pop(stack, &value);
    printf("弹出：%d\n", value);   // 10

    // 此时栈为空
    if (isempty(stack)) {
        printf("栈已空\n");
    }

    freestack(stack);
    return 0;
}

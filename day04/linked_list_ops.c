#include<stdio.h>
#include<stdlib.h>
struct Node{
int data;
struct Node*next;
};

struct Node*createNode(int value){
struct Node*newnode=(struct Node*)malloc(sizeof(struct Node));
if(newnode==NULL)
{
printf("fail");
exit(1);
}
newnode->data=value;
newnode->next=NULL;
return newnode;
}

struct Node*inserttail(struct Node *head,int value){
struct Node *newnode=createNode(value);
if(head==NULL){
return newnode;
}
struct Node*current=head;
while(current->next!=NULL)
{
current=current->next;
}
current->next=newnode;
return head;
}
struct Node*insert(struct Node *head,int vaule){
struct Node*newnode=createNode(vaule);
newnode->next=head;
return newnode;
}

void printList(struct Node*head){
struct Node*current=head;
while(current!=NULL)
{
printf("%d->",current->data);
current=current->next;
}
printf("NULL\n");
}

void freeList(struct Node*head){
struct Node*current=head;
while(current!=NULL){
struct Node* temp=current->next;
free(current);
current =temp;}
}

struct Node *deleteNode(struct Node *head,int value){
	if(head==NULL)
{
	return NULL;
}
if(head->data==value){
	struct Node*temp=head;
	head=head->next;
	free(temp);
	return head;
}
struct Node *prev =head;
struct Node *current = head->next;
while(current!=NULL){
if(current->data==value){
prev->next=current->next;
free(current);
return head;
}
prev=current;
current=current->next;
}
printf("not find the value is %d node\n",value);
return head;
}

struct Node*reverseList(struct Node *head)
{
struct Node*prev=NULL;
struct Node *current=head;
while(current!=NULL)
{
struct Node*next=current->next;
current->next=prev;
prev=current;
current=next;
}
return prev;
}
int main(){
struct Node*head=NULL;
head =insert(head,10);
head=insert(head,20);
head=insert(head,30);
printList(head);

head =inserttail(head,5);
head=inserttail(head,0);
printList(head);

head =deleteNode(head,20);
printList(head);

head= deleteNode(head,30);
printList(head);

head = deleteNode(head,99);
printList(head);

head = reverseList(head);
printList(head);
   
freeList(head);
return 0;
}

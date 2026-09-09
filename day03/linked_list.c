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
int main(){
struct Node*head=NULL;
head =insert(head,10);
head=insert(head,20);
head=insert(head,30);
printList(head);
head =inserttail(head,5);
head=inserttail(head,0);
printList(head);
freeList(head);
return 0;
}

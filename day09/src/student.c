#include<stdio.h>
#include<stdlib.h>
#include"student.h"

struct Student*addStudent(struct Student *head){
struct Student *newnode=malloc(sizeof(struct Student));
if(newnode==NULL){
printf("fail");
exit(1);
}
printf("请输入学号:");
scanf("%d",&newnode->id);
printf("请输入姓名:");
scanf("%s",newnode->name);
printf("请输入成绩:");
scanf("%f",&newnode->score);
newnode->next=NULL;
if(head==NULL){
return newnode;
}
struct Student *current=head;
while(current->next!=NULL){
current=current->next;
}
current->next=newnode;
return head;
}
void printAll(struct Student*head){
if(head==NULL){
printf("暂无记录");
return ;}
printf("\n%-10s %-15s %-10s\n", "学号", "姓名", "成绩");
printf("--------------------------------------\n");
struct Student* current=head;
while(current!=NULL){
printf("%-10d %-15s %-10.2f\n",current->id,current->name,current->score);
current=current->next;
}}
void freeAll(struct Student *head){
struct Student *current =head;
while(current!=NULL){
struct Student *temp=current->next;
free(current);
current=temp;
}}



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

struct Student *deleteStudent(struct Student *head,int id){
if(head==NULL){
printf("kong");
return NULL;
}
if(head->id==id){
struct Student*temp=head;
head=head->next;
free(temp);
printf("delete %d\n",id);
return head;
}
struct Student*prev=head;
struct Student*current=head->next;
while(current!=NULL){
if(current->id==id){
prev->next=current->next;
free(current);
printf("delete %d\n",id);
return head;
}
prev=current;
current=current->next;
}
printf("not find %d\n",id);
return head;
}
struct Student* findStudent(struct Student *head, int id) {
    struct Student *current = head;
    while (current != NULL) {
        if (current->id == id) {
            printf("找到学生：学号=%d 姓名=%s 成绩=%.2f\n",
                   current->id, current->name, current->score);
            return current;
        }
        current = current->next;
    }
    printf("未找到学号 %d\n", id);
    return NULL;
}
void modifyStudent(struct Student *head, int id) {
    struct Student *target = findStudent(head, id);
    if (target == NULL) {
        return;
    }
    printf("请输入新姓名：");
    scanf("%s", target->name);
    printf("请输入新成绩：");
    scanf("%f", &target->score);
    printf("修改成功\n");
}
void freeAll(struct Student *head){
struct Student *current =head;
while(current!=NULL){
struct Student *temp=current->next;
free(current);
current=temp;
}}



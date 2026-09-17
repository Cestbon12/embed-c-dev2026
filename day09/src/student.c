#include<stdio.h>
#include<stdlib.h>
#include"student.h"
#include<string.h>
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

struct Student*sortByScore(struct Student *head){
if(head==NULL){
return NULL;}
for(struct Student *p=head;p!=NULL;p=p->next){
	for(struct Student *q=p->next;q!=NULL;q=q->next){
		if(p->score<q->score){
			int tmpId= p->id;
			p->id=q->id;
			q->id=tmpId;
			
			char tmpName[30];
			strcpy(tmpName,p->name);
			strcpy(p->name,q->name);
			strcpy(q->name,tmpName);

			float tmpScore=p->score;
			p->score=q->score;
			q->score=tmpScore;
}
}
}
return head;
}
void saveToFile(struct Student *head, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("无法打开文件 %s\n", filename);
        return;
    }
struct Student *current = head;
    while (current != NULL) {
        fprintf(fp, "%d %s %.2f\n", current->id, current->name, current->score);
        current = current->next;
    }

    fclose(fp);
    printf("已保存到 %s\n", filename);
}
struct Student* loadFromFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("无法打开文件 %s\n", filename);
        return NULL;
    }

    struct Student *head = NULL;
    struct Student *tail = NULL;

    int id;
    char name[30];
    float score;

    while (fscanf(fp, "%d %s %f", &id, name, &score) == 3) {
        struct Student *newnode = malloc(sizeof(struct Student));
        if (newnode == NULL) {
            printf("内存分配失败\n");
            fclose(fp);
            return head;
        }
        newnode->id = id;
        strcpy(newnode->name, name);
        newnode->score = score;
        newnode->next = NULL;

        if (head == NULL) {
            head = newnode;
            tail = newnode;
        } else {
            tail->next = newnode;
            tail = newnode;
        }
    }

    fclose(fp);
    printf("已从 %s 加载数据\n", filename);
    return head;
}

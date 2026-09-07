#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Student{
	int id;
	char name[20];
	float score;
	struct Student *next;//指向下一个节点的指针 
}Student;//定义结构体Student代替struct Student 

Student* createStudent(int id,const char *name,float score){
	Student *newNode =(Student*)malloc(sizeof(Student));
	if(newNode==NULL){
		printf("分配内存失败.");
		exit(1);
	}
	newNode->id=id;
	strcpy(newNode->name,name);
	newNode->score=score;
	newNode->next=NULL;
	return newNode;
}//创建新节点(一个学生)
Student* createList(){
	Student*head=NULL;
	Student*tail=NULL;
	//准备五个学生数据
	int ids[5]={1,2,3,4,5};
	char names[5][20]={"张三","李四","王五","赵六","钱七"};
	float scores[5]={85,45,70,55,90};
	int i;
	for(i =0;i<5;i++){
		Student *newNode=createStudent(ids[i],names[i],scores[i]);
		if(head==NULL){
			head=newNode;//头 
			tail=newNode;
		}else{
			tail->next=newNode;//接到尾部 
			tail=newNode;//更新尾指针 
		}
	}
	return head;
} //尾插法创建链表
void printfList(Student *head){
	Student*p=head;
	while(p!=NULL){
		printf("学号:%d,姓名:%s,成绩:%.1f\n",p->id,p->name,p->score);
		p=p->next;
	}
	printf("\n");
} //遍历打印链表
Student* deleteLowScore(Student *head){
	while(head!=NULL&&head->score<60){
		Student*temp=head;
		head = head->next;
		free(temp);//释放被删除的节点内存 
	}//如果链表空了,就返回NULL 
	if(head==NULL){
		return NULL;
	}
	Student *prev=head;//前一个节点 
	Student*curr=head->next;//当前要检查节点 
	while(curr!=NULL){
		if(curr->score<60){
			prev->next=curr->next;//前一个节点直接连接当前节点的下一个节点 
			free(curr);//释放当前节点 
			curr=prev->next;//继续开始下一个 
		}else{
			prev=curr;
			curr=curr->next;//成绩都合格,prev和curr都向后移动 
		}
	}
	return head;
} //删除成绩低于60分的学生 
int main(){
	Student*list=createList();
	printf("原始链表:\n");
	printfList(list);
	list = deleteLowScore(list);
	printf("删除成绩低于60分后的链表:\n");
	printfList(list);
	return 0;
} 

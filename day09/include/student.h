#ifndef STUDENT_H
#define STUDENT_H
struct Student{
int id;
char name[30];
float score;
struct Student *next;
};
struct Student *addStudent (struct Student *head);
void printAll(struct Student *head);
void freeAll(struct Student *head);
struct Student * deleteStudent(struct Student *head,int id);
struct Student*findStudent(struct Student*head,int id);
void modifyStudent(struct Student *head,int id);

#endif

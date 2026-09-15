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

#endif

#ifndef STUDENT_H
#define STUDENT_H

struct Student {
    int id;
    char name[30];
    float score;
    struct Student *next;
};

// 增删改查
struct Student* addStudent(struct Student *head);
struct Student* deleteStudent(struct Student *head, int id);
void findStudent(struct Student *head, int id);
void findByName(struct Student *head, const char *name);
void modifyStudent(struct Student *head, int id);
void printAll(struct Student *head);
void freeAll(struct Student *head);

// 排序
struct Student* sortByScore(struct Student *head);

// 文件
void saveToFile(struct Student *head, const char *filename);
struct Student* loadFromFile(const char *filename);

#endif

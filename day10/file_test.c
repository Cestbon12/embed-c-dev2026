#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[30];
    float score;
    struct Student *next;
};

void saveFile(struct Student *head, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("无法打开 %s\n", filename);
        return;
    }

    struct Student *current = head;
    while (current != NULL) {
        fprintf(fp, "%d %s %.2f\n",
                current->id, current->name, current->score);
        current = current->next;
    }

    fclose(fp);
    printf("已保存到 %s\n", filename);
}

struct Student* loadFromFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("无法打开 %s\n", filename);
        return NULL;
    }

    struct Student *head = NULL;
    struct Student *tail = NULL;

    int id;
    char name[30];
    float score;

    while (fscanf(fp, "%d %s %f", &id, name, &score) == 3) {
        struct Student *newnode = malloc(sizeof(struct Student));
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
    printf("已从 %s 加载\n", filename);
    return head;
}

void printAll(struct Student *head) {
    struct Student *current = head;
    while (current != NULL) {
        printf("id=%d name=%s score=%.2f\n",
               current->id, current->name, current->score);
        current = current->next;
    }
}

void freeAll(struct Student *head) {
    struct Student *current = head;
    while (current != NULL) {
        struct Student *temp = current->next;
        free(current);
        current = temp;
    }
}

int main(void) {
    // 手动构造两个学生
    struct Student *s1 = malloc(sizeof(struct Student));
    s1->id = 1001;
    strcpy(s1->name, "zhangsan");
    s1->score = 85.5;
    s1->next = NULL;

    struct Student *s2 = malloc(sizeof(struct Student));
    s2->id = 1002;
    strcpy(s2->name, "lisi");
    s2->score = 92.0;
    s2->next = NULL;

    s1->next = s2;

    // 保存
    saveFile(s1, "test.txt");

    // 释放旧链表
    freeAll(s1);

    // 加载
    struct Student *head = loadFromFile("test.txt");

    // 打印
    printf("\n=== 加载后 ===\n");
    printAll(head);

    freeAll(head);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

// 清空输入缓冲区
static void clear_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 检查学号是否已存在
static int id_exists(struct Student *head, int id) {
    struct Student *current = head;
    while (current != NULL) {
        if (current->id == id) return 1;
        current = current->next;
    }
    return 0;
}

// 添加学生（尾插法）
struct Student* addStudent(struct Student *head) {
    struct Student *newnode = malloc(sizeof(struct Student));
    if (newnode == NULL) {
        printf("内存分配失败\n");
        return head;
    }

    // 输入学号，检查重复
    int id;
    while (1) {
        printf("请输入学号：");
        if (scanf("%d", &id) != 1) {
            printf("输入无效，请重新输入\n");
            clear_input();
            continue;
        }
        clear_input();
        if (id_exists(head, id)) {
            printf("学号 %d 已存在，请重新输入\n", id);
            continue;
        }
        break;
    }
    newnode->id = id;

    // 输入姓名，限制长度
    printf("请输入姓名：");
    scanf("%29s", newnode->name);
    clear_input();

    // 输入成绩，检查范围
    float score;
    while (1) {
        printf("请输入成绩（0~100）：");
        if (scanf("%f", &score) != 1) {
            printf("输入无效，请重新输入\n");
            clear_input();
            continue;
        }
        clear_input();
        if (score < 0 || score > 100) {
            printf("成绩必须在 0~100 之间，请重新输入\n");
            continue;
        }
        break;
    }
    newnode->score = score;
    newnode->next = NULL;

    // 尾插
    if (head == NULL) return newnode;

    struct Student *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newnode;
    return head;
}

// 删除学生
struct Student* deleteStudent(struct Student *head, int id) {
    if (head == NULL) {
        printf("链表为空\n");
        return NULL;
    }

    if (head->id == id) {
        struct Student *temp = head;
        head = head->next;
        free(temp);
        printf("已删除学号 %d\n", id);
        return head;
    }

    struct Student *prev = head;
    struct Student *current = head->next;
    while (current != NULL) {
        if (current->id == id) {
            prev->next = current->next;
            free(current);
            printf("已删除学号 %d\n", id);
            return head;
        }
        prev = current;
        current = current->next;
    }

    printf("未找到学号 %d\n", id);
    return head;
}

// 按学号查找
void findStudent(struct Student *head, int id) {
    struct Student *current = head;
    while (current != NULL) {
        if (current->id == id) {
            printf("找到：学号=%d 姓名=%s 成绩=%.2f\n",
                   current->id, current->name, current->score);
            return;
        }
        current = current->next;
    }
    printf("未找到学号 %d\n", id);
}

// 按姓名查找
void findByName(struct Student *head, const char *name) {
    struct Student *current = head;
    int found = 0;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("找到：学号=%d 姓名=%s 成绩=%.2f\n",
                   current->id, current->name, current->score);
            found = 1;
        }
        current = current->next;
    }
    if (!found) {
        printf("未找到姓名 %s\n", name);
    }
}

// 修改学生
void modifyStudent(struct Student *head, int id) {
    struct Student *current = head;
    while (current != NULL) {
        if (current->id == id) {
            printf("请输入新姓名：");
            scanf("%29s", current->name);
            clear_input();

            float score;
            while (1) {
                printf("请输入新成绩（0~100）：");
                if (scanf("%f", &score) != 1) {
                    printf("输入无效\n");
                    clear_input();
                    continue;
                }
                clear_input();
                if (score < 0 || score > 100) {
                    printf("成绩必须在 0~100 之间\n");
                    continue;
                }
                break;
            }
            current->score = score;
            printf("修改成功\n");
            return;
        }
        current = current->next;
    }
    printf("未找到学号 %d\n", id);
}

// 打印所有学生
void printAll(struct Student *head) {
    if (head == NULL) {
        printf("暂无学生记录\n");
        return;
    }

    printf("\n%-10s %-15s %-10s\n", "学号", "姓名", "成绩");
    printf("--------------------------------------\n");
    struct Student *current = head;
    while (current != NULL) {
        printf("%-10d %-15s %-10.2f\n",
               current->id, current->name, current->score);
        current = current->next;
    }
}

// 按成绩排序（从高到低）
struct Student* sortByScore(struct Student *head) {
    if (head == NULL) return NULL;

    for (struct Student *p = head; p != NULL; p = p->next) {
        for (struct Student *q = p->next; q != NULL; q = q->next) {
            if (p->score < q->score) {
                int tmpId = p->id;
                p->id = q->id;
                q->id = tmpId;

                char tmpName[30];
                strcpy(tmpName, p->name);
                strcpy(p->name, q->name);
                strcpy(q->name, tmpName);

                float tmpScore = p->score;
                p->score = q->score;
                q->score = tmpScore;
            }
        }
    }
    return head;
}

// 释放链表
void freeAll(struct Student *head) {
    struct Student *current = head;
    while (current != NULL) {
        struct Student *temp = current->next;
        free(current);
        current = temp;
    }
}

// 保存到文件
void saveToFile(struct Student *head, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("无法打开文件 %s\n", filename);
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

// 从文件加载
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
    printf("已从 %s 加载\n", filename);
    return head;
}

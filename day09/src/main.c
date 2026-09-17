#include <stdio.h>
#include <stdlib.h>
#include "student.h"

void menu(void) {
    printf("\n====================\n");
    printf("  学生管理系统\n");
    printf("====================\n");
    printf("1. 添加学生\n");
    printf("2. 删除学生\n");
    printf("3. 修改学生\n");
    printf("4. 查找学生\n");
    printf("5. 显示所有学生\n");
    printf("6. 按成绩排序\n");
    printf("7. 保存到文件\n");
    printf("8. 从文件加载\n");
    printf("0. 退出\n");
    printf("====================\n");
    printf("请选择：");
}

int main(void) {
    struct Student *head = NULL;
    int choice;
    int id;

    while (1) {
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                head = addStudent(head);
                break;
            case 2:
                printf("请输入要删除的学号：");
                scanf("%d", &id);
                head = deleteStudent(head, id);
                break;
            case 3:
                printf("请输入要修改的学号：");
                scanf("%d", &id);
                modifyStudent(head, id);
                break;
            case 4:
                printf("请输入要查找的学号：");
                scanf("%d", &id);
                findStudent(head, id);
                break;
            case 5:
                printAll(head);
                break;
            case 6:
                head = sortByScore(head);
                printf("排序完成\n");
                printAll(head);
                break;
            case 7:
                saveToFile(head, "students.txt");
                break;
            case 8:
                freeAll(head);
                head = loadFromFile("students.txt");
                printAll(head);
                break;
            case 0:
                freeAll(head);
                printf("再见\n");
                return 0;
            default:
                printf("无效选择，请重新输入\n");
        }
    }
}

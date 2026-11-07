#include <stdio.h>
#include "student.h"

void menu(void) {
    printf("\n====================\n");
    printf("  学生管理系统\n");
    printf("====================\n");
    printf("1. 添加学生\n");
    printf("2. 删除学生\n");
    printf("3. 修改学生\n");
    printf("4. 按学号查找\n");
    printf("5. 按姓名查找\n");
    printf("6. 显示所有\n");
    printf("7. 按成绩排序\n");
    printf("8. 保存到文件\n");
    printf("9. 从文件加载\n");
    printf("0. 退出\n");
    printf("====================\n");
    printf("请选择：");
}

int main(void) {
    struct Student *head = NULL;
    int choice;
    int id;
    char name[30];

    while (1) {
        menu();

        if (scanf("%d", &choice) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("无效输入，请重新选择\n");
            continue;
        }

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
                printf("请输入要查找的姓名：");
                scanf("%29s", name);
                findByName(head, name);
                break;

            case 6:
                printAll(head);
                break;

            case 7:
                head = sortByScore(head);
                printf("排序完成\n");
                printAll(head);
                break;

            case 8:
                saveToFile(head, "students.txt");
                break;

            case 9:
                freeAll(head);
                head = loadFromFile("students.txt");
                break;

            case 0:
                freeAll(head);
                printf("再见\n");
                return 0;

            default:
                printf("无效选择\n");
        }
    }

    return 0;
}

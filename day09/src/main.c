#include <stdio.h>
#include "student.h"

int main(void) {
    struct Student *head = NULL;

    printf("=== 添加学生 ===\n");
    head = addStudent(head);
    head = addStudent(head);
    head = addStudent(head);
    printf("\n=== 所有学生 ===\n");
    printAll(head);

    printf("\n=== 查找学号 2 ===\n");
    findStudent(head, 2);

    printf("\n=== 修改学号 2 ===\n");
    modifyStudent(head, 2);
    printAll(head);

    printf("\n=== 删除学号 1 ===\n");
    head = deleteStudent(head, 1);
    printAll(head);

    printf("\n=== 删除不存在的学号 99 ===\n");
    head = deleteStudent(head, 99);
    printAll(head);

    freeAll(head);
    return 0;
}

#include <stdio.h>
#include "student.h"

int main(void) {
    struct Student *head = NULL;

    printf("=== 添加学生 ===\n");
    head = addStudent(head);
    head = addStudent(head);

    printf("\n=== 所有学生 ===\n");
    printAll(head);

    freeAll(head);
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
struct Student{
char name[20];
int age;
float score;
};
int main(){
struct Student s1;
printf("请输入姓名：");
scanf("%s",s1.name);
printf("年龄：");
scanf("%d",&s1.age);
printf("请输入成绩：");
    scanf("%f", &s1.score);

    printf("\n--- 普通变量 ---\n");
    printf("姓名：%s\n", s1.name);
    printf("年龄：%d\n", s1.age);
    printf("成绩：%.2f\n", s1.score);

    // 2. 指针访问结构体
    struct Student *p = &s1;
    printf("\n--- 指针访问 ---\n");
    printf("姓名：%s\n", p->name);
    printf("年龄：%d\n", p->age);
    printf("成绩：%.2f\n", p->score);

    // 3. 动态分配结构体
    struct Student *p2 = malloc(sizeof(struct Student));
    if (p2 == NULL) {
        printf("内存分配失败\n");
        return 1;
    }

    printf("\n请输入第二个学生姓名：");
    scanf("%s", p2->name);
    printf("请输入年龄：");
    scanf("%d", &p2->age);
    printf("请输入成绩：");
    scanf("%f", &p2->score);

    printf("\n--- 动态分配的学生 ---\n");
    printf("姓名：%s\n", p2->name);
    printf("年龄：%d\n", p2->age);
    printf("成绩：%.2f\n", p2->score);

    free(p2);

    return 0;
}

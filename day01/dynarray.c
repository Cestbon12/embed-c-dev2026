#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int capacity = 5;
    int size = 0;                 // 当前已存储的元素个数
    int *arr = malloc(capacity * sizeof(int));
    if (arr == NULL) {
        printf("内存分配失败\n");
        return 1;
    }

    printf("请输入整数（输入非数字结束）：\n");
    int num;
    while (scanf("%d", &num) == 1) {
        // 如果数组已满，扩容
        if (size == capacity) {
            capacity *= 2;        // 容量翻倍（5 -> 10）
            int *temp = realloc(arr, capacity * sizeof(int));
            if (temp == NULL) {
                printf("内存扩容失败\n");
                free(arr);        // 释放原来内存
                return 1;
            }
            arr = temp;           // 更新指针
        }
        arr[size] = num;          // 存储输入的数字
        size++;
    }

    // 打印所有元素
    printf("数组内容：");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);                    // 释放内存
    return 0;
}

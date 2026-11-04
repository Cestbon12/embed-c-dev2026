#include <stdio.h>
#include "hash.h"

int main(void) {
    struct HashTable *ht = hash_create(10);

    // 插入
    hash_put(ht, 1001, "张三");
    hash_put(ht, 1002, "李四");
    hash_put(ht, 1003, "赵六");
    hash_put(ht, 1013, "王五");   // 和 1003 冲突，都到格子 3
    hash_put(ht, 1023, "孙八");   // 也和 1003 冲突

    hash_print(ht);

    // 查找
    printf("\n查找 1003: %s\n", hash_get(ht, 1003));
    printf("查找 1013: %s\n", hash_get(ht, 1013));
    printf("查找 9999: %s\n", hash_get(ht, 9999) ? hash_get(ht, 9999) : "未找到");

    // 更新
    hash_put(ht, 1003, "赵六六");
    printf("\n更新后 1003: %s\n", hash_get(ht, 1003));

    // 删除
    hash_remove(ht, 1013);
    printf("\n删除 1013 后：\n");
    hash_print(ht);

    hash_free(ht);
    return 0;
}

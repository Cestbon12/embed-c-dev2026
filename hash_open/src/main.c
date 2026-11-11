#include <stdio.h>
#include "hash.h"

int main(void) {
    struct HashTable *ht = hash_create(10);

    hash_put(ht, "张三", "1001");
    hash_put(ht, "李四", "1002");
    hash_put(ht, "赵六", "1003");
    hash_put(ht, "王五", "1013");
    hash_put(ht, "孙八", "1023");

    hash_print(ht);

    printf("\n查找 张三: %s\n", hash_get(ht, "张三"));
    printf("查找 王五: %s\n", hash_get(ht, "王五"));
    char *r = hash_get(ht, "不存在");
    printf("查找 不存在: %s\n", r ? r : "未找到");

    hash_put(ht, "张三", "9999");
    printf("\n更新后 张三: %s\n", hash_get(ht, "张三"));

    hash_remove(ht, "王五");
    printf("\n删除 王五 后：\n");
    hash_print(ht);

    printf("\n删除后查找 孙八: %s\n", hash_get(ht, "孙八"));

    hash_free(ht);
    return 0;
}

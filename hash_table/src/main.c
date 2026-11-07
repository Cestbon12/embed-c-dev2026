#include <stdio.h>
#include "hash.h"

int main(void) {
    struct HashTable *ht = hash_create(10);

    // 插入
    hash_put(ht, 1001, "张三");
    hash_put(ht, 1002, "李四");
    hash_put(ht, 1003, "赵六");
    hash_put(ht, 1013, "王五");
    hash_put(ht, 1023, "孙八");

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

    // ========== 扩容测试 ==========
    printf("\n========== 扩容测试 ==========\n");
    struct HashTable *ht2 = hash_create(4);   // 故意建小一点，4 个格子
    printf("初始 size = %d\n", ht2->size);

    for (int i = 0; i < 20; i++) {
        char val[32];
        sprintf(val, "value_%d", i);
        hash_put(ht2, 1000 + i, val);

        // 每次插入后打印 size，观察扩容
        printf("插入第 %2d 个后，size = %2d, count = %2d\n",
               i + 1, ht2->size, ht2->count);
    }

    printf("\n最终哈希表：\n");
    hash_print(ht2);

    // 验证数据没丢
    printf("\n验证扩容后数据完整性：\n");
    for (int i = 0; i < 20; i++) {
        char *v = hash_get(ht2, 1000 + i);
        if (v == NULL) {
            printf("❌ 丢失 key = %d\n", 1000 + i);
        }
    }
    printf("全部 20 个 key 检查完毕\n");

    hash_free(ht2);

    return 0;
}

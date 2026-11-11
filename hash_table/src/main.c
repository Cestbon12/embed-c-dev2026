#include <stdio.h>
#include "hash.h"

int main(void) {
    struct HashTable *ht = hash_create(10);

    // 插入
    hash_put(ht, "张三", "1001");
    hash_put(ht, "李四", "1002");
    hash_put(ht, "赵六", "1003");
    hash_put(ht, "王五", "1013");
    hash_put(ht, "孙八", "1023");

    hash_print(ht);

    // 查找
    printf("\n查找 张三: %s\n", hash_get(ht, "张三"));
    printf("查找 王五: %s\n", hash_get(ht, "王五"));
    char *r = hash_get(ht, "不存在");
    printf("查找 不存在: %s\n", r ? r : "未找到");

    // 更新
    hash_put(ht, "张三", "9999");
    printf("\n更新后 张三: %s\n", hash_get(ht, "张三"));

    // 删除
    hash_remove(ht, "王五");
    printf("\n删除 王五 后：\n");
    hash_print(ht);

    hash_free(ht);

    // 扩容测试
    printf("\n========== 扩容测试 ==========\n");
    struct HashTable *ht2 = hash_create(4);
    printf("初始 size = %d\n", ht2->size);

    for (int i = 0; i < 20; i++) {
        char key[32], val[32];
        sprintf(key, "key_%d", i);
        sprintf(val, "value_%d", i);
        hash_put(ht2, key, val);
        printf("插入第 %2d 个后，size = %2d, count = %2d\n",
               i + 1, ht2->size, ht2->count);
    }

    printf("\n最终哈希表：\n");
    hash_print(ht2);

    // 验证数据完整性
    printf("\n验证扩容后数据完整性：\n");
    for (int i = 0; i < 20; i++) {
        char key[32];
        sprintf(key, "key_%d", i);
        if (hash_get(ht2, key) == NULL) {
            printf("❌ 丢失 %s\n", key);
        }
    }
    printf("全部 20 个 key 检查完毕\n");

    hash_free(ht2);
    return 0;
}

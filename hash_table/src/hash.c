#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

// djb2 字符串哈希函数
static unsigned long hash_string(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++) != '\0') {
        hash = hash * 33 + c;
    }
    return hash;
}

// 创建哈希表
struct HashTable* hash_create(int size) {
    struct HashTable *ht = malloc(sizeof(struct HashTable));
    if (ht == NULL) {
        printf("内存分配失败\n");
        return NULL;
    }

    ht->size = size;
    ht->count = 0;
    ht->table = malloc(sizeof(struct Entry *) * size);
    if (ht->table == NULL) {
        printf("内存分配失败\n");
        free(ht);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        ht->table[i] = NULL;
    }

    return ht;
}

// 扩容
static void hash_resize(struct HashTable *ht, int new_size) {
    struct Entry **old_table = ht->table;
    int old_size = ht->size;

    struct Entry **new_table = malloc(sizeof(struct Entry *) * new_size);
    if (new_table == NULL) return;

    for (int i = 0; i < new_size; i++) {
        new_table[i] = NULL;
    }

    for (int i = 0; i < old_size; i++) {
        struct Entry *current = old_table[i];
        while (current != NULL) {
            struct Entry *next = current->next;
            int new_idx = hash_string(current->key) % new_size;
            current->next = new_table[new_idx];
            new_table[new_idx] = current;
            current = next;
        }
    }

    free(old_table);
    ht->table = new_table;
    ht->size = new_size;
}

// 插入或更新
void hash_put(struct HashTable *ht, const char *key, const char *value) {
    if (ht->count >= ht->size * 3 / 4) {
        hash_resize(ht, ht->size * 2);
    }

    int idx = hash_string(key) % ht->size;

    struct Entry *current = ht->table[idx];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            strncpy(current->value, value, VALUE_SIZE - 1);
            current->value[VALUE_SIZE - 1] = '\0';
            return;
        }
        current = current->next;
    }

    struct Entry *newnode = malloc(sizeof(struct Entry));
    if (newnode == NULL) return;

    strncpy(newnode->key, key, KEY_SIZE - 1);
    newnode->key[KEY_SIZE - 1] = '\0';
    strncpy(newnode->value, value, VALUE_SIZE - 1);
    newnode->value[VALUE_SIZE - 1] = '\0';
    newnode->next = ht->table[idx];
    ht->table[idx] = newnode;
    ht->count++;
}

// 查找
char* hash_get(struct HashTable *ht, const char *key) {
    int idx = hash_string(key) % ht->size;

    struct Entry *current = ht->table[idx];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }

    return NULL;
}

// 删除
void hash_remove(struct HashTable *ht, const char *key) {
    int idx = hash_string(key) % ht->size;

    struct Entry *prev = NULL;
    struct Entry *current = ht->table[idx];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                ht->table[idx] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            ht->count--;
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("未找到 key %s\n", key);
}

// 打印
void hash_print(struct HashTable *ht) {
    printf("=== 哈希表 (size=%d, count=%d) ===\n", ht->size, ht->count);
    for (int i = 0; i < ht->size; i++) {
        printf("[%d]: ", i);
        struct Entry *current = ht->table[i];
        while (current != NULL) {
            printf("(%s, %s) -> ", current->key, current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// 释放
void hash_free(struct HashTable *ht) {
    if (ht == NULL) return;

    for (int i = 0; i < ht->size; i++) {
        struct Entry *current = ht->table[i];
        while (current != NULL) {
            struct Entry *temp = current->next;
            free(current);
            current = temp;
        }
    }

    free(ht->table);
    free(ht);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

static unsigned long hash_string(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++) != '\0') {
        hash = hash * 33 + c;
    }
    return hash;
}

struct HashTable* hash_create(int size) {
    struct HashTable *ht = malloc(sizeof(struct HashTable));
    if (ht == NULL) return NULL;

    ht->size = size;
    ht->count = 0;
    ht->table = malloc(sizeof(struct Entry) * size);
    if (ht->table == NULL) {
        free(ht);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        ht->table[i].state = EMPTY;
    }

    return ht;
}

static void hash_resize(struct HashTable *ht, int new_size) {
    struct Entry *old_table = ht->table;
    int old_size = ht->size;

    struct Entry *new_table = malloc(sizeof(struct Entry) * new_size);
    if (new_table == NULL) return;

    for (int i = 0; i < new_size; i++) {
        new_table[i].state = EMPTY;
    }

    for (int i = 0; i < old_size; i++) {
        if (old_table[i].state != OCCUPIED) continue;

        int idx = hash_string(old_table[i].key) % new_size;
        for (int j = 0; j < new_size; j++) {
            int pos = (idx + j) % new_size;
            if (new_table[pos].state == EMPTY) {
                strncpy(new_table[pos].key, old_table[i].key, KEY_SIZE - 1);
                new_table[pos].key[KEY_SIZE - 1] = '\0';
                strncpy(new_table[pos].value, old_table[i].value, VALUE_SIZE - 1);
                new_table[pos].value[VALUE_SIZE - 1] = '\0';
                new_table[pos].state = OCCUPIED;
                break;
            }
        }
    }

    free(old_table);
    ht->table = new_table;
    ht->size = new_size;
}

void hash_put(struct HashTable *ht, const char *key, const char *value) {
    if (ht->count >= ht->size * 3 / 4) {
        hash_resize(ht, ht->size * 2);
    }

    int idx = hash_string(key) % ht->size;
    int tomb_idx = -1;

    for (int i = 0; i < ht->size; i++) {
        int pos = (idx + i) % ht->size;

        if (ht->table[pos].state == EMPTY) {
            int insert_pos = (tomb_idx != -1) ? tomb_idx : pos;
            strncpy(ht->table[insert_pos].key, key, KEY_SIZE - 1);
            ht->table[insert_pos].key[KEY_SIZE - 1] = '\0';
            strncpy(ht->table[insert_pos].value, value, VALUE_SIZE - 1);
            ht->table[insert_pos].value[VALUE_SIZE - 1] = '\0';
            ht->table[insert_pos].state = OCCUPIED;
            ht->count++;
            return;
        }

        if (ht->table[pos].state == TOMB) {
            if (tomb_idx == -1) tomb_idx = pos;
            continue;
        }

        if (strcmp(ht->table[pos].key, key) == 0) {
            strncpy(ht->table[pos].value, value, VALUE_SIZE - 1);
            ht->table[pos].value[VALUE_SIZE - 1] = '\0';
            return;
        }
    }

    printf("哈希表已满，插入失败\n");
}

char* hash_get(struct HashTable *ht, const char *key) {
    int idx = hash_string(key) % ht->size;

    for (int i = 0; i < ht->size; i++) {
        int pos = (idx + i) % ht->size;

        if (ht->table[pos].state == EMPTY) {
            return NULL;
        }

        if (ht->table[pos].state == TOMB) {
            continue;
        }

        if (strcmp(ht->table[pos].key, key) == 0) {
            return ht->table[pos].value;
        }
    }

    return NULL;
}

void hash_remove(struct HashTable *ht, const char *key) {
    int idx = hash_string(key) % ht->size;

    for (int i = 0; i < ht->size; i++) {
        int pos = (idx + i) % ht->size;

        if (ht->table[pos].state == EMPTY) {
            printf("未找到 key %s\n", key);
            return;
        }

        if (ht->table[pos].state == TOMB) {
            continue;
        }

        if (strcmp(ht->table[pos].key, key) == 0) {
            ht->table[pos].state = TOMB;
            ht->count--;
            return;
        }
    }

    printf("未找到 key %s\n", key);
}

void hash_print(struct HashTable *ht) {
    printf("=== 哈希表 (size=%d, count=%d) ===\n", ht->size, ht->count);
    for (int i = 0; i < ht->size; i++) {
        if (ht->table[i].state == EMPTY) {
            printf("[%d]: EMPTY\n", i);
        } else if (ht->table[i].state == TOMB) {
            printf("[%d]: TOMB\n", i);
        } else {
            printf("[%d]: (%s, %s)\n", i, ht->table[i].key, ht->table[i].value);
        }
    }
}

void hash_free(struct HashTable *ht) {
    if (ht == NULL) return;
    free(ht->table);
    free(ht);
}

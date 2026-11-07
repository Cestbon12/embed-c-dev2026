#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hash.h"

static int hash_func(int key,int size)
{
return key%size;
}
struct HashTable*hash_create(int size){
struct HashTable *ht =malloc(sizeof(struct HashTable));
if(ht==NULL){
printf("fail");
return NULL;
}

ht->size=size;
ht->count=0;
ht->table=malloc(sizeof(struct Entry*)*size);
if(ht->table==NULL){
printf("fail");
free(ht);
return NULL;
}
for(int i=0;i<size;i++)
{
ht->table[i]=NULL;
}
return ht;
}
static void hash_resize(struct HashTable*ht,int new_size){
	struct Entry **old_table=ht->table;
	int old_size=ht->size;
	struct Entry**new_table=malloc(sizeof(struct Entry*)*new_size);
	if(new_table==NULL)
{
	return;
}
	for(int i=0;i<new_size;i++)
{
	new_table[i]=NULL;
}
for(int i=0;i<old_size;i++)
{struct Entry*current=old_table[i];
while(current!=NULL)
{struct Entry*next=current->next;
int new_idx=current->key%new_size;
current->next=new_table[new_idx];
new_table[new_idx]=current;
current=next;
}
}
free(old_table);
ht->table=new_table;
ht->size=new_size;
}
void hash_put(struct HashTable *ht, int key, const char *value) {
 if (ht->count >= ht->size * 3 / 4) {
        hash_resize(ht, ht->size * 2);
    }
    int idx = hash_func(key, ht->size);

    // 先找 key 是否存在
    struct Entry *current = ht->table[idx];
    while (current != NULL) {
        if (current->key == key) {
            strncpy(current->value, value, VALUE_SIZE - 1);
            current->value[VALUE_SIZE - 1] = '\0';
            return;
        }
        current = current->next;
    }

    // 不存在，创建新节点，头插
    struct Entry *newnode = malloc(sizeof(struct Entry));
    if (newnode == NULL) {
        printf("内存分配失败\n");
        return;
    }
    newnode->key = key;
    strncpy(newnode->value, value, VALUE_SIZE - 1);
    newnode->value[VALUE_SIZE - 1] = '\0';
    newnode->next = ht->table[idx];
    ht->table[idx] = newnode;
    ht->count++;
}

// 查找
char* hash_get(struct HashTable *ht, int key) {
    int idx = hash_func(key, ht->size);

    struct Entry *current = ht->table[idx];
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }

    return NULL;
}

// 删除
void hash_remove(struct HashTable *ht, int key) {
    int idx = hash_func(key, ht->size);

    struct Entry *current = ht->table[idx];
    struct Entry *prev = NULL;

    while (current != NULL) {
        if (current->key == key) {
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

    printf("未找到 key %d\n", key);
}

// 打印所有元素
void hash_print(struct HashTable *ht) {
    printf("=== 哈希表 (size=%d, count=%d) ===\n", ht->size, ht->count);
    for (int i = 0; i < ht->size; i++) {
        printf("[%d]: ", i);
        struct Entry *current = ht->table[i];
        while (current != NULL) {
            printf("(%d, %s) -> ", current->key, current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// 释放整个哈希表
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


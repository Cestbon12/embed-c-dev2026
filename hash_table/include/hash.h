#ifndef HASH_H
#define HASH_H

#define VALUE_SIZE 50

struct Entry {
    int key;
    char value[VALUE_SIZE];
    struct Entry *next;
};

struct HashTable {
    struct Entry **table;
    int size;
    int count;
};

struct HashTable* hash_create(int size);
void hash_put(struct HashTable *ht, int key, const char *value);
char* hash_get(struct HashTable *ht, int key);
void hash_remove(struct HashTable *ht, int key);
void hash_print(struct HashTable *ht);
void hash_free(struct HashTable *ht);

#endif

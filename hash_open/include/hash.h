#ifndef HASH_H
#define HASH_H

#define KEY_SIZE 50
#define VALUE_SIZE 50

#define EMPTY 0
#define OCCUPIED 1
#define TOMB 2

struct Entry {
    char key[KEY_SIZE];
    char value[VALUE_SIZE];
    int state;
};

struct HashTable {
    struct Entry *table;
    int size;
    int count;
};

struct HashTable* hash_create(int size);
void hash_put(struct HashTable *ht, const char *key, const char *value);
char* hash_get(struct HashTable *ht, const char *key);
void hash_remove(struct HashTable *ht, const char *key);
void hash_print(struct HashTable *ht);
void hash_free(struct HashTable *ht);

#endif

#ifndef HASH_LL_H
#define HASH_LL_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct hashTable table;

bool Hash_Create(table**, int buckets, bool unique);
void Hash_Destroy(table**);

bool Hash_Insert(table*, int value);
size_t Hash_Exists(table*, int value);
bool Hash_Remove(table*, int value);

size_t Hash_ValuesStored(table*);
size_t Hash_BucketsUsed(table*);
size_t Hash_BucketsMax(table*);
double Hash_LoadFactor(table*);

void Hash_Print(table*, bool ignoreEmptyBuckets);

#endif

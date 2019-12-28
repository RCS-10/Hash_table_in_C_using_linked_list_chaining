#include "Hash_LL.h"

typedef struct node
{
	int value;
	struct node *next;
}node;

typedef struct hashTable
{
	node **table;
	size_t valuesStored;
	size_t buckets;
	size_t bucketsMax;
	size_t capacity;
}hashTable;
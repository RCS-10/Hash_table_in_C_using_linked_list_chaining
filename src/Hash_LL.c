#include "Hash_LL.h"
#include <assert.h>
#include <stdio.h>

typedef struct node
{
	int value;
	size_t count;
	struct node *next;
}node;

typedef struct hashTable
{
	node **array;
	size_t valuesStored;
	size_t bucketsUsed;
	size_t bucketsMax;
	bool unique;
}hashTable;

bool Hash_Create(table **ht, int buckets, bool unique)
{
	if(!ht || buckets < 1)
	{
		return false;
	}

	hashTable *newTable = calloc(1, sizeof(hashTable));
	if(!newTable)
	{
		return false;
	}

	newTable->bucketsMax = buckets;
	newTable->unique = unique;

	node **newArray = calloc(newTable->bucketsMax, sizeof(node*));
	if(!newArray)
	{
		free(newTable);
		return false;
	}

	newTable->array = newArray;
	*ht = newTable;

	return true;
}

void Hash_Destroy(table **ht)
{
	if(!ht || !*ht)
		return;

	assert((*ht)->array);

	size_t bucketsMax = (*ht)->bucketsMax;
	node **array = (*ht)->array;

	for(size_t i = 0; i < bucketsMax; ++i)
	{
		if(array[i])
		{
			node *curr = array[i];
			node *prev;
			while(curr)
			{
				prev = curr;
				curr = curr->next;
				free(prev);
			}
		}
	}
		
	free(array);
	free(*ht);

	*ht = NULL;
}

enum {FIND, INSERT, REMOVE};

#define abs(x) ((x) < 0 ? -(x) : (x))

static size_t find(table *ht, int value, int action)
{
	if(!ht)
	{
		return false;
	}

	assert(action == FIND || action == INSERT || action == REMOVE);

	size_t ind = abs(value) % ht->bucketsMax; // Calculate hash

	node *curr = ht->array[ind];
	node *prev = curr;

	while(curr && value > curr->value)
	{
		prev = curr;
		curr = curr->next;
	}

	if(curr && value == curr->value)
	{
		if(FIND == action)
		{
			if(ht->unique)
			{
				return 1;
			}

			return curr->count;
		}
		else if(INSERT == action)
		{
			curr->count++;

			if(ht->unique)
			{
				return 0;
			}

			ht->valuesStored++;
			return 1;
		}
		else
		{
			curr->count--;
			ht->valuesStored--;

			assert(curr->count >= 0);
			assert(ht->valuesStored >= 0);

			if(!ht->unique && curr->count > 0)
			{
				return 1;
			}

			node *deleteMe = curr;
			if(prev == curr) // First entry in array
			{
				if((ht->array[ind] = curr->next) == NULL)
				{
					ht->bucketsUsed--;
					assert(ht->bucketsUsed >= 0);
				}
			}
			else
			{
				prev->next = curr->next;
			}

			free(deleteMe);

			return 1;
		}
	}

	if(FIND == action || REMOVE == action)
	{
		return 0; // Value not found
	}

	assert(action == INSERT);

	node *newNode = calloc(1, sizeof(node));
	if(!newNode)
		return 0;
	newNode->value = value;
	newNode->count = 1;

	assert(curr == NULL || value < curr->value);

	newNode->next = curr;

	if(!prev)
	{
		assert(curr == NULL);
		ht->array[ind] = newNode;
		ht->bucketsUsed++;
		assert(ht->bucketsUsed <= ht->bucketsMax);
	}
	else
	{
		prev->next = newNode;
	}

	ht->valuesStored++;

	return 1;
}

bool Hash_Insert(table *ht, int value)
{
	return find(ht, value, INSERT);
}

size_t Hash_Exists(table *ht, int value)
{
	return find(ht, value, FIND);
}

bool Hash_Remove(table *ht, int value)
{
	return find(ht, value, REMOVE);
}

size_t Hash_ValuesStored(table *ht)
{
	if(!ht)
	{
		return 0;
	}

	return ht->valuesStored;
}

size_t Hash_BucketsUsed(table *ht)
{
	if(!ht)
	{
		return 0;
	}

	return ht->bucketsUsed;
}

size_t Hash_BucketsMax(table *ht)
{
	if(!ht)
	{
		return 0;
	}

	return ht->bucketsMax;
}

double Hash_LoadFactor(table *ht)
{
	if(!ht)
	{
		return 0;
	}

	return (double)ht->bucketsUsed / ht->bucketsMax;
}

void Hash_Print(table *ht, bool ignoreEmptyBuckets)
{
	if(!ht)
	{
		return;
	}

	if(ignoreEmptyBuckets && 0 == ht->bucketsUsed)
	{
		printf("[ ]:\n");
		return;
	}

	size_t bucketsMax = ht->bucketsMax;
	node **array = ht->array;

	for(size_t i = 0; i < bucketsMax; ++i)
	{
		if(array[i])
		{
			printf("[%ld]: ", i);
			node *curr = array[i];
			while(curr)
			{
				size_t count = ht->unique ? 1 : curr->count;
				for(size_t i = 0; i < count; ++i)
				{
					printf("%d ", curr->value);
				}
				curr = curr->next;
			}
			printf("\n");
		}
		else
		{
			if(!ignoreEmptyBuckets)
			{
				printf("[%ld]:\n", i);
			}
		}
	}
	if(!ignoreEmptyBuckets)
	{
		printf("\n");
	}
}

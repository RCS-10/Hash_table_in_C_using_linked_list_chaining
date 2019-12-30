extern "C"
{
#include "Hash_LL.h"
}

#include "CppUTest/TestHarness.h"
// https://github.com/cpputest/cpputest

TEST_GROUP(None)
{
  	hashTable *ht;
	
  	void setup()
  	{
		CHECK(Hash_Create(&ht, 100, true));
		CHECK(ht);
  	}

  	void teardown()
  	{
		Hash_Destroy(&ht);
		POINTERS_EQUAL(NULL, ht);
  	}
};

#if 1
TEST(None, CreateFailsWhenPassingNullPointer)
{
	CHECK_FALSE(Hash_Create(NULL, 100, true));
}
#endif
#if 1
TEST(None, CreateFailsWhenPassingZeroOrNegativeSize)
{
	hashTable *t;
	CHECK_FALSE(Hash_Create(&t, 0, true));
	CHECK_FALSE(Hash_Create(&t, -1, true));
}
#endif
#if 1
TEST(None, CreateDoesNotCrash)
{
	hashTable *t;
	CHECK(Hash_Create(&t, 100, true));
	Hash_Destroy(&t);
}
#endif
#if 1
TEST(None, CreateAndDestroyAssignsToPointer)
{
	hashTable *t;
	CHECK(Hash_Create(&t, 100, true));
	CHECK(t);
	Hash_Destroy(&t);
	POINTERS_EQUAL(NULL, t);
}
#endif
#if 1
TEST(None, NoValuesAndNoBucketsOnCreation)
{
	LONGS_EQUAL(0, Hash_ValuesStored(ht));
	LONGS_EQUAL(0, Hash_BucketsUsed(ht));
}
#endif
#if 1
TEST(None, MaxBucketsDeterminedByInitialization)
{
	hashTable *t;
	CHECK(Hash_Create(&t, 10, true));
	LONGS_EQUAL(10, Hash_BucketsMax(t));
	Hash_Destroy(&t);
	CHECK(Hash_Create(&t, 10000, true));
	LONGS_EQUAL(10000, Hash_BucketsMax(t));
	Hash_Destroy(&t);
}
#endif
#if 1
TEST(None, LoadFactorIsZeroOnCreation)
{
	DOUBLES_EQUAL(0, Hash_LoadFactor(ht), 0.01);
}
#endif
#if 1
TEST(None, FunctionsReturnZeroWhenPassedNull)
{
	CHECK_FALSE(Hash_Insert(NULL, 1));
	CHECK_FALSE(Hash_Exists(NULL, 1));
	CHECK_FALSE(Hash_Remove(NULL, 1));
	LONGS_EQUAL(0, Hash_ValuesStored(NULL));
	LONGS_EQUAL(0, Hash_BucketsUsed(NULL));
	LONGS_EQUAL(0, Hash_BucketsMax(NULL));
	DOUBLES_EQUAL(0, Hash_LoadFactor(NULL), 0.0001);
}
#endif


TEST_GROUP(One)
{
  	hashTable *ht;
	
  	void setup()
  	{
		CHECK(Hash_Create(&ht, 100, true));
		CHECK(ht);
  	}

  	void teardown()
  	{
		Hash_Destroy(&ht);
		POINTERS_EQUAL(NULL, ht);
  	}
};

#if 1
TEST(One, CanInsertOne)
{
	CHECK(Hash_Insert(ht, 1));
}
#endif
#if 1
TEST(One, InsertedValueExists)
{
	CHECK(Hash_Insert(ht, 1));
	CHECK(Hash_Exists(ht, 1));
}
#endif
#if 1
TEST(One, CanRemoveInsertedValue)
{
	CHECK(Hash_Insert(ht, 1));
	CHECK(Hash_Exists(ht, 1));
	CHECK(Hash_Remove(ht, 1));
}
#endif
#if 1
TEST(One, OneValueOneBucket)
{
	CHECK(Hash_Insert(ht, 1));
	LONGS_EQUAL(1, Hash_ValuesStored(ht));
	LONGS_EQUAL(1, Hash_BucketsUsed(ht));
}
#endif
#if 1
TEST(One, ValueDoesNotExistAfterRemovingIt)
{
	CHECK(Hash_Insert(ht, 1));
	CHECK(Hash_Exists(ht, 1));
	CHECK(Hash_Remove(ht, 1));

	CHECK_FALSE(Hash_Exists(ht, 1));
	CHECK_FALSE(Hash_Remove(ht, 1));

	LONGS_EQUAL(0, Hash_ValuesStored(ht));
	LONGS_EQUAL(0, Hash_BucketsUsed(ht));
}
#endif
#if 1
TEST(One, CannotInsertTheSameValueTwice)
{
	CHECK(Hash_Insert(ht, 1));
	CHECK_FALSE(Hash_Insert(ht, 1));
	LONGS_EQUAL(1, Hash_ValuesStored(ht));
	LONGS_EQUAL(1, Hash_BucketsUsed(ht));
}
#endif
#if 1
TEST(One, LoadFactorIsBucketsUsedDividedByBucketsMax)
{
	CHECK(Hash_Insert(ht, 1));
	DOUBLES_EQUAL(1.0/100, Hash_LoadFactor(ht), 0.001);
	DOUBLES_EQUAL(1.0/100, (double)Hash_BucketsUsed(ht)/Hash_BucketsMax(ht), 0.001);
}
#endif


TEST_GROUP(Many_Unique)
{
  	hashTable *ht;
  	const int SIZE = 100;
	
  	void setup()
  	{
		CHECK(Hash_Create(&ht, SIZE, true));
		CHECK(ht);
  	}

  	void teardown()
  	{
		Hash_Destroy(&ht);
		POINTERS_EQUAL(NULL, ht);
  	}

  	enum {ASCENDING = 1, DESCENDING = 0, NEGATE = 2};

  	void insertMany(int howMany, int mode)
	{
		if(mode & ASCENDING)
		{
			for(int i = 0; i < howMany; ++i)
			{
				if(!(mode & NEGATE))
					CHECK(Hash_Insert(ht, i));
				else
					CHECK_FALSE(Hash_Insert(ht, i));
			}
		}
		else
		{
			for(int i = howMany - 1; i >= 0; --i)
			{
				if(!(mode & NEGATE))
					CHECK(Hash_Insert(ht, i));
				else
					CHECK_FALSE(Hash_Insert(ht, i));
			}
		}
	}

  	void existsMany(int howMany, int mode)
	{
		if(mode & ASCENDING)
		{
			for(int i = 0; i < howMany; ++i)
			{
				if(!(mode & NEGATE))
					CHECK(Hash_Exists(ht, i));
				else
					CHECK_FALSE(Hash_Exists(ht, i));
			}
		}
		else
		{
			for(int i = howMany - 1; i >= 0; --i)
			{
				if(!(mode & NEGATE))
					CHECK(Hash_Exists(ht, i));
				else
					CHECK_FALSE(Hash_Exists(ht, i));
			}
		}
	}

  	void removeMany(int howMany, int mode)
	{
		if(mode & ASCENDING)
		{
			for(int i = 0; i < howMany; ++i)
			{
				if(!(mode & NEGATE))
					CHECK(Hash_Remove(ht, i));
				else
					CHECK_FALSE(Hash_Remove(ht, i));
			}
		}
		else
		{
			for(int i = howMany - 1; i >= 0; --i)
			{
				if(!(mode & NEGATE))
					CHECK(Hash_Remove(ht, i));
				else
					CHECK_FALSE(Hash_Remove(ht, i));
			}
		}
	}
};

#if 1
TEST(Many_Unique, CanFillAllBuckets)
{
	insertMany(SIZE, ASCENDING);
	existsMany(SIZE, ASCENDING);
	LONGS_EQUAL(SIZE, Hash_ValuesStored(ht));
	LONGS_EQUAL(SIZE, Hash_BucketsUsed(ht));
	DOUBLES_EQUAL(1.00, Hash_LoadFactor(ht), 0.01);
}
#endif
#if 1
TEST(Many_Unique, DuplicatesRejected)
{
	insertMany(SIZE, ASCENDING);
	existsMany(SIZE, DESCENDING);
	insertMany(SIZE, NEGATE);
	LONGS_EQUAL(SIZE, Hash_ValuesStored(ht));
	LONGS_EQUAL(SIZE, Hash_BucketsUsed(ht));
	DOUBLES_EQUAL(1.00, Hash_LoadFactor(ht), 0.01);
}
#endif
#if 1
TEST(Many_Unique, CanInsertTwiceAsManyValuesAsThereAreBuckets)
{
	insertMany(2 * SIZE, ASCENDING);
	LONGS_EQUAL(2 * SIZE, Hash_ValuesStored(ht));
	LONGS_EQUAL(SIZE, Hash_BucketsUsed(ht));
	DOUBLES_EQUAL(1.00, Hash_LoadFactor(ht), 0.01);
}
#endif
#if 1
TEST(Many_Unique, CanFillAndDeleteAllBuckets)
{
	insertMany(SIZE, ASCENDING);
	existsMany(SIZE, ASCENDING);
	removeMany(SIZE, ASCENDING);

	existsMany(SIZE, NEGATE);
	removeMany(SIZE, NEGATE);

	LONGS_EQUAL(0, Hash_ValuesStored(ht));
	LONGS_EQUAL(0, Hash_BucketsUsed(ht));
	DOUBLES_EQUAL(0, Hash_LoadFactor(ht), 0.01);
}
#endif
#if 1
TEST(Many_Unique, CanFillAndDeleteAllBucketsRepeatedly)
{
	for(int i = 0; i < 10; ++i)
	{
		insertMany(SIZE, DESCENDING);
		existsMany(SIZE, DESCENDING);
		removeMany(SIZE, DESCENDING);
		existsMany(SIZE, DESCENDING | NEGATE);
		removeMany(SIZE, DESCENDING | NEGATE);
		LONGS_EQUAL(0, Hash_ValuesStored(ht));
		LONGS_EQUAL(0, Hash_BucketsUsed(ht));
		DOUBLES_EQUAL(0, Hash_LoadFactor(ht), 0.01);
	}
}
#endif
#if 1
TEST(Many_Unique, HowNotToMakeATestCase)
{
	for(int i = 0; i < 3 * SIZE; i += 2) 		// Add even values
	{
		CHECK(Hash_Insert(ht, i));
	}
	for(int i = 0; i < 3 * SIZE; i += 2)
	{
		CHECK(Hash_Exists(ht, i)); 				// Even values exist
		CHECK_FALSE(Hash_Exists(ht, i + 1)); 	// Odd values do not exist
	}
	for(int i = 0; i < 3 * SIZE; i += 2)
	{
		CHECK(Hash_Insert(ht, i + 1)); 			// Add odd values
	}
	for(int i = 0; i < 3 * SIZE; i += 2)
	{
		CHECK(Hash_Exists(ht, i)); 				// Even values exist
		CHECK(Hash_Exists(ht, i + 1)); 			// Odd values exist
	}
	for(int i = 0; i < 3 * SIZE; i += 2)
	{
		CHECK(Hash_Remove(ht, i + 1)); 			// Remove odd values
	}
	for(int i = 0; i < 3 * SIZE; i += 2)
	{
		CHECK(Hash_Exists(ht, i));  			// Even values exist
		CHECK_FALSE(Hash_Exists(ht, i + 1));  	// Odd values do not exist
	}
	for(int i = 0; i < 3 * SIZE; i += 2)
	{
		CHECK(Hash_Insert(ht, i + 1)); 			// Add odd values
	}
	for(int i = 0; i < 3 * SIZE; i += 2)
	{
		CHECK(Hash_Exists(ht, i)); 				// Even values exist
		CHECK(Hash_Exists(ht, i + 1)); 			// Odd values exist
	}
	for(int i = 0; i < 3 * SIZE; i += 2)
	{
		CHECK(Hash_Remove(ht, i)); 				// Remove even values
	}
	for(int i = 0; i < 3 * SIZE; i += 2)
	{
		CHECK_FALSE(Hash_Exists(ht, i));		// Even values do not exist
		CHECK(Hash_Exists(ht, i + 1));			// Odd values exist
	}
	for(int i = 0; i < 3 * SIZE; i += 2)
	{
		CHECK(Hash_Remove(ht, i + 1)); 			// Remove odd values
	}
	for(int i = 0; i < 3 * SIZE; i += 2)
	{
		CHECK_FALSE(Hash_Exists(ht, i));		// Even values do not exist
		CHECK_FALSE(Hash_Exists(ht, i + 1));	// Odd values do not exist
	}
}
#endif


TEST_GROUP(Many_NonUnique)
{
  	hashTable *ht;
  	const int SIZE = 100;
	
  	void setup()
  	{
		CHECK(Hash_Create(&ht, SIZE, false));
		CHECK(ht);
  	}

  	void teardown()
  	{
		Hash_Destroy(&ht);
		POINTERS_EQUAL(NULL, ht);
  	}
};
#if 1
TEST(Many_NonUnique, CanInsertTheSameValueTwice)
{
	CHECK(Hash_Insert(ht, 1));
	CHECK(Hash_Insert(ht, 1));

	LONGS_EQUAL(2, Hash_Exists(ht, 1));
	LONGS_EQUAL(2, Hash_ValuesStored(ht));
	LONGS_EQUAL(1, Hash_BucketsUsed(ht));
}
#endif
#if 1
TEST(Many_NonUnique, CanInsertAndRemoveDuplicates)
{
	CHECK(Hash_Insert(ht, 1));
	CHECK(Hash_Insert(ht, 1));
	CHECK(Hash_Insert(ht, 1));

	LONGS_EQUAL(3, Hash_Exists(ht, 1));
	CHECK(Hash_Remove(ht, 1));
	LONGS_EQUAL(2, Hash_Exists(ht, 1));
	CHECK(Hash_Remove(ht, 1));
	LONGS_EQUAL(1, Hash_Exists(ht, 1));
	CHECK(Hash_Remove(ht, 1));
	LONGS_EQUAL(0, Hash_Exists(ht, 1));
}
#endif
#if 1
TEST(Many_NonUnique, CanInsertManyDuplicateValues)
{
	int i, j;
	const int duplicates = 100;

	for(i = 0; i < SIZE; ++i)
	{
		for(j = 0; j < duplicates; j++)
		{
			CHECK(Hash_Insert(ht, i));
		}
		LONGS_EQUAL(duplicates, Hash_Exists(ht, i));
		LONGS_EQUAL((i + 1) * duplicates, Hash_ValuesStored(ht));
		LONGS_EQUAL(i + 1, Hash_BucketsUsed(ht));
	}
}
#endif

 // Manual tests - not using output spy
TEST_GROUP(Print)
{
  	hashTable *ht;

  	const int SIZE = 20;
	
  	void setup()
  	{
		CHECK(Hash_Create(&ht, SIZE, true));
		CHECK(ht);
  	}

  	void teardown()
  	{
		Hash_Destroy(&ht);
		POINTERS_EQUAL(NULL, ht);
  	}
};

#if 0
TEST(Print, EmptyHash)
{
	Hash_Print(ht, true);
}
#endif
#if 0
TEST(Print, PrintOne)
{
	Hash_Insert(ht, 1);
	Hash_Print(ht, true);
}
#endif
#if 0
TEST(Print, InsertSomeRemoveSome)
{
	Hash_Print(ht, true);
	Hash_Insert(ht, 1);
	Hash_Insert(ht, 1 + SIZE);
	Hash_Insert(ht, 1 + 2 * SIZE);
	Hash_Insert(ht, 1 + 3 * SIZE);
	Hash_Print(ht, true);
	Hash_Remove(ht, 1 + SIZE);
	Hash_Print(ht, true);
	Hash_Remove(ht, 1 + 3 * SIZE);
	Hash_Print(ht, true);
	Hash_Remove(ht, 1);
	Hash_Print(ht, true);
	Hash_Remove(ht, 1 + 2 * SIZE);
	Hash_Print(ht, true);
}
#endif
#if 0
TEST(Print, AllBucketsFilled)
{
	for(int i = 0; i < SIZE; ++i)
	{
		Hash_Insert(ht, i);
	}

	Hash_Print(ht, true);
}
#endif
#if 0
TEST(Print, EvenBucketsFilled)
{
	for(int i = 0; i < SIZE; i += 2)
	{
		Hash_Insert(ht, i);
	}

	Hash_Print(ht, false);
}
#endif
#if 0
TEST(Print, EveryBucketFilledWithTenValues)
{
	for(int i = 0; i < 10 * SIZE; ++i)
	{
		Hash_Insert(ht, i);
	}

	Hash_Print(ht, true);
}
#endif
#if 0
TEST(Print, InsertSomeRemoveSomeDuplicates)
{
	hashTable *t;
	CHECK(Hash_Create(&t, 10, false));
	Hash_Print(t, true);
	Hash_Insert(t, 1);
	Hash_Insert(t, 1);
	Hash_Insert(t, 1);
	Hash_Insert(t, 1);
	Hash_Print(t, true);
	Hash_Remove(t, 1);
	Hash_Print(t, true);
	Hash_Remove(t, 1);
	Hash_Print(t, true);
	Hash_Remove(t, 1);
	Hash_Print(t, true);
	Hash_Remove(t, 1);
	Hash_Print(t, true);
	Hash_Destroy(&t);
}
#endif
#if 0
TEST(Print, EveryBucketFilledWithTenIdenticalValues)
{
	hashTable *t;
	CHECK(Hash_Create(&t, SIZE, false));
	const int duplicates = 10;

	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < duplicates; j++)
		{
			CHECK(Hash_Insert(t, i));
		}
	}

	Hash_Print(t, false);
	Hash_Destroy(&t);
}
#endif
#if 1
TEST(Print, UniqueVSNonunique)
{
	hashTable *unique, *nonunique;
	CHECK(Hash_Create(&unique, SIZE, true));
	CHECK(Hash_Create(&nonunique, SIZE, false));

	for(int i = 0; i < 2 * SIZE; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			Hash_Insert(unique, i);
			Hash_Insert(nonunique, i);
		}
	}

	printf("\nUnique - duplicate values rejected:\n");
	Hash_Print(unique, false);
	printf("NonUnique - duplicate values accepted:\n");
	Hash_Print(nonunique, false);

	Hash_Destroy(&unique);
	Hash_Destroy(&nonunique);
}
#endif
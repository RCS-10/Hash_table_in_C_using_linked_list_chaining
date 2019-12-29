extern "C"
{
#include "Hash_LL.h"
}

#include "CppUTest/TestHarness.h"
// https://github.com/cpputest/cpputest

TEST_GROUP(ASCENDING)
{
  	hashTable *ht;
	
  	void setup()
  	{
		CHECK(Hash_Create(&ht, 100));
		CHECK(ht);
  	}

  	void teardown()
  	{
		Hash_Destroy(&ht);
		POINTERS_EQUAL(NULL, ht);
  	}
};

#if 1
TEST(ASCENDING, CreateFailsWhenPassingNullPointer)
{
	CHECK_FALSE(Hash_Create(NULL, 100));
}
#endif
#if 1
TEST(ASCENDING, CreateFailsWhenPassingZeroOrNegativeSize)
{
	hashTable *t;
	CHECK_FALSE(Hash_Create(&t, 0));
	CHECK_FALSE(Hash_Create(&t, -1));
}
#endif
#if 1
TEST(ASCENDING, CreateDoesNotCrash)
{
	hashTable *t;
	CHECK(Hash_Create(&t, 100));
	Hash_Destroy(&t);
}
#endif
#if 1
TEST(ASCENDING, CreateAndDestroyAssignsToPointer)
{
	hashTable *t;
	CHECK(Hash_Create(&t, 100));
	CHECK(t);
	Hash_Destroy(&t);
	POINTERS_EQUAL(NULL, t);
}
#endif
#if 1
TEST(ASCENDING, NoValuesAndNoBucketsOnCreation)
{
	LONGS_EQUAL(0, Hash_ValuesStored(ht));
	LONGS_EQUAL(0, Hash_BucketsUsed(ht));
}
#endif
#if 1
TEST(ASCENDING, MaxBucketsDeterminedByInitialization)
{
	hashTable *t;
	CHECK(Hash_Create(&t, 10));
	LONGS_EQUAL(10, Hash_BucketsMax(t));
	Hash_Destroy(&t);
	CHECK(Hash_Create(&t, 10000));
	LONGS_EQUAL(10000, Hash_BucketsMax(t));
	Hash_Destroy(&t);
}
#endif
#if 1
TEST(ASCENDING, LoadFactorIsZeroOnCreation)
{
	DOUBLES_EQUAL(0, Hash_LoadFactor(ht), 0.01);
}
#endif
#if 1
TEST(ASCENDING, FunctionsReturnZeroWhenPassedNull)
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
		CHECK(Hash_Create(&ht, 100));
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


TEST_GROUP(Many)
{
  	hashTable *ht;
  	const int SIZE = 100;
	
  	void setup()
  	{
		CHECK(Hash_Create(&ht, SIZE));
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
TEST(Many, CanFillAllBuckets)
{
	insertMany(SIZE, ASCENDING);
	existsMany(SIZE, ASCENDING);
	LONGS_EQUAL(SIZE, Hash_ValuesStored(ht));
	LONGS_EQUAL(SIZE, Hash_BucketsUsed(ht));
	DOUBLES_EQUAL(1.00, Hash_LoadFactor(ht), 0.01);
}
#endif
#if 1
TEST(Many, DuplicatesRejected)
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
TEST(Many, CanInsertTwiceAsManyValuesAsThereAreBuckets)
{
	insertMany(2 * SIZE, ASCENDING);
	LONGS_EQUAL(2 * SIZE, Hash_ValuesStored(ht));
	LONGS_EQUAL(SIZE, Hash_BucketsUsed(ht));
	DOUBLES_EQUAL(1.00, Hash_LoadFactor(ht), 0.01);
}
#endif
#if 1
TEST(Many, CanFillAndDeleteAllBuckets)
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
TEST(Many, CanFillAndDeleteAllBucketsRepeatedly)
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
TEST(Many, HowNotToMakeATestCase)
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


TEST_GROUP(Print) // Not using spy - visual inspection only
{
  	hashTable *ht;

  	const int SIZE = 20;
	
  	void setup()
  	{
		CHECK(Hash_Create(&ht, SIZE));
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
#if 1
TEST(Print, EveryBucketFilledWithTenValues)
{
	for(int i = 0; i < 10 * SIZE; ++i)
	{
		Hash_Insert(ht, i);
	}

	Hash_Print(ht, true);
}
#endif
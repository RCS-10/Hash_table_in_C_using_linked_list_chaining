extern "C"
{
#include "Hash_LL.h"
#include <time.h>
#include <stdlib.h>
}

#include "CppUTest/TestHarness.h"
// https://github.com/cpputest/cpputest

TEST_GROUP(None)
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
TEST(None, CreateFailsWhenPassingNullPointer)
{
	CHECK_FALSE(Hash_Create(NULL, 100));
}
#endif
#if 1
TEST(None, CreateFailsWhenPassingZeroOrNegativeSize)
{
	hashTable *t;
	CHECK_FALSE(Hash_Create(&t, 0));
	CHECK_FALSE(Hash_Create(&t, -1));
}
#endif
#if 1
TEST(None, CreateDoesNotCrash)
{
	hashTable *t;
	CHECK(Hash_Create(&t, 100));
	Hash_Destroy(&t);
}
#endif
#if 1
TEST(None, CreateAndDestroyAssignsToPointer)
{
	hashTable *t;
	CHECK(Hash_Create(&t, 100));
	CHECK(t);
	Hash_Destroy(&t);
	POINTERS_EQUAL(NULL, t);
}
#endif
#if 1
TEST(None, EmptyHasNoValuesAndNoBuckets)
{
	LONGS_EQUAL(0, Hash_ValuesStored(ht));
	LONGS_EQUAL(0, Hash_BucketsUsed(ht));
}
#endif
#if 1
TEST(None, BucketsMaxDeterminedByInitialization)
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
TEST(None, LoadFactorIsZeroWhenEmpty)
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
TEST(None, LoadFactorIsBucketsUsedDividedByBucketsMax)
{
	CHECK(Hash_Insert(ht, 1));
	DOUBLES_EQUAL(1.0/100, Hash_LoadFactor(ht), 0.001);
	DOUBLES_EQUAL(1.0/100, (double)Hash_BucketsUsed(ht)/Hash_BucketsMax(ht), 0.001);
}
#endif


TEST_GROUP(Many)
{
  	hashTable *ht;
  	#define SIZE 100
	
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

  	enum {NONE = 0, REVERSE = 1, NEGATE = 2};

  	void insertMany(int howMany, int modifier)
	{
		if(!(modifier & REVERSE))
		{
			for(int i = 0; i < howMany; ++i)
			{
				if(!(modifier & NEGATE))
					CHECK(Hash_Insert(ht, i));
				else
					CHECK_FALSE(Hash_Insert(ht, i));
			}
		}
		else
		{
			for(int i = howMany - 1; i >= 0; --i)
			{
				if(!(modifier & NEGATE))
					CHECK(Hash_Insert(ht, i));
				else
					CHECK_FALSE(Hash_Insert(ht, i));
			}
		}
	}

  	void existsMany(int howMany, int modifier)
	{
		if(!(modifier & REVERSE))
		{
			for(int i = 0; i < howMany; ++i)
			{
				if(!(modifier & NEGATE))
					CHECK(Hash_Exists(ht, i));
				else
					CHECK_FALSE(Hash_Exists(ht, i));
			}
		}
		else
		{
			for(int i = howMany - 1; i >= 0; --i)
			{
				if(!(modifier & NEGATE))
					CHECK(Hash_Exists(ht, i));
				else
					CHECK_FALSE(Hash_Exists(ht, i));
			}
		}
	}

  	void removeMany(int howMany, int modifier)
	{
		if(!(modifier & REVERSE))
		{
			for(int i = 0; i < howMany; ++i)
			{
				if(!(modifier & NEGATE))
					CHECK(Hash_Remove(ht, i));
				else
					CHECK_FALSE(Hash_Remove(ht, i));
			}
		}
		else
		{
			for(int i = howMany - 1; i >= 0; --i)
			{
				if(!(modifier & NEGATE))
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
	insertMany(SIZE, NONE);
	existsMany(SIZE, NONE);
	LONGS_EQUAL(SIZE, Hash_ValuesStored(ht));
	LONGS_EQUAL(SIZE, Hash_BucketsUsed(ht));
	DOUBLES_EQUAL(1.00, Hash_LoadFactor(ht), 0.01);
}
#endif
#if 1
TEST(Many, DuplicatesRejected)
{
	insertMany(SIZE, NONE);
	existsMany(SIZE, REVERSE);
	insertMany(SIZE, NEGATE);
	LONGS_EQUAL(SIZE, Hash_ValuesStored(ht));
	LONGS_EQUAL(SIZE, Hash_BucketsUsed(ht));
	DOUBLES_EQUAL(1.00, Hash_LoadFactor(ht), 0.01);
}
#endif
#if 1
TEST(Many, CanInsertTwiceAsManyValuesAsThereAreBuckets)
{
	insertMany(2 * SIZE, NONE);
	LONGS_EQUAL(2 * SIZE, Hash_ValuesStored(ht));
	LONGS_EQUAL(SIZE, Hash_BucketsUsed(ht));
	DOUBLES_EQUAL(1.00, Hash_LoadFactor(ht), 0.01);
}
#endif
#if 1
TEST(Many, CanFillAndDeleteAllBuckets)
{
	insertMany(SIZE, NONE);
	existsMany(SIZE, NONE);
	removeMany(SIZE, NONE);

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
		insertMany(SIZE, REVERSE);
		existsMany(SIZE, REVERSE);
		removeMany(SIZE, REVERSE);
		existsMany(SIZE, REVERSE | NEGATE);
		removeMany(SIZE, REVERSE | NEGATE);
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
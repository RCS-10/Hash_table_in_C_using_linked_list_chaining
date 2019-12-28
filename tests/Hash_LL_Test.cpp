extern "C"
{
#include "Hash_LL.h"
#include <time.h>
#include <stdlib.h>
}

#include "CppUTest/TestHarness.h"
// https://github.com/cpputest/cpputest

TEST_GROUP(Hash_LL_Test)
{
  	hashTable *ht;
	
  	void setup()
  	{

  	}

  	void teardown()
  	{

  	}

  	#define SIZE(x) (sizeof(x)/sizeof(int))
};

#if 1
TEST(Hash_LL_Test, Test)
{
	FAIL("Start here");
}
#endif


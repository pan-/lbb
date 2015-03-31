#include <gtest/gtest.h>
#include <lbb/threading.h>

using lbb::mutex;
using lbb::lock_guard;

TEST(lock_guard, mutex_should_be_locked_after_construction) { 
	mutex m;
	lock_guard<mutex> lock(m);
	EXPECT_FALSE(m.try_lock());
}


TEST(lock_guard, mutex_should_be_unlocked_after_destruction) { 
	mutex m;
	{
		lock_guard<mutex> lock(m);		
	}

	EXPECT_TRUE(m.try_lock());
	m.unlock();
}


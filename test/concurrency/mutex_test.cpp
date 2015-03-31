#include <gtest/gtest.h>
#include <lbb/threading.h>

TEST(mutex, mutex_should_not_be_lockable_after_a_lock) { 
	lbb::mutex m;

	m.lock();
	EXPECT_FALSE(m.try_lock());
	m.unlock();
}


TEST(mutex, mutex_should_be_lockable_after_an_unlock) { 
	lbb::mutex m;

	m.lock();
	m.unlock();
	EXPECT_TRUE(m.try_lock());
	m.unlock();
}


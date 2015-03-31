#include <gtest/gtest.h>
#include <lbb/threading.h>

using lbb::mutex;
using lbb::unique_lock;
using lbb::move;

TEST(unique_lock, empty_constructor_should_be_correctly_initialized) { 
	unique_lock<mutex> lock;

	EXPECT_FALSE(lock);
	EXPECT_FALSE(lock.owns_lock());
	EXPECT_EQ(0, lock.mutex());
}


TEST(unique_lock, constructor_with_mutex_should_lock_the_mutex) {
	mutex m; 
	unique_lock<mutex> lock(m);

	EXPECT_TRUE(lock);
	EXPECT_TRUE(lock.owns_lock());
	EXPECT_EQ(&m, lock.mutex());
	EXPECT_FALSE(m.try_lock());
}


TEST(unique_lock, move_constructor_should_acquire_the_mutex_and_let_it_locked_if_previously_locked) {
	mutex m; 
	unique_lock<mutex> old_lock(m);
	unique_lock<mutex> lock(move(old_lock));

	EXPECT_TRUE(lock);
	EXPECT_TRUE(lock.owns_lock());
	EXPECT_EQ(&m, lock.mutex());
	EXPECT_FALSE(m.try_lock());
	EXPECT_FALSE(old_lock);
	EXPECT_FALSE(old_lock.owns_lock());
	EXPECT_EQ(0, old_lock.mutex());
}


TEST(unique_lock, move_constructor_should_acquire_the_mutex_and_let_it_unlocked_if_previously_unlocked) {
	mutex m; 
	unique_lock<mutex> old_lock(m);
	old_lock.unlock();
	unique_lock<mutex> lock(move(old_lock));

	EXPECT_FALSE(lock);
	EXPECT_FALSE(lock.owns_lock());
	EXPECT_EQ(&m, lock.mutex());
	EXPECT_TRUE(m.try_lock());
	EXPECT_FALSE(old_lock);
	EXPECT_FALSE(old_lock.owns_lock());
	EXPECT_EQ(0, old_lock.mutex());
}


TEST(unique_lock, destructor_should_release_the_mutex_if_locked) {
	mutex m; 

	{ 
		unique_lock<mutex> lock(m);
	}

	EXPECT_TRUE(m.try_lock());
	m.unlock();
}


TEST(unique_lock, destructor_should_do_nothing_if_the_mutex_is_unlocked) {
	mutex m; 

	{ 
		unique_lock<mutex> lock(m);
		lock.unlock();
	}

	EXPECT_TRUE(m.try_lock());
	m.unlock();
}


TEST(unique_lock, move_assignemet_should_release_the_previous_mutex_replace_it_with_the_new_one) {
	mutex old_mutex; 
	unique_lock<mutex> old_lock(old_mutex);
	mutex m;
	unique_lock<mutex> lock(m);

	lock = move(old_lock);

	EXPECT_TRUE(lock);
	EXPECT_TRUE(lock.owns_lock());
	EXPECT_EQ(&old_mutex, lock.mutex());
	EXPECT_FALSE(old_mutex.try_lock());
	EXPECT_FALSE(old_lock);
	EXPECT_FALSE(old_lock.owns_lock());
	EXPECT_EQ(0, old_lock.mutex());
	EXPECT_TRUE(m.try_lock());
	m.unlock();
}

TEST(unique_lock, lock_throw_if_no_mutex_is_available) {
	unique_lock<mutex> lock;
	EXPECT_THROW(lock.lock(), lbb::system_error);
}

TEST(unique_lock, lock_throw_if_mutex_is_already_locked) {
	mutex m;
	unique_lock<mutex> lock(m);
	EXPECT_THROW(lock.lock(), lbb::system_error);
}

TEST(unique_lock, lock_should_lock_if_mutex_was_not_locked) {
	mutex m;
	unique_lock<mutex> lock(m);
	lock.unlock();
	lock.lock();
	EXPECT_TRUE(lock);
	EXPECT_TRUE(lock.owns_lock());
	EXPECT_FALSE(m.try_lock());
}


TEST(unique_lock, try_lock_throw_if_no_mutex_is_available) {
	unique_lock<mutex> lock;
	EXPECT_THROW(lock.try_lock(), lbb::system_error);
}

TEST(unique_lock, try_lock_throw_if_mutex_is_already_owned) {
	mutex m;
	unique_lock<mutex> lock(m);
	EXPECT_THROW(lock.try_lock(), lbb::system_error);
}

TEST(unique_lock, try_lock_should_return_true_if_mutex_was_not_owned_and_not_owned_elsewhere) {
	mutex m;
	unique_lock<mutex> lock(m);
	lock.unlock();
	EXPECT_TRUE(lock.try_lock());
	EXPECT_TRUE(lock);
	EXPECT_TRUE(lock.owns_lock());
	EXPECT_FALSE(m.try_lock());
}

TEST(unique_lock, try_lock_should_return_false_if_mutex_was_not_owned_and_owned_elsewhere) {
	mutex m;
	unique_lock<mutex> lock(m);
	lock.unlock();
	m.lock();
	EXPECT_FALSE(lock.try_lock());
	EXPECT_FALSE(lock);
	EXPECT_FALSE(lock.owns_lock());
	m.unlock();
}


TEST(unique_lock, unlock_throw_if_no_mutex_is_available) {
	unique_lock<mutex> lock;
	EXPECT_THROW(lock.unlock(), lbb::system_error);
}

TEST(unique_lock, unlock_throw_if_mutex_is_not_owned) {
	mutex m;
	unique_lock<mutex> lock(m);
	lock.unlock();
	EXPECT_THROW(lock.unlock(), lbb::system_error);
}

TEST(unique_lock, unlock_should_succeed_if_mutex_is_available_and_not_locked) {
	mutex m;
	unique_lock<mutex> lock(m);
	lock.unlock();
	EXPECT_FALSE(lock);
	EXPECT_FALSE(lock.owns_lock());
	EXPECT_TRUE(m.try_lock());
	m.unlock();
}

TEST(unique_lock, swap_should_exchange_the_state_of_objects) {
	mutex m;
	unique_lock<mutex> lock(m);
	unique_lock<mutex> other;
	lock.swap(other);

	EXPECT_FALSE(lock);
	EXPECT_FALSE(lock.owns_lock());
	EXPECT_EQ(0, lock.mutex());

	EXPECT_TRUE(other);
	EXPECT_TRUE(other.owns_lock());
	EXPECT_EQ(&m, other.mutex());
}


TEST(unique_lock, release_should_return_the_mutex_and_not_touch_it_state) {
	mutex m;
	unique_lock<mutex> lock(m);

	EXPECT_EQ(&m, lock.release());
	EXPECT_FALSE(lock);
	EXPECT_FALSE(lock.owns_lock());
	EXPECT_EQ(0, lock.mutex());

	EXPECT_FALSE(m.try_lock());

	m.unlock();
}



//other methods have been tested all along !!!






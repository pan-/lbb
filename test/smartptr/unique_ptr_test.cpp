#include <gtest/gtest.h>
#include <lbb/smartptr.h>

using lbb::unique_ptr;
using lbb::move;

namespace { 

struct foo_struct { 
	bool test() { return true; }
};


struct destruct_test { 
	destruct_test(bool& destroyed) : _destroyed(destroyed) { 
		_destroyed = false;
	}

	~destruct_test() { 
		_destroyed = true;
	}
private:
	bool& _destroyed;
};

}


TEST(unique_ptr, should_be_null_when_default_initialized) {
	unique_ptr<foo_struct> under_test;
	EXPECT_FALSE(under_test);
	EXPECT_EQ(0, under_test.get());
} 

TEST(unique_ptr, should_be_initialized_with_right_ptr) {
	foo_struct* ptr = new foo_struct();
	unique_ptr<foo_struct> under_test(ptr);
	EXPECT_TRUE(under_test);
	EXPECT_EQ(ptr, under_test.get());
} 

TEST(unique_ptr, after_move_source_get_should_return_null) {
	foo_struct* ptr = new foo_struct();
	unique_ptr<foo_struct> source(ptr);
	unique_ptr<foo_struct> sink(move(source));

	EXPECT_FALSE(source);
	EXPECT_EQ(0, source.get());
} 

TEST(unique_ptr, after_move_sink_get_should_return_previous_source_ptr) {
	foo_struct* ptr = new foo_struct();
	unique_ptr<foo_struct> source(ptr);
	unique_ptr<foo_struct> sink(move(source));

	EXPECT_TRUE(sink);
	EXPECT_EQ(ptr, sink.get());
} 


TEST(unique_ptr, ptr_destructor_should_be_called) {
	bool ptr_destroyed;

	{ 
		unique_ptr<destruct_test> foo(new destruct_test(ptr_destroyed));
	}

	EXPECT_TRUE(ptr_destroyed);
} 


TEST(unique_ptr, ptr_assignement_should_delete_old_ptr_and_replace_it_by_the_new_one) {
	bool old_ptr_destroyed;
	bool current_ptr_destroyed;

	unique_ptr<destruct_test> under_test(new destruct_test(old_ptr_destroyed));
	destruct_test* new_ptr = new destruct_test(current_ptr_destroyed);
	under_test = new_ptr;

	EXPECT_TRUE(old_ptr_destroyed);
	EXPECT_FALSE(current_ptr_destroyed);
	EXPECT_TRUE(under_test);
	EXPECT_EQ(new_ptr, under_test.get());
} 

TEST(unique_ptr, move_assignement_should_delete_sink_ptr_and_replace_it_by_source) {
	bool source_destroyed;
	bool sink_destroyed;

	destruct_test* source_ptr = new destruct_test(source_destroyed);
	unique_ptr<destruct_test> source(source_ptr);
	unique_ptr<destruct_test> sink(new destruct_test(sink_destroyed));

	sink = move(source);

	EXPECT_TRUE(sink_destroyed);
	EXPECT_FALSE(source_destroyed);
	EXPECT_FALSE(source);
	EXPECT_TRUE(sink);
	EXPECT_EQ(source_ptr, sink.get());
	EXPECT_EQ(0, source.get());
} 


TEST(unique_ptr, release_should_return_the_ptr_held_and_invalidate_the_unique_ptr) {

	foo_struct* ptr = new foo_struct();
	unique_ptr<foo_struct> under_test(ptr);
	foo_struct* released_ptr = under_test.release();

	EXPECT_EQ(ptr, released_ptr);
	EXPECT_FALSE(under_test);
	EXPECT_EQ(0, under_test.get());

	delete released_ptr;
} 


TEST(unique_ptr, reset_should_delete_the_previous_ptr_and_assign_the_new_one) { 
	bool old_ptr_destroyed;
	bool current_ptr_destroyed;

	unique_ptr<destruct_test> under_test(new destruct_test(old_ptr_destroyed));
	destruct_test* new_ptr = new destruct_test(current_ptr_destroyed);
	under_test.reset(new_ptr);

	EXPECT_TRUE(old_ptr_destroyed);
	EXPECT_FALSE(current_ptr_destroyed);
	EXPECT_TRUE(under_test);
	EXPECT_EQ(new_ptr, under_test.get());
}


TEST(unique_ptr, swap_should_swap_ptr) { 
	foo_struct* left_ptr = new foo_struct();
	foo_struct* right_ptr = new foo_struct();

	unique_ptr<foo_struct> left(left_ptr); 
	unique_ptr<foo_struct> right(right_ptr); 

	left.swap(right);

	EXPECT_EQ(right_ptr, left.get());
	EXPECT_EQ(left_ptr, right.get());
}


//TODO : comparison operator !!!







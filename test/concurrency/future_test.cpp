#include <string>

#include <gtest/gtest.h>

#include <lbb/threading.h>

//instantiation
template class lbb::future<int>;
template class lbb::promise<int>;
template class lbb::promise_handler<int>;


template<typename T>
void set_promise_value(lbb::promise<T>& p, T value) { 
	p.set_value(value);
}

template<typename T, typename E>
void set_promise_exception(lbb::promise<T>& p, E e) { 
	p.set_exception(e);
}


TEST(future, should_not_be_valid_with_default_constructor) { 
	lbb::future<int> f;
	EXPECT_FALSE(f.valid());
}


TEST(future, get_should_throw_if_no_shared_state_is_available) { 
	lbb::future<int> f;
	EXPECT_THROW(f.get(), lbb::future_error);
}


TEST(future, wait_should_throw_if_no_shared_state_is_available) { 
	lbb::future<int> f;
	EXPECT_THROW(f.wait(), lbb::future_error);
}


TEST(future, should_be_valid_when_constructed_from_a_promise) { 
	lbb::promise<int> p;
	lbb::future<int> f = p.get_future();
	EXPECT_TRUE(f.valid());
}


TEST(future, should_be_correctly_move_constructed) { 
	lbb::promise<int> p;
	lbb::future<int> old_f = p.get_future();
	lbb::future<int> f = lbb::move(old_f);
	EXPECT_TRUE(f.valid());
	EXPECT_FALSE(old_f.valid());
}


TEST(future, should_be_correctly_move_assigned) { 
	lbb::promise<int> p;
	lbb::future<int> old_f = p.get_future();
	lbb::future<int> f;
	f = lbb::move(old_f);
	EXPECT_TRUE(f.valid());
	EXPECT_FALSE(old_f.valid());
}


TEST(future, wait_should_wait_for_the_value) { 
	lbb::promise<int> p;
	lbb::future<int> f = p.get_future();
	lbb::thread(set_promise_value<int>, lbb::ref(p), 42).join();
	f.wait();
	EXPECT_TRUE(f.valid());
}


TEST(future, get_should_return_the_value_and_invalidate_future_state) { 
	lbb::promise<int> p;
	lbb::future<int> f = p.get_future();
	lbb::thread(set_promise_value<int>, lbb::ref(p), 42).join();
	EXPECT_EQ(42, f.get());
	EXPECT_FALSE(f.valid());
}


TEST(future, broken_promise_should_throw_on_get) { 
	lbb::future<int> f;
	{ 
		lbb::promise<int> p;
		f = p.get_future();
	}
	EXPECT_THROW(f.get(), lbb::future_error);
	EXPECT_FALSE(f.valid());
}


TEST(future, promise_filled_with_exception_should_throw_on_get) { 
	lbb::promise<int> p;
	lbb::future<int> f = p.get_future();
	lbb::thread(set_promise_exception<int, std::string>, lbb::ref(p), std::string("Hello World !")).join();
	EXPECT_THROW(f.get(), std::string);
	EXPECT_FALSE(f.valid());
}


void void_then(lbb::future<int> v) { 

}

int int_then(lbb::future<int> v) { 
	return v.get() * 2;
}


TEST(future, void_then_should_let_the_future_in_invalid_state) { 
	lbb::promise<int> p;
	lbb::future<int> f = p.get_future();
	f.then(&void_then);
	EXPECT_FALSE(f.valid());
}

TEST(future, then_should_let_the_future_in_invalid_state) { 
	lbb::promise<int> p;
	lbb::future<int> f = p.get_future();
	lbb::future<int> ft = f.then(&int_then);
	EXPECT_FALSE(f.valid());
	EXPECT_TRUE(ft.valid());
	p.set_value(42);
}


TEST(future, then_should_set_the_value_in_the_next_future) { 
	lbb::promise<int> p;
	lbb::future<int> f = p.get_future().then(&int_then);
	p.set_value(42);
	EXPECT_EQ(84, f.get());
}


TEST(future, then_should_throw_if_there_is_no_shared_state) { 
	lbb::future<int> f;
	EXPECT_THROW(f.then(&int_then), lbb::future_error);
}


TEST(future, then_should_throw_if_the_future_has_already_been_retrieved) { 
	lbb::promise<int> p;
	lbb::future<int> f = p.get_future();
	p.set_value(42);
	f.get();
	EXPECT_THROW(f.then(&int_then), lbb::future_error);
}


TEST(future, then_should_call_the_callback_if_the_promise_is_already_satisfied) { 
	lbb::promise<int> p;
	lbb::future<int> f = p.get_future();
	p.set_value(42);
	lbb::future<int> ft = f.then(&int_then);
	EXPECT_EQ(84, ft.get());
}







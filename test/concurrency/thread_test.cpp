#include <gtest/gtest.h>
#include <lbb/threading.h>

#include <iostream>

using lbb::thread;
using std::cout;
using std::endl;

void empty() { 
}

void unary(int val1) { 
}

void binary(int val1, int val2) { 
}

TEST(thread, start_empty) { 
	thread t(empty);
	t.join();
}

TEST(thread, start_unary) { 
	thread t(unary, 0);
	t.join();
}


TEST(thread, start_delayed) { 
	thread t;
	t = thread(binary, 4, 2);
	t.join();
}





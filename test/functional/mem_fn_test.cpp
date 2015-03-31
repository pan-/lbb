#include <cstdlib>
#include <gtest/gtest.h>
#include <lbb/functional.h>

using lbb::mem_fn;

namespace { 

struct tester { 

	tester(int threshold) : _threshold(threshold) { }

	int threshold() const { return _threshold; }

	void set_threshold(int threshold) { _threshold = threshold; }

	int unit() const { 
		return _threshold; 
	}

	int unary(int arg1) const { 
		return _threshold + arg1; 
	}

	int binary(int arg1, int arg2) const { 
		return _threshold + arg1 + arg2; 
	}

	int ternary(int arg1, int arg2, int arg3) const { 
		return _threshold + arg1 + arg2 + arg3; 
	}

	int quaternary(int arg1, int arg2, int arg3, int arg4) const { 
		return _threshold + arg1 + arg2 + arg3 + arg4; 
	}


private:
	int _threshold;
};

int generate_int() { 
	return rand() % 100;
}

}

TEST(mem_fn, should_handle_unit_function) {
	int threshold = generate_int();
	tester t(threshold);
	EXPECT_EQ(t.unit(), mem_fn(&tester::unit)(&t));
}

TEST(mem_fn, should_handle_unary_function) {
	int threshold = generate_int();
	int arg1 = generate_int();
	tester t(threshold);
	EXPECT_EQ(t.unary(arg1), mem_fn(&tester::unary)(&t, arg1));
}

TEST(mem_fn, should_handle_binary_function) {
	int threshold = generate_int();
	int arg1 = generate_int();
	int arg2 = generate_int();
	tester t(threshold);
	EXPECT_EQ(t.binary(arg1, arg2), mem_fn(&tester::binary)(&t, arg1, arg2));
}

TEST(mem_fn, should_handle_ternary_function) {
	int threshold = generate_int();
	int arg1 = generate_int();
	int arg2 = generate_int();
	int arg3 = generate_int();
	tester t(threshold);
	EXPECT_EQ(t.ternary(arg1, arg2, arg3), mem_fn(&tester::ternary)(&t, arg1, arg2, arg3));
}

TEST(mem_fn, should_handle_quaternary_function) {
	int threshold = generate_int();
	int arg1 = generate_int();
	int arg2 = generate_int();
	int arg3 = generate_int();
	int arg4 = generate_int();
	tester t(threshold);
	EXPECT_EQ(t.quaternary(arg1, arg2, arg3, arg4), mem_fn(&tester::quaternary)(&t, arg1, arg2, arg3, arg4));
}

TEST(mem_fn, should_handle_mutation) {
	tester t(generate_int());
	int new_threshold = generate_int();
	mem_fn(&tester::set_threshold)(&t, new_threshold);
	EXPECT_EQ(new_threshold, t.threshold());
}

















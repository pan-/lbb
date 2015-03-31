#include <cstdlib>

#include <gtest/gtest.h>
#include <lbb/functional.h>

using lbb::bind;
using lbb::placeholders::_1;
using lbb::placeholders::_2;
using lbb::placeholders::_3;
using lbb::placeholders::_4;
using lbb::placeholders::_5;

using lbb::function;

namespace { 

int generate_int() { 
	return rand() % 100;
}

int unary(int arg1) { 
	return arg1;
}

int binary(int arg1, int arg2) { 
	return arg1 + arg2;
}

int ternary(int arg1, int arg2, int arg3) { 
	return arg1 + arg2 + arg3;
}

int quaternary(int arg1, int arg2, int arg3, int arg4) { 
	return arg1 + arg2 + arg3 + arg4;
}

int quinary(int arg1, int arg2, int arg3, int arg4, int arg5) { 
	return arg1 + arg2 + arg3 + arg4 + arg5;
}


struct test_class { 

	test_class(int threshold) : _threshold(threshold) { }

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


}


TEST(bind, should_bind_one_arg) { 
	int arg1 = generate_int();
	test_class tester(arg1);
	
	//FOR FUNCTION
	EXPECT_EQ(unary(arg1), bind(unary, arg1)());
	EXPECT_EQ(binary(arg1, 0), bind(binary, arg1, _1)(0));
	EXPECT_EQ(ternary(arg1, 0, 0), bind(ternary, arg1, _1, _2)(0, 0));
	EXPECT_EQ(quaternary(arg1, 0, 0, 0), bind(quaternary, arg1, _1, _2, _3)(0, 0, 0));
	EXPECT_EQ(quinary(arg1, 0, 0, 0, 0), bind(quinary, arg1, _1, _2, _3, _4)(0, 0, 0, 0));

	// //FOR OBJECT
	EXPECT_EQ(tester.unit(), bind(&test_class::unit, &tester)());
	EXPECT_EQ(tester.unary(0), bind(&test_class::unary, &tester, _1)(0));
	EXPECT_EQ(tester.binary(0, 0), bind(&test_class::binary, &tester, _1, _2)(0, 0));
	EXPECT_EQ(tester.ternary(0, 0, 0), bind(&test_class::ternary, &tester, _1, _2, _3)(0, 0, 0));
	EXPECT_EQ(tester.quaternary(0, 0, 0, 0), bind(&test_class::quaternary, &tester, _1, _2, _3, _4)(0, 0, 0, 0));
}


TEST(bind, should_bind_two_arg) { 
	int arg1 = generate_int();
	int arg2 = generate_int();
	test_class tester(arg1);
	
	//FOR FUNCTION
	EXPECT_EQ(binary(arg1, arg2), bind(binary, arg1, arg2)());
	EXPECT_EQ(ternary(arg1, arg2, 0), bind(ternary, arg1, arg2, _1)(0));
	EXPECT_EQ(quaternary(arg1, arg2, 0, 0), bind(quaternary, arg1, arg2, _1, _2)(0, 0));
	EXPECT_EQ(quinary(arg1, arg2, 0, 0, 0), bind(quinary, arg1, arg2, _1, _2, _3)(0, 0, 0));

	//FOR OBJECT
	EXPECT_EQ(tester.unary(arg2), bind(&test_class::unary, &tester, arg2)());
	EXPECT_EQ(tester.binary(arg2, 0), bind(&test_class::binary, &tester, arg2, _1)(0));
	EXPECT_EQ(tester.ternary(arg2, 0, 0), bind(&test_class::ternary, &tester, arg2, _1, _2)(0, 0));
	EXPECT_EQ(tester.quaternary(arg2, 0, 0, 0), bind(&test_class::quaternary, &tester, arg2, _1, _2, _3)(0, 0, 0));
}


TEST(bind, should_bind_three_arg) { 
	int arg1 = generate_int();
	int arg2 = generate_int();
	int arg3 = generate_int();
	test_class tester(arg1);
		
	//FOR FUNCTION
	EXPECT_EQ(ternary(arg1, arg2, arg3), bind(ternary, arg1, arg2, arg3)());
	EXPECT_EQ(quaternary(arg1, arg2, arg3, 0), bind(quaternary, arg1, arg2, arg3, _1)(0));
	EXPECT_EQ(quinary(arg1, arg2, arg3, 0, 0), bind(quinary, arg1, arg2, arg3, _1, _2)(0, 0));

	//FOR OBJECT
	EXPECT_EQ(tester.binary(arg2, arg3), bind(&test_class::binary, &tester, arg2, arg3)());
	EXPECT_EQ(tester.ternary(arg2, arg3, 0), bind(&test_class::ternary, &tester, arg2, arg3, _1)(0));
	EXPECT_EQ(tester.quaternary(arg2, arg3, 0, 0), bind(&test_class::quaternary, &tester, arg2, arg3, _1, _2)(0, 0));
}


TEST(bind, should_bind_four_arg) { 
	int arg1 = generate_int();
	int arg2 = generate_int();
	int arg3 = generate_int();
	int arg4 = generate_int();
	test_class tester(arg1);
	
	//FOR FUNCTION	
	EXPECT_EQ(quaternary(arg1, arg2, arg3, arg4), bind(quaternary, arg1, arg2, arg3, arg4)());
	EXPECT_EQ(quinary(arg1, arg2, arg3, arg4, 0), bind(quinary, arg1, arg2, arg3, arg4, _1)(0));

	//FOR OBJECT
	EXPECT_EQ(tester.ternary(arg2, arg3, arg4), bind(&test_class::ternary, &tester, arg2, arg3, arg4)());
	EXPECT_EQ(tester.quaternary(arg2, arg3, arg4, 0), bind(&test_class::quaternary, &tester, arg2, arg3, arg4, _1)(0));
}


TEST(bind, should_bind_bind) { 
	int arg1 = generate_int();
	int arg2 = generate_int();
	int arg3 = generate_int();
	int arg4 = generate_int();
	int arg5 = generate_int();	
	test_class tester(arg1);

	
	//FOR FUNCTION
	EXPECT_EQ(binary(arg1, arg2), bind(bind(binary, arg1, _1), arg2)());
	EXPECT_EQ(ternary(arg1, arg2, arg3), bind(bind(ternary, arg1, _1, _2), arg2, _1)(arg3));
	EXPECT_EQ(quaternary(arg1, arg2, arg3, arg4), bind(bind(quaternary, arg1, _1, _2, _3), arg2, _1, _2)(arg3, arg4));	
	EXPECT_EQ(quinary(arg1, arg2, arg3, arg4, arg5), bind(bind(quinary, arg1, _1, _2, _3, _4), arg2, _1, _2, _3)(arg3, arg4, arg5));

	// //FOR OBJECT
	EXPECT_EQ(tester.unary(arg1), bind(bind(&test_class::unary, &tester, _1), arg1)());
	EXPECT_EQ(tester.binary(arg1, arg2), bind(bind(&test_class::binary, &tester, _1, _2), arg1, _1)(arg2));
	EXPECT_EQ(tester.ternary(arg1, arg2, arg3), bind(bind(&test_class::ternary, &tester, _1, _2, _3), arg1, _1, _2)(arg2, arg3));	
	EXPECT_EQ(tester.quaternary(arg1, arg2, arg3, arg4), bind(bind(&test_class::quaternary, &tester, _1, _2, _3, _4), arg1, _1, _2, _3)(arg2, arg3, arg4));	
}


TEST(bind, should_bind_function) { 
	int arg1 = generate_int();
	int arg2 = generate_int();
	int arg3 = generate_int();
	int arg4 = generate_int();
	int arg5 = generate_int();	
	test_class tester(arg1);

	function<int(int)> unary_function(unary);
	function<int(int, int)> binary_function(binary);
	function<int(int, int, int)> ternary_function(ternary);
	function<int(int, int, int, int)> quaternary_function(quaternary);	
	function<int(int, int, int, int, int)> quinary_function(quinary);	

	EXPECT_EQ(unary(arg1), bind(unary_function, arg1)());
	EXPECT_EQ(binary(arg1, arg2), bind(binary_function, arg1, _1)(arg2));
	EXPECT_EQ(ternary(arg1, arg2, arg3), bind(ternary_function, arg1, _1, _2)(arg2, arg3));
	EXPECT_EQ(quaternary(arg1, arg2, arg3, arg4), bind(quaternary_function, arg1, _1, _2, _3)(arg2, arg3, arg4));	
	EXPECT_EQ(quinary(arg1, arg2, arg3, arg4, arg5), bind(quinary_function, arg1, _1, _2, _3, _4)(arg2, arg3, arg4, arg5));
}


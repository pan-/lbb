#include <gtest/gtest.h>

#include <iostream>
using namespace std;

#include <lbb/functional.h>

using lbb::function;

#define DEBUG() do { /* cout << __PRETTY_FUNCTION__ << endl; */ } while(0)


void foo() { DEBUG(); }
float bar(int) { DEBUG(); return 0.0;}
char baz(const char* s, int) { DEBUG(); return s[0]; }

struct Foo {
	void foo_method() { DEBUG(); }
};

struct Bar {
	float bar_method(int) { DEBUG(); return 0.0;}
};

struct Baz {
	char baz_method(const char* s, int) { DEBUG(); return s[0]; }
};

typedef void test_type();


typedef void (Foo::*test_method)();


struct Test {
	Test(void(*)()) { DEBUG(); }
	template<typename aClass>
	Test(void(aClass::*)()) { DEBUG(); }
};


struct Base {
	virtual ~Base() { }
	virtual void Do() { DEBUG(); }
	int foo;
};

struct Left : public virtual Base {
	virtual ~Left() { }
};

struct Right : public virtual Base {
	virtual ~Right() { }
};

struct Final : public Left, public Right {
	virtual ~Final() { }
};

struct PointerToMemberTest {
	int function1() { DEBUG();  return 0; }
	int function2(char) { DEBUG(); return 0; }
	int function3(char, float) { DEBUG(); return 0; }
	int function4(char, float, char*) { DEBUG(); return 0; }
	int function5(char, float, char*, void*) { DEBUG(); return 0; }
};

typedef PointerToMemberTest* PtrTest;


int function0() { DEBUG(); return 0; }
int function1(PtrTest) { DEBUG();  return 0; }
int function2(PtrTest, char) { DEBUG(); return 0; }
int function3(PtrTest, char, float) { DEBUG(); return 0; }
int function4(PtrTest, char, float, char*) { DEBUG(); return 0; }
int function5(PtrTest, char, float, char*, void*) { DEBUG(); return 0; }


typedef int function0_signature();
typedef int function1_signature(PtrTest);
typedef int function2_signature(PtrTest, char);
typedef int function3_signature(PtrTest, char, float);
typedef int function4_signature(PtrTest, char, float, char*);
typedef int function5_signature(PtrTest, char, float, char*, void*);


int test_function0_call(function<function0_signature> func) {
	return func();
}

int test_function1_call(function<function1_signature> func) {
	PointerToMemberTest test;
	return func(&test);
}

int test_function2_call(function<function2_signature>& func) {
	PointerToMemberTest test;
	return func(&test,0);
}

int test_function3_call(function<function3_signature>& func) {
	PointerToMemberTest test;
	return func(&test, 0, 0);
}

int test_function4_call(function<function4_signature>& func) {
	PointerToMemberTest test;
	return func(&test, 0, 0, 0);
}

int test_function5_call(function<function5_signature>& func) {
	PointerToMemberTest test;
	return func(&test, 0, 0, 0, 0);
}



struct TestFunctionObject {
	int operator()() { DEBUG(); return 0; }
	int operator()(PtrTest) { DEBUG();  return 0; }
	int operator()(PtrTest, char) { DEBUG(); return 0; }
	int operator()(PtrTest, char, float) { DEBUG(); return 0; }
	int operator()(PtrTest, char, float, char*) { DEBUG(); return 0; }
	int operator()(PtrTest, char, float, char*, void*) { DEBUG(); return 0; }
};




TEST(function, instantiation_should_succeed) {

	//Test of function pointer instantiation !!
	function<function0_signature> function0_test = &function0;
	function<function1_signature> function1_test = &function1;
	function<function2_signature> function2_test = &function2;
	function<function3_signature> function3_test = &function3;
	function<function4_signature> function4_test = &function4;
	function<function5_signature> function5_test = &function5;


	//Call test ...
	test_function0_call(function0_test);
	test_function1_call(function1_test);
	test_function2_call(function2_test);
	test_function3_call(function3_test);
	test_function4_call(function4_test);
	test_function5_call(function5_test);


	//pointer to member ....
	function<function1_signature> ptrToMember_test1 = &PointerToMemberTest::function1;
	function<function2_signature> ptrToMember_test2 = &PointerToMemberTest::function2;
	function<function3_signature> ptrToMember_test3 = &PointerToMemberTest::function3;
	function<function4_signature> ptrToMember_test4 = &PointerToMemberTest::function4;
	function<function5_signature> ptrToMember_test5 = &PointerToMemberTest::function5;


	test_function1_call(ptrToMember_test1);
	test_function2_call(ptrToMember_test2);
	test_function3_call(ptrToMember_test3);
	test_function4_call(ptrToMember_test4);
	test_function5_call(ptrToMember_test5);


	TestFunctionObject functor;

	//function object ....
	//Test of function pointer instantiation !!
	function<function0_signature> functionobject0_test = functor;
	function<function1_signature> functionobject1_test = functor;
	function<function2_signature> functionobject2_test = functor;
	function<function3_signature> functionobject3_test = functor;
	function<function4_signature> functionobject4_test = functor;
	function<function5_signature> functionobject5_test = functor;

	//Call test ...
	test_function0_call(functionobject0_test);
	test_function1_call(functionobject1_test);
	test_function2_call(functionobject2_test);
	test_function3_call(functionobject3_test);
	test_function4_call(functionobject4_test);
	test_function5_call(functionobject5_test);
}




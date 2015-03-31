#include <gtest/gtest.h>
#include <lbb/smartptr.h>

using lbb::shared_ptr;
//using lbb::thread;

namespace { 

struct test_struct { 
	test_struct() { }
	virtual ~test_struct() { }
};

struct test_struct_derived : test_struct { };

}


TEST(shared_ptr, constructor_instantiation) { 
	shared_ptr<test_struct> under_test(new test_struct());
}

TEST(shared_ptr, copy_constructor_instantiation) { 
	shared_ptr<test_struct> under_test = new test_struct();
}

TEST(shared_ptr, copy_constructor_from_derived_instantiation) { 
	shared_ptr<test_struct_derived> derived(new test_struct_derived());
	shared_ptr<test_struct> under_test = derived;
}

TEST(shared_ptr, assignement_from_ptr_instantiation) { 
	shared_ptr<test_struct> under_test = new test_struct();
	under_test = new test_struct();
}

TEST(shared_ptr, assignement_from_shared_ptr_instantiation) { 
	shared_ptr<test_struct> under_test = new test_struct();
	shared_ptr<test_struct> other = new test_struct();
	under_test = other;
}

TEST(shared_ptr, assignement_from_derived_instantiation) { 
	shared_ptr<test_struct> under_test = new test_struct();	
	shared_ptr<test_struct_derived> derived(new test_struct_derived());
	under_test = derived;
}

TEST(shared_ptr, swap_instantiation) { 
	shared_ptr<test_struct> under_test = new test_struct();
	shared_ptr<test_struct> other = new test_struct();
	under_test.swap(other);
}

TEST(shared_ptr, deference_operator_instantiation) { 
	shared_ptr<test_struct> under_test = new test_struct();
	*under_test;
}

TEST(shared_ptr, get_instantiation) { 
	shared_ptr<test_struct> under_test = new test_struct();
	under_test.get();
}

TEST(shared_ptr, equality_comparison_instantiation) { 
	shared_ptr<test_struct> under_test = new test_struct();
	shared_ptr<test_struct> other = new test_struct();
	(under_test == other);
}

TEST(shared_ptr, inequality_comparison_instantiation) { 
	shared_ptr<test_struct> under_test = new test_struct();
	shared_ptr<test_struct> other = new test_struct();
	(under_test != other);
}

TEST(shared_ptr, bool_conversion) { 
	shared_ptr<test_struct> under_test = new test_struct();
	if(under_test) { }
}



TEST(shared_ptr, make_shared) { 
	shared_ptr<int> foo = lbb::make_shared<int>(42);

}

class Foo {

public:
	Foo(double d) :_d(d){
	}

	~Foo(){
		_d = _d *3;

		int i = -_d;
		_d = i +6;

		set(_d * 5);
	}

	void set(double d) {
		_d = d;
	}

	void print() {
		std::cout << "_d = '" << _d << "'." << std::endl;
	}


private:
	double _d;
};

void useShared(shared_ptr<Foo> foo) {
	foo->set(50.);
	foo->print();
}

shared_ptr<Foo> makeShared() {

	return lbb::make_shared<Foo>(42);

}

#if 0
TEST(shared_ptr, keep_alive_heap) { 

	thread  worker(useShared, makeShared());
	worker.detach();

}

#endif

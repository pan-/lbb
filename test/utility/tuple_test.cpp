#include <iostream>

#include <gtest/gtest.h>

#include <lbb/meta.h>
#include <lbb/utility.h>


using namespace lbb;

struct empty { };

struct not_empty { 
	char a;
};



/*
 * DEFAULT CONSTRUCTION
 */
TEST(tuple, empty_tuple_should_be_allowed) { 
	tuple<> empty;
}


TEST(tuple, tuple_with_one_element_should_be_default_constructible) { 
	tuple<int> under_test;

	EXPECT_EQ(0, get<0>(under_test));
}


TEST(tuple, tuple_with_two_element_should_be_default_constructible) { 
	tuple<int, int> under_test;

	EXPECT_EQ(0, get<0>(under_test));
	EXPECT_EQ(0, get<1>(under_test));	
}


TEST(tuple, tuple_with_three_element_should_be_default_constructible) { 
	tuple<int, int, int> under_test;

	EXPECT_EQ(0, get<0>(under_test));
	EXPECT_EQ(0, get<1>(under_test));	
	EXPECT_EQ(0, get<2>(under_test));		
}


TEST(tuple, tuple_with_four_element_should_be_default_constructible) { 
	tuple<int, int, int, int> under_test;

	EXPECT_EQ(0, get<0>(under_test));
	EXPECT_EQ(0, get<1>(under_test));
	EXPECT_EQ(0, get<2>(under_test));
	EXPECT_EQ(0, get<3>(under_test));		
}


TEST(tuple, tuple_with_five_element_should_be_default_constructible) { 
	tuple<int, int, int, int, int> under_test;

	EXPECT_EQ(0, get<0>(under_test));
	EXPECT_EQ(0, get<1>(under_test));
	EXPECT_EQ(0, get<2>(under_test));
	EXPECT_EQ(0, get<3>(under_test));		
	EXPECT_EQ(0, get<4>(under_test));		
}



/*
 * CONSTRUCTION WITH VALUE
 */
TEST(tuple, tuple_with_one_element_should_be_constructible_with_value) { 
	tuple<int> under_test(0);

	EXPECT_EQ(0, get<0>(under_test));
}


TEST(tuple, tuple_with_two_element_should_be_constructible_with_value) { 
	tuple<int, int> under_test(0, 1);

	EXPECT_EQ(0, get<0>(under_test));
	EXPECT_EQ(1, get<1>(under_test));	
}


TEST(tuple, tuple_with_three_element_should_be_constructible_with_value) { 
	tuple<int, int, int> under_test(0, 1, 2);

	EXPECT_EQ(0, get<0>(under_test));
	EXPECT_EQ(1, get<1>(under_test));	
	EXPECT_EQ(2, get<2>(under_test));		
}


TEST(tuple, tuple_with_four_element_should_be_constructible_with_value) { 
	tuple<int, int, int, int> under_test(0, 1, 2, 3);

	EXPECT_EQ(0, get<0>(under_test));
	EXPECT_EQ(1, get<1>(under_test));
	EXPECT_EQ(2, get<2>(under_test));
	EXPECT_EQ(3, get<3>(under_test));		
}


TEST(tuple, tuple_with_five_element_should_be_constructible_with_value) { 
	tuple<int, int, int, int, int> under_test(0, 1, 2, 3, 4);

	EXPECT_EQ(0, get<0>(under_test));
	EXPECT_EQ(1, get<1>(under_test));
	EXPECT_EQ(2, get<2>(under_test));
	EXPECT_EQ(3, get<3>(under_test));		
	EXPECT_EQ(4, get<4>(under_test));		
}


/*
 * COPY CONSTRUCTION
 */
TEST(tuple, tuple_with_one_element_should_be_copy_constructible) { 
	tuple<int> other(0);
	tuple<int> under_test = other;

	EXPECT_TRUE(get<0>(other) == get<0>(under_test));
	EXPECT_FALSE((&get<0>(other)) == (&get<0>(under_test)));	
}



TEST(tuple, tuple_with_two_element_should_be_copy_constructible) { 
	tuple<int, int> other(0, 1);
	tuple<int, int> under_test = other;

	EXPECT_TRUE(get<0>(other) == get<0>(under_test));
	EXPECT_FALSE((&get<0>(other)) == (&get<0>(under_test)));	

	EXPECT_TRUE(get<1>(other) == get<1>(under_test));
	EXPECT_FALSE((&get<1>(other)) == (&get<1>(under_test)));		
}


TEST(tuple, tuple_with_three_element_should_be_copy_constructible) { 
	tuple<int, int, int> other(0, 1, 2);
	tuple<int, int, int> under_test = other;

	EXPECT_TRUE(get<0>(other) == get<0>(under_test));
	EXPECT_FALSE((&get<0>(other)) == (&get<0>(under_test)));	

	EXPECT_TRUE(get<1>(other) == get<1>(under_test));
	EXPECT_FALSE((&get<1>(other)) == (&get<1>(under_test)));		

	EXPECT_TRUE(get<2>(other) == get<2>(under_test));
	EXPECT_FALSE((&get<2>(other)) == (&get<2>(under_test)));		
}

TEST(tuple, tuple_with_four_element_should_be_copy_constructible) { 
	tuple<int, int, int, int> other(0, 1, 2, 3);
	tuple<int, int, int, int> under_test = other;

	EXPECT_TRUE(get<0>(other) == get<0>(under_test));
	EXPECT_FALSE((&get<0>(other)) == (&get<0>(under_test)));	

	EXPECT_TRUE(get<1>(other) == get<1>(under_test));
	EXPECT_FALSE((&get<1>(other)) == (&get<1>(under_test)));		

	EXPECT_TRUE(get<2>(other) == get<2>(under_test));
	EXPECT_FALSE((&get<2>(other)) == (&get<2>(under_test)));

	EXPECT_TRUE(get<3>(other) == get<3>(under_test));
	EXPECT_FALSE((&get<3>(other)) == (&get<3>(under_test)));		
}


TEST(tuple, tuple_with_five_element_should_be_copy_constructible) { 
	tuple<int, int, int, int, int> other(0, 1, 2, 3, 4);
	tuple<int, int, int, int, int> under_test = other;

	EXPECT_TRUE(get<0>(other) == get<0>(under_test));
	EXPECT_FALSE((&get<0>(other)) == (&get<0>(under_test)));	

	EXPECT_TRUE(get<1>(other) == get<1>(under_test));
	EXPECT_FALSE((&get<1>(other)) == (&get<1>(under_test)));		

	EXPECT_TRUE(get<2>(other) == get<2>(under_test));
	EXPECT_FALSE((&get<2>(other)) == (&get<2>(under_test)));

	EXPECT_TRUE(get<3>(other) == get<3>(under_test));
	EXPECT_FALSE((&get<3>(other)) == (&get<3>(under_test)));		

	EXPECT_TRUE(get<4>(other) == get<4>(under_test));
	EXPECT_FALSE((&get<4>(other)) == (&get<4>(under_test)));		
}



/*
 * MAKE_TUPLE
 */
TEST(tuple, make_tuple_should_work_with_one_element) { 
	tuple<int> under_test(make_tuple(0));

	EXPECT_EQ(0, get<0>(under_test));
}


TEST(tuple, make_tuple_should_work_with_two_element) { 
	tuple<int, int> under_test(make_tuple(0, 1));

	EXPECT_EQ(0, get<0>(under_test));
	EXPECT_EQ(1, get<1>(under_test));	
}


TEST(tuple, make_tuple_should_work_with_three_element) { 
	tuple<int, int, int> under_test(make_tuple(0, 1, 2));

	EXPECT_EQ(0, get<0>(under_test));
	EXPECT_EQ(1, get<1>(under_test));	
	EXPECT_EQ(2, get<2>(under_test));		
}


TEST(tuple, make_tuple_should_work_with_four_element) { 
	tuple<int, int, int, int> under_test(make_tuple(0, 1, 2, 3));

	EXPECT_EQ(0, get<0>(under_test));
	EXPECT_EQ(1, get<1>(under_test));
	EXPECT_EQ(2, get<2>(under_test));
	EXPECT_EQ(3, get<3>(under_test));		
}


TEST(tuple, make_tuple_should_work_with_five_element) { 
	tuple<int, int, int, int, int> under_test(make_tuple(0, 1, 2, 3, 4));

	EXPECT_EQ(0, get<0>(under_test));
	EXPECT_EQ(1, get<1>(under_test));
	EXPECT_EQ(2, get<2>(under_test));
	EXPECT_EQ(3, get<3>(under_test));		
	EXPECT_EQ(4, get<4>(under_test));		
}


/*
 * TIE TEST
 */
/*
 * MAKE_TUPLE
 */
TEST(tuple, tie_tuple_should_work_with_one_element) { 
	int first = 0;
	tuple<int&> under_test(tie(first));

	EXPECT_EQ(&first, &get<0>(under_test));
}


TEST(tuple, tie_tuple_should_work_with_two_element) { 
	int first = 0;
	int second = 1;

	tuple<int&, int&> under_test(tie(first, second));

	EXPECT_EQ(&first, &get<0>(under_test));
	EXPECT_EQ(&second, &get<1>(under_test));	
}


TEST(tuple, tie_tuple_should_work_with_three_element) { 
	int first = 0;
	int second = 1;
	int third = 2;

	tuple<int&, int&, int&> under_test(tie(first, second, third));

	EXPECT_EQ(&first, &get<0>(under_test));
	EXPECT_EQ(&second, &get<1>(under_test));	
	EXPECT_EQ(&third, &get<2>(under_test));		
}


TEST(tuple, tie_tuple_should_work_with_four_element) { 
	int first = 0;
	int second = 1;
	int third = 2;
	int fourth = 3;

	tuple<int&, int&, int&, int&> under_test(tie(first, second, third, fourth));

	EXPECT_EQ(&first, &get<0>(under_test));
	EXPECT_EQ(&second, &get<1>(under_test));	
	EXPECT_EQ(&third, &get<2>(under_test));		
	EXPECT_EQ(&fourth, &get<3>(under_test));		
}


TEST(tuple, tie_tuple_should_work_with_five_element) { 
	int first = 0;
	int second = 1;
	int third = 2;
	int fourth = 3;
	int fifth = 4;	

	tuple<int&, int&, int&, int&, int&> under_test(tie(first, second, third, fourth, fifth));

	EXPECT_EQ(&first, &get<0>(under_test));
	EXPECT_EQ(&second, &get<1>(under_test));	
	EXPECT_EQ(&third, &get<2>(under_test));		
	EXPECT_EQ(&fourth, &get<3>(under_test));		
	EXPECT_EQ(&fifth, &get<4>(under_test));			
} 



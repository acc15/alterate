#include <gtest/gtest.h>

#include <alterate/iterator.hpp>


TEST(iterator_test, scalar_iterator_can_move_forward_and_backward) {
    alterate::scalar_iterator<int> iter(15);
    ASSERT_EQ(15, *iter);
	iter++;
	ASSERT_EQ(15, *iter);
	iter--;
	ASSERT_EQ(15, *iter);
}

TEST(iterator_test, scalar_iterator_assignment) {
	alterate::scalar_iterator<int> iter(15);

	*iter = 178;

	ASSERT_EQ(*iter, 178);
	iter += 50;
	ASSERT_EQ(*iter, 178);
	iter -= 25;
	ASSERT_EQ(*iter, 178);
}

TEST(iterator_test, scalar_iterator_equality) {

	alterate::scalar_iterator<int> iter1(15);
	alterate::scalar_iterator<int> iter2(16);
	alterate::scalar_iterator<int> iter3(15);
	alterate::scalar_iterator<int> iter4(15, 5);

	ASSERT_EQ(iter1, iter3);
	ASSERT_NE(iter1, iter2);

	++iter1;
	ASSERT_NE(iter1, iter3);

	++iter3;
	ASSERT_EQ(iter1, iter3);

	--iter3;
	--iter1;
	ASSERT_EQ(iter1, iter3);

	ASSERT_NE(iter1, iter4);
	iter1 += 5;
	ASSERT_EQ(iter1, iter4);

}

TEST(iterator_test, array_iterator_factory_test) {

	typedef alterate::array_iterator_factory< int[10] > factory_type;
	typedef typename factory_type::const_iterator const_iterator;

	int test_array[10] = {1,2,3,4,5,6,7,8,9,10};

	const_iterator begin = factory_type::begin(test_array);
	const_iterator end = factory_type::end(test_array, 0);

	int dist = std::distance(begin, end);
	ASSERT_EQ(10, dist);
	ASSERT_EQ(1, *begin);

	++begin;
	ASSERT_EQ(2, *begin);

	begin += 8;
	ASSERT_EQ(10, *begin);

	++begin;
	ASSERT_EQ(begin, end);

}

TEST(iterator_test, pointer_iterator_factory_test) {

	typedef alterate::pointer_iterator_factory< int* > factory_type;
	typedef typename factory_type::const_iterator const_iterator;

	int test_array[10] = {1,2,3,4,5,6,7,8,9,10};

	const_iterator begin = factory_type::begin(test_array);
	const_iterator end1 = factory_type::end(test_array, 0);
	const_iterator end2 = factory_type::end(test_array, 5);

	ASSERT_EQ(begin,end1);
	ASSERT_NE(begin,end2);


	std::vector<int> expected = {1,2,3,4,5,6,7,8,9,10};
	std::vector<int> actual;

	ASSERT_EQ(1, *begin);
	ASSERT_EQ(6, *end2);

	ASSERT_EQ(5, std::distance(begin, end2));

}


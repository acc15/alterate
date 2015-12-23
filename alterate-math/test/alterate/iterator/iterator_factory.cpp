#include <gtest/gtest.h>

#include <alterate/iterator/iterator_factory.hpp>

using namespace alterate::iterator;

TEST(iterator_test, array_iterator_factory_test) {

    typedef array_iterator_factory< int[10] > factory_type;
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

    typedef pointer_iterator_factory< int* > factory_type;
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


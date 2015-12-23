#include <gtest/gtest.h>

#include <alterate/iterator/scalar_iterator.hpp>

using namespace alterate::iterator;

TEST(scalar_iterator, can_move_forward_and_backward) {
    scalar_iterator<int> iter(15);
    ASSERT_EQ(15, *iter);
    iter++;
    ASSERT_EQ(15, *iter);
    iter--;
    ASSERT_EQ(15, *iter);
}

TEST(scalar_iterator, assignment) {
    scalar_iterator<int> iter(15);

    *iter = 178;

    ASSERT_EQ(*iter, 178);
    iter += 50;
    ASSERT_EQ(*iter, 178);
    iter -= 25;
    ASSERT_EQ(*iter, 178);
}

TEST(scalar_iterator, equality) {

    scalar_iterator<int> iter1(15);
    scalar_iterator<int> iter2(16);
    scalar_iterator<int> iter3(15);
    scalar_iterator<int> iter4(15, 5);
    
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

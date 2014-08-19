#include "pch.h"

#include <alterate/iterable/scalar.h>

namespace {

    using alterate::iterable::scalar_iterator;

    TEST(scalar_iterator_test, is_default_constructible) {
        scalar_iterator<int> default_constructible;
    }

    TEST(scalar_iterator_test, is_copy_constructible) {
        scalar_iterator<int> copy_sample(150, 5);
        scalar_iterator<int> copy_constructible(copy_sample);
    }

    TEST(scalar_iterator_test, is_copy_assignable) {
        scalar_iterator<int> copy_sample(150, 5);
        scalar_iterator<int> copy_assignable = copy_sample;
    }

    TEST(scalar_iterator_test, is_equivalance_comparable) {
        scalar_iterator<int> copy_sample(150, 5);
        scalar_iterator<int> copy_assignable = copy_sample;
        ASSERT_TRUE(copy_sample == copy_assignable);
        ASSERT_FALSE(copy_sample != copy_assignable);

        scalar_iterator<int> diff_sample(10, 5);
        ASSERT_FALSE(copy_sample == diff_sample);
        ASSERT_TRUE(copy_sample != diff_sample);
        ASSERT_FALSE(copy_assignable == diff_sample);
        ASSERT_TRUE(copy_assignable != diff_sample);
    }

    TEST(scalar_iterator_test, can_be_dereferenced) {
        scalar_iterator<int> iter(150, 5);
        ASSERT_EQ(*iter, 150);

        struct test_struct {
            int x = 50;
        };

        scalar_iterator<test_struct> iter2(test_struct(), 5);
        ASSERT_EQ( iter2->x, 50);
    }

    TEST(scalar_iterator_test, can_be_incremented) {
        scalar_iterator<int> iter1(150, 5);
        scalar_iterator<int> iter2(150, 5);
        
        ++iter1;
        iter2++;
        
        ASSERT_EQ(iter1, iter2);
    }

    TEST(scalar_iterator_test, can_be_decremented) {
        scalar_iterator<int> iter1(150, 5);
        scalar_iterator<int> iter2(150, 5);

        --iter1;
        iter2--;

        ASSERT_EQ(iter1, iter2);
    }

    TEST(scalar_iterator_test, supports_add) {
        const scalar_iterator<int> iter_original(150, 5);
        scalar_iterator<int> iter(iter_original);
        scalar_iterator<int> iter_actual = iter + 5;
        scalar_iterator<int> iter_expected(150, 10);
        ASSERT_EQ(iter_expected, iter_actual);
        ASSERT_EQ(iter_original, iter);
    }

    TEST(scalar_iterator_test, supports_sub) {
        const scalar_iterator<int> iter_original(150, 5);
        scalar_iterator<int> iter(iter_original);
        scalar_iterator<int> iter_actual = iter - 3;
        scalar_iterator<int> iter_expected(150, 2);
        ASSERT_EQ(iter_expected, iter_actual);
        ASSERT_EQ(iter_original, iter);
    }

    TEST(scalar_iterator_test, supports_sub_from_another) {
        scalar_iterator<int> iter1(150, 10);
        scalar_iterator<int> iter2(150, 4);
        ASSERT_EQ(iter1 - iter2, 6);
        ASSERT_EQ(iter2 - iter1, -6);
    }

    TEST(scalar_iterator_test, supports_assignment_add) {
        scalar_iterator<int> iter(150, 4);
        iter += 6;

        scalar_iterator<int> iter_expected(150, 10);
        ASSERT_EQ(iter_expected, iter);
    }

    TEST(scalar_iterator_test, supports_assignment_sub) {
        scalar_iterator<int> iter(150, 4);
        iter -= 2;

        scalar_iterator<int> iter_expected(150, 2);
        ASSERT_EQ(iter_expected, iter);
    }

    TEST(scalar_iterator_test, supports_assignment_sub_another) {
        scalar_iterator<int> iter1(150, 7);
        scalar_iterator<int> iter2(150, 4);
        iter1 -= iter2;

        scalar_iterator<int> iter_expected(150, 3);
        ASSERT_EQ(iter_expected, iter1);
    }

    TEST(scalar_iterator_test, can_be_compared_by_relational_operators) {
        scalar_iterator<int> iter1(150, 7);
        scalar_iterator<int> iter2(150, 4);
        ASSERT_TRUE(iter1 > iter2);
        ASSERT_FALSE(iter1 < iter2);
        ASSERT_TRUE(iter2 < iter1);
        ASSERT_FALSE(iter2 > iter1);

        scalar_iterator<int> iter3(150, 4);
        ASSERT_TRUE(iter2 >= iter3);
        ASSERT_FALSE(iter3 >= iter1);

        ASSERT_TRUE(iter3 <= iter2);
        ASSERT_FALSE(iter1 <= iter2);

    }
    
    TEST(scalar_iterator_test, supports_offset_dereference_operator) {
        scalar_iterator<int> iter1(150, 7);
        ASSERT_EQ(iter[5], 150);
        ASSERT_EQ(iter[2], 150);
    }
}

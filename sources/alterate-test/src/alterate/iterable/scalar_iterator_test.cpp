#include "pch.h"

#include <alterate/iterable/scalar.h>

namespace {

    using alterate::iterable::scalar_iterator;

    TEST(scalar_iterator_test, is_default_constructible) {
        scalar_iterator<int> default_constructible;
    }

    TEST(scalar_iterator_test, is_copy_constructible) {
        int iterator_value = 150;
        scalar_iterator<int> copy_sample(iterator_value, 5);
        scalar_iterator<int> copy_constructible(copy_sample);
    }

    TEST(scalar_iterator_test, is_copy_assignable) {
        int iterator_value = 150;
        scalar_iterator<int> copy_sample(iterator_value, 5);
        scalar_iterator<int> copy_assignable = copy_sample;
    }

    TEST(scalar_iterator_test, is_equivalance_comparable) {
        int iterator_value = 150;
        scalar_iterator<int> copy_sample(iterator_value, 5);
        scalar_iterator<int> copy_assignable = copy_sample;
        ASSERT_TRUE(copy_sample == copy_assignable);
        ASSERT_FALSE(copy_sample != copy_assignable);

        int iterator_value2 = 10;
        scalar_iterator<int> diff_sample(iterator_value2, 5);
        ASSERT_FALSE(copy_sample == diff_sample);
        ASSERT_TRUE(copy_sample != diff_sample);
        ASSERT_FALSE(copy_assignable == diff_sample);
        ASSERT_TRUE(copy_assignable != diff_sample);
    }

    TEST(scalar_iterator_test, can_be_dereferenced) {
        int iterator_value = 150;
        scalar_iterator<int> iter(iterator_value, 5);
        ASSERT_EQ(*iter, iterator_value);

        struct test_struct {
            int x = 50;
        };

        test_struct tmp;

        scalar_iterator<test_struct> iter2(tmp, 5);
        ASSERT_EQ( 50, iter2->x );
    }

    TEST(scalar_iterator_test, can_be_incremented) {
        int iterator_value = 150;
        scalar_iterator<int> iter1(iterator_value, 5);
        scalar_iterator<int> iter2(iterator_value, 5);
        
        ++iter1;
        iter2++;
        
        ASSERT_EQ(iter1, iter2);
    }

    TEST(scalar_iterator_test, can_be_decremented) {
        int iterator_value = 150;
        scalar_iterator<int> iter1(iterator_value, 5);
        scalar_iterator<int> iter2(iterator_value, 5);

        --iter1;
        iter2--;

        ASSERT_EQ(iter1, iter2);
    }

    TEST(scalar_iterator_test, supports_add) {
        int iterator_value = 150;
        const scalar_iterator<int> iter_original(iterator_value, 5);
        scalar_iterator<int> iter(iter_original);
        scalar_iterator<int> iter_actual = iter + 5;
        scalar_iterator<int> iter_expected(iterator_value, 10);
        ASSERT_EQ(iter_expected, iter_actual);
        ASSERT_EQ(iter_original, iter);
    }

    TEST(scalar_iterator_test, supports_sub) {
        int iterator_value = 150;
        const scalar_iterator<int> iter_original(iterator_value, 5);
        scalar_iterator<int> iter(iter_original);
        scalar_iterator<int> iter_actual = iter - 3;
        scalar_iterator<int> iter_expected(iterator_value, 2);
        ASSERT_EQ(iter_expected, iter_actual);
        ASSERT_EQ(iter_original, iter);
    }

    TEST(scalar_iterator_test, supports_sub_from_another) {
        int iterator_value = 150;
        scalar_iterator<int> iter1(iterator_value, 10);
        scalar_iterator<int> iter2(iterator_value, 4);
        ASSERT_EQ(6, iter1 - iter2);
        ASSERT_EQ(-6, iter2 - iter1);
    }

    TEST(scalar_iterator_test, supports_assignment_add) {
        int iterator_value = 150;
        scalar_iterator<int> iter(iterator_value, 4);
        iter += 6;

        scalar_iterator<int> iter_expected(iterator_value, 10);
        ASSERT_EQ(iter_expected, iter);
    }

    TEST(scalar_iterator_test, supports_assignment_sub) {
        int iterator_value = 150;
        scalar_iterator<int> iter(iterator_value, 4);
        iter -= 2;

        scalar_iterator<int> iter_expected(iterator_value, 2);
        ASSERT_EQ(iter_expected, iter);
    }

    TEST(scalar_iterator_test, supports_assignment_sub_another) {
        int iterator_value = 150;
        scalar_iterator<int> iter1(iterator_value, 7);
        scalar_iterator<int> iter2(iterator_value, 4);
        iter1 -= iter2;

        scalar_iterator<int> iter_expected(iterator_value, 3);
        ASSERT_EQ(iter_expected, iter1);
    }

    TEST(scalar_iterator_test, can_be_compared_by_relational_operators) {
        int iterator_value = 150;
        scalar_iterator<int> iter1(iterator_value, 7);
        scalar_iterator<int> iter2(iterator_value, 4);
        ASSERT_TRUE(iter1 > iter2);
        ASSERT_FALSE(iter1 < iter2);
        ASSERT_TRUE(iter2 < iter1);
        ASSERT_FALSE(iter2 > iter1);

        scalar_iterator<int> iter3(iterator_value, 4);
        ASSERT_TRUE(iter2 >= iter3);
        ASSERT_FALSE(iter3 >= iter1);

        ASSERT_TRUE(iter3 <= iter2);
        ASSERT_FALSE(iter1 <= iter2);

    }
    
    TEST(scalar_iterator_test, supports_offset_dereference_operator) {
        int iterator_value = 150;
        scalar_iterator<int> iter(iterator_value, 7);
        ASSERT_EQ(150, iter[5]);
        ASSERT_EQ(150, iter[-2]);
    }
}

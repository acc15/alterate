#include "pch.h"

#include <alterate/iterable/scalar_iterator.h>

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

}

#pragma once

#include <gtest/gtest.h>  // C++ Google Test Framework
#include <alterate/types.h>

template <typename Iterator, typename Type>
void assert_equals(Iterator begin, Iterator end, std::initializer_list<Type> const& expected) {
    typedef std::initializer_list<Type>::const_iterator list_iter;
    list_iter e_begin = expected.begin(), e_end = expected.end();

    alterate::uint_t i = 0;
    for (; e_begin != e_end; e_begin++, begin++, i++) {
        ASSERT_NE(begin, end) << "Actual collection is too short";
        ASSERT_EQ(*e_begin, *begin) << "Elements at " << i << " position isn't equal. Expected: " << (*e_begin) << "; but was: " << (*begin);
    }
    ASSERT_EQ(begin, end) << "Actual collection is too long";
}

template <typename Collection, typename Type>
void assert_container(Collection const& values, std::initializer_list<Type> const& expected) {
    assert_equals(values.begin(), values.end(), expected);
}

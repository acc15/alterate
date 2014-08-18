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
void assert_equals_il(Collection const& values, std::initializer_list<Type> const& expected) {
    assert_equals(expected.begin(), expected.end(), values.cbegin(), values.cend());
}


template <typename ExpectedIterator, typename ActualIterator>
void assert_equals(ExpectedIterator const& e_begin, ExpectedIterator const& e_end, ActualIterator const& a_begin, ActualIterator const& a_end) {
    ExpectedIterator e_iter = e_begin;
    ActualIterator a_iter = a_begin;
    alterate::uint_t i = 0;
    for (; e_iter != e_end; e_iter++, a_iter++, i++) {
        ASSERT_NE(a_iter, a_end) << "Actual collection is too short";
        ASSERT_EQ(*e_iter, *a_iter) << "Elements at " << i << " position isn't equal. Expected: " << (*e_iter) << "; but was: " << (*a_iter);
    }
    ASSERT_EQ(a_iter, a_end) << "Actual collection is too long";
}

template <typename ExpectedIterable, typename ActualIterable>
void assert_equals(ExpectedIterable const& e_iterable, ActualIterable const& a_iterable) {
    assert_equals(e_iterable.cbegin(), e_iterable.cend(), a_iterable.cbegin(), a_iterable.cend());
}
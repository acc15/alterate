#pragma once

#include <gtest/gtest.h>  // C++ Google Test Framework
#include <alterate/types.h>

template <typename ExpectedIterator, typename ActualIterator>
void assert_equals(ExpectedIterator const&  e_begin, ExpectedIterator const&    e_end, 
                   ActualIterator const&    a_begin, ActualIterator const&      a_end) {
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
    assert_equals(e_iterable.begin(), e_iterable.end(), a_iterable.begin(), a_iterable.end());
}

template <typename ExpectedValue, typename ActualIterable>
void assert_equals(std::initializer_list<ExpectedValue> const& e_iterable, ActualIterable const& a_iterable) {
    assert_equals(e_iterable.begin(), e_iterable.end(), a_iterable.begin(), a_iterable.end());
}
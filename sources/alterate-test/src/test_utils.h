#pragma once

#include <gtest/gtest.h>  // C++ Google Test Framework
#include <alterate/types.h>

template <typename ExpectedValue, typename ActualValue>
void assert_element_equals(ExpectedValue const& e_value, ActualValue const& a_value, alterate::uint_t index) {
    ASSERT_EQ(e_value, a_value) << "Elements at " << index << 
        " position isn't equal. Expected: " << e_value << "; but was: " << a_value;
}

template <typename ExpectedIterator, typename ActualIterator>
void assert_equals(ExpectedIterator const&  e_begin, ExpectedIterator const&    e_end, 
                   ActualIterator const&    a_begin, ActualIterator const&      a_end) {
    ExpectedIterator e_iter = e_begin;
    ActualIterator a_iter = a_begin;
    alterate::uint_t i = 0;
    for (; e_iter != e_end; e_iter++, a_iter++, i++) {
        ASSERT_NE(a_iter, a_end) << "Actual collection is too short";
        assert_element_equals(*e_iter, *a_iter, i);
    }
    ASSERT_EQ(a_iter, a_end) << "Actual collection is too long";
}

template <typename ExpectedContainer, typename ActualContainer>
void assert_equals(ExpectedContainer const& e_iterable, ActualContainer const& a_iterable) {
    assert_equals(e_iterable.begin(), e_iterable.end(), a_iterable.begin(), a_iterable.end());
}

template <typename ExpectedValue, typename ActualContainer>
void assert_equals_all(ExpectedValue const& e_value, ActualContainer const& a_iterable) {
    typedef typename ActualContainer::const_iterator const_iterator;
    alterate::uint_t i = 0;
    for (const_iterator iter = a_iterable.begin(); iter != a_iterable.end(); iter++, i++) {
        assert_element_equals(e_value, *iter, i);
    }
}

template <typename ExpectedValue, typename ActualContainer>
void assert_equals(std::initializer_list<ExpectedValue> const& e_iterable, ActualContainer const& a_iterable) {
    assert_equals(e_iterable.begin(), e_iterable.end(), a_iterable.begin(), a_iterable.end());
}

template <typename ExpectedContainer, typename ActualContainer>
void assert_range_equals(
    ExpectedContainer const& e_iterable, 
    ActualContainer const& a_iterable, 
    alterate::uint_t start = 0, 
    alterate::uint_t end = -1) {

    typedef typename ExpectedContainer::const_iterator expected_iterator;
    typedef typename ActualContainer::const_iterator actual_iterator;

    expected_iterator e_begin = e_iterable.begin(), e_end = e_iterable.end();
    actual_iterator a_begin = a_iterable.begin(), a_end = a_iterable.end();

    expected_iterator e_iter = e_begin;
    actual_iterator a_iter = a_begin;

    alterate::uint_t position = 0;
    for (; position < start && e_iter != e_end && a_iter != a_end; position++, e_iter++, a_iter++) {
    }
    
    for (; position < end && e_iter != e_end; position++, e_iter++, a_iter++) {
        ASSERT_NE(a_iter, a_end) << 
            "Actual iterable is too short. Expected size: " << end << "; But was: " << position;
        assert_element_equals(*e_iter, *a_iter, position);
    }

}
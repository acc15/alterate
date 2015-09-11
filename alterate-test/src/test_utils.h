#pragma once

#include <gtest/gtest.h>  // C++ Google Test Framework
#include <alterate/defs.h>

namespace alterate {
namespace test {

template <typename To>
struct static_cast_fn {
    template <typename From>
    To operator()(const From& from) const {
        return static_cast<To>(from);
    }
};

template <typename ExpectedValue, typename ActualValue>
void assert_is_equal_elements(const ExpectedValue& e_value, const ActualValue& a_value, size_t index) {
    ASSERT_EQ(e_value, a_value) << "Elements at " << index <<
        " position isn't equal. Expected: " << e_value << "; but was: " << a_value;
}

template <typename ExpectedIterator, typename ActualIterator>
void assert_has_equal_elements(
    const ExpectedIterator&  e_begin, const ExpectedIterator&    e_end,
    const ActualIterator&    a_begin, const ActualIterator&      a_end) {

    ExpectedIterator e_iter = e_begin;
    ActualIterator a_iter = a_begin;
    size_t i = 0;
    for (; e_iter != e_end; e_iter++, a_iter++, i++) {
        ASSERT_NE(a_iter, a_end) << "Actual collection is too short";
        assert_is_equal_elements(*e_iter, *a_iter, i);
    }
    ASSERT_EQ(a_iter, a_end) << "Actual collection is too long";

}

template <typename ExpectedContainer, typename ActualContainer>
void assert_has_equal_elements(const ExpectedContainer& e_iterable, const ActualContainer& a_iterable) {
    assert_has_equal_elements(e_iterable.begin(), e_iterable.end(), a_iterable.begin(), a_iterable.end());
}

template <typename ExpectedValue, typename ActualContainer>
void assert_all_elements_equal(const ExpectedValue& e_value, const ActualContainer& a_iterable) {
    typedef typename ActualContainer::const_iterator const_iterator;
    size_t i = 0;
    for (const_iterator iter = a_iterable.begin(); iter != a_iterable.end(); iter++, i++) {
        assert_is_equal_elements(e_value, *iter, i);
    }
}

template <typename ExpectedValue, typename ActualContainer>
void assert_has_equal_elements(const std::initializer_list<ExpectedValue>& e_iterable,
                               const ActualContainer& a_iterable) {
    assert_has_equal_elements(e_iterable.begin(), e_iterable.end(), a_iterable.begin(), a_iterable.end());
}

template <typename ExpectedContainer, typename ActualContainer>
void assert_has_equal_elements_between(
    const ExpectedContainer& e_iterable,
    const ActualContainer& a_iterable,
    size_t start = 0,
    size_t end = -1) {

    typedef typename ExpectedContainer::const_iterator expected_iterator;
    typedef typename ActualContainer::const_iterator actual_iterator;

    expected_iterator e_begin = e_iterable.begin(), e_end = e_iterable.end();
    actual_iterator a_begin = a_iterable.begin(), a_end = a_iterable.end();

    expected_iterator e_iter = e_begin;
    actual_iterator a_iter = a_begin;

    size_t position = 0;
    for (; position < start && e_iter != e_end && a_iter != a_end; position++, e_iter++, a_iter++) {
    }

    for (; position < end && e_iter != e_end && a_iter != a_end; position++, e_iter++, a_iter++) {
        assert_is_equal_elements(*e_iter, *a_iter, position);
    }

}


}
}

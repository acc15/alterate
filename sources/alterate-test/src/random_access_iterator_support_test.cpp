#include "pch.h"

#include <alterate/iterator/random_access_iterator_support.h>

#include "test_utils.h"

namespace {

    using namespace alterate::test;

    struct test_struct : ::alterate::iterator::random_access_iterator_support < test_struct, int > {
        int fieldA, fieldB, fieldC;

        test_struct(int a, int b, int c) : fieldA(a), fieldB(b), fieldC(c) {
        }

        size_type size() const {
            return 3;
        }

        int& operator[](const size_type& i) {
            return reinterpret_cast<int*>(this)[i];
        }

        const int& operator[](const size_type& i) const {
            return reinterpret_cast<const int*>(this)[i];
        }
    };

    TEST(random_access_iterator_support, const_iterator_test) {
        test_struct v(4, 5, 6);
        assert_has_equal_elements({ 4, 5, 6 }, v);
    }

    TEST(random_access_iterator_support, iterator_test) {
        test_struct v(1, 2, 3);

        // mutating values
        std::for_each(v.begin(), v.end(), [](int& x) { ++x; });
        assert_has_equal_elements({ 2, 3, 4 }, v);
    }

    TEST(random_access_iterator_support, const_reverse_iterator_test) {
        test_struct v(1, 2, 3);
        std::initializer_list<int> expected = { 3, 2, 1 };
        assert_has_equal_elements(expected.begin(), expected.end(), v.rbegin(), v.rend());
    }

    TEST(random_access_iterator_support, reverse_iterator_test) {
        test_struct v(1, 2, 3);

        int i = 0;
        std::for_each(v.rbegin(), v.rend(), [&i](int& x) { x += i; ++i; });

        assert_has_equal_elements({ 3, 3, 3 }, v);
    }

}
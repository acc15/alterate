#include "pch.h"

#include <list>

#include <boost/range.hpp>

#include <alterate/math/vector_support.h>
#include <alterate/math/vec.h>
#include "../../test_utils.h"


namespace {

    template <typename T>
    struct vector_support_test : public ::testing::Test {
        typedef T                           vector_type;
        typedef typename T::const_iterator  const_iterator;
        typedef typename T::value_type      value_type;
    };

    TYPED_TEST_CASE_P(vector_support_test);

    TYPED_TEST_P(vector_support_test, default_constructor_test) {
        vector_type vec;
        value_type default_value;
        assert_equals_all(default_value, vec);
    }

    TYPED_TEST_P(vector_support_test, scalar_constructor_test) {
        value_type scalar_value = static_cast<value_type>(58);
        vector_type vec = scalar_value;
        assert_equals_all(scalar_value, vec);
    }

    TYPED_TEST_P(vector_support_test, array_constructor_test) {
        value_type array_value[5] = {
            static_cast<value_type>(5),
            static_cast<value_type>(6),
            static_cast<value_type>(7),
            static_cast<value_type>(3),
            static_cast<value_type>(2),
        };

        vector_type vec = array_value;

        alterate::uint_t min_size = std::min<alterate::uint_t>(vec.size(), boost::size(array_value));
        assert_equals<const value_type*, const_iterator>(
            array_value, array_value + min_size, 
            vec.cbegin(), vec.cbegin() + min_size);
    }

    TYPED_TEST_P(vector_support_test, pointer_constructor_test) {
        value_type array_value[7] = {
            static_cast<value_type>(5),
            static_cast<value_type>(6),
            static_cast<value_type>(7),
            static_cast<value_type>(3),
            static_cast<value_type>(2),
            static_cast<value_type>(15),
            static_cast<value_type>(13)
        };

        value_type* ptr = array_value;

        vector_type vec = ptr;

        alterate::uint_t min_size = std::min<alterate::uint_t>(vec.size(), boost::size(array_value));
        assert_equals<const value_type*, const_iterator>(
            ptr, ptr + min_size,
            vec.cbegin(), vec.cbegin() + min_size);
    }

    TYPED_TEST_P(vector_support_test, container_constructor_test) {
        std::list<value_type> l = { 
            static_cast<value_type>(5),
            static_cast<value_type>(6),
            static_cast<value_type>(7),
            static_cast<value_type>(3),
            static_cast<value_type>(2),
        };

        typedef std::list<value_type>::const_iterator list_iter;
        typedef list_iter::difference_type diff_type;
        vector_type vec = l;

        alterate::uint_t min_size = std::min<alterate::uint_t>(vec.size(), l.size());
        assert_range_equals(l, vec, 0, min_size);
    }

    TYPED_TEST_P(vector_support_test, initializer_list_constructor_test) {
        std::initializer_list<value_type> l = {
            static_cast<value_type>(5),
            static_cast<value_type>(6),
            static_cast<value_type>(7),
            static_cast<value_type>(3),
            static_cast<value_type>(2),
        };

        vector_type vec = l;

        alterate::uint_t min_size = std::min<alterate::uint_t>(vec.size(), l.size());
        assert_range_equals(l, vec, 0, min_size);
    }

    REGISTER_TYPED_TEST_CASE_P(vector_support_test, 
        default_constructor_test,
        scalar_constructor_test,
        array_constructor_test,
        pointer_constructor_test,
        container_constructor_test,
        initializer_list_constructor_test);

    typedef ::testing::Types< 
        alterate::math::vec<int, 1>, 
        alterate::math::vec<float, 3>, 
        alterate::math::vec<char, 7> 
    > core_vector_types;
    INSTANTIATE_TYPED_TEST_CASE_P(core, vector_support_test, core_vector_types);

}

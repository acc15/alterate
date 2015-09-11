#include <list>

#include <boost/range.hpp>

#include <alterate/math/vector_support.h>
#include <alterate/math/vec.h>
#include "test_utils.h"

using namespace alterate::test;

template <typename T>
struct vector_support_test : public ::testing::Test {
    typedef T                           vector_type;
    typedef typename T::const_iterator  const_iterator;
    typedef typename T::value_type      value_type;
};

// those constructor isn't supported by C++ standard
// http://www.cplusplus.com/reference/initializer_list/initializer_list/initializer_list/
//
// template <typename T>
// std::initializer_list<T> make_initializer_list(const std::vector<T>& vec) {
//     return std::initializer_list<T>(&vec.front(), &vec.back());
// }

template <typename T, typename U>
std::vector<T> make_vector(const std::initializer_list<U>& l) {
    std::vector<T> result;
    std::transform(l.begin(), l.end(), std::back_insert_iterator< std::vector<T> >(result), static_cast_fn<T>());
    return result;
}

template <typename T, alterate::uint_t N>
void init_array(const std::vector<T>& vec, T(&a)[N]) {
    std::copy(vec.begin(), vec.end(), a);
}

template <typename T>
std::list<T> make_list(const std::vector<T>& vec) {
    return std::list<T>(vec.begin(), vec.end());
}

template <typename T>
std::vector<T> make_test_vector_1() {
    return make_vector<T, int>({ 5, 6, 7, 3, 2, 15, 13 });
}


TYPED_TEST_CASE_P(vector_support_test);

TYPED_TEST_P(vector_support_test, constructor_default_test) {
    vector_type vec;
    value_type default_value;
    assert_all_elements_equal(default_value, vec);
}

TYPED_TEST_P(vector_support_test, constructor_scalar_test) {
    value_type scalar_value = static_cast<value_type>(58);
    vector_type vec = scalar_value;
    assert_all_elements_equal(scalar_value, vec);
}

TYPED_TEST_P(vector_support_test, constructor_array_test) {
    value_type array_value[7];
    init_array(make_test_vector_1<value_type>(), array_value);

    vector_type vec = array_value;

    size_t min_size = std::min(vec.size(), boost::size(array_value));
    assert_has_equal_elements<const value_type*, const_iterator>(
        array_value, array_value + min_size,
        vec.cbegin(), vec.cbegin() + min_size);
}

TYPED_TEST_P(vector_support_test, constructor_pointer_test) {
    std::vector<value_type> v = make_test_vector_1<value_type>();
    value_type* ptr = &v.front();

    vector_type vec = ptr;

    size_t min_size = std::min(vec.size(), v.size());
    assert_has_equal_elements<const value_type*, const_iterator>(
        ptr, ptr + min_size,
        vec.cbegin(), vec.cbegin() + min_size);
}

TYPED_TEST_P(vector_support_test, constructor_container_test) {
    std::list<value_type> l = make_list(make_test_vector_1<value_type>());
    vector_type vec = l;
    assert_has_equal_elements_between(l, vec);
}

TYPED_TEST_P(vector_support_test, constructor_initializer_list_test) {
    std::initializer_list<value_type> l = { 5, 6, 7, 3, 2, 15, 13 };
    vector_type vec = l;
    assert_has_equal_elements_between(l, vec);
}

TYPED_TEST_P(vector_support_test, constructor_copy_test) {
    vector_type vec1 = { 3,7,4 };
    vector_type vec2 = vec1;
    assert_has_equal_elements(vec1, vec2);
}

TYPED_TEST_P(vector_support_test, assign_scalar_test) {
    vector_type vec1;

    vec1 = 1;
    assert_all_elements_equal(1, vec1);
}

TYPED_TEST_P(vector_support_test, assign_initializer_list_test) {
    vector_type vec1;
    vec1 = { 1, 2, 3, 4, 5, 6, 7 };
    assert_has_equal_elements_between<std::initializer_list<value_type>, vector_type>({ 1, 2, 3, 4, 5, 6, 7 },
        vec1);
}

TYPED_TEST_P(vector_support_test, assign_container_test) {
    vector_type vec1;
    std::vector<value_type> test_vec1 = make_test_vector_1<value_type>();
    vec1 = test_vec1;
    assert_has_equal_elements_between(test_vec1, vec1);
}

TYPED_TEST_P(vector_support_test, assign_array_test) {
    vector_type vec1;

    std::vector<value_type> test_vec1 = make_test_vector_1<value_type>();
    value_type test_arr1[7];
    init_array(test_vec1, test_arr1);
    vec1 = test_arr1;
    assert_has_equal_elements_between(test_vec1, vec1);
}

TYPED_TEST_P(vector_support_test, assign_copy_test) {
    vector_type vec1;
    vector_type vec2 = make_test_vector_1<value_type>();
    vec1 = vec2;
    assert_has_equal_elements(vec2, vec1);
}

TYPED_TEST_P(vector_support_test, for_each_test) {
    vector_type vec1 = make_test_vector_1<value_type>();
    std::vector<value_type> values;
    vec1.for_each([&values](value_type& v) {
        values.push_back(v);
    });
    assert_has_equal_elements(vec1, values);
}

TYPED_TEST_P(vector_support_test, accumulate_test) {
    vector_type vec1 = make_test_vector_1<value_type>();
    value_type actual = vec1.accumulate<value_type>(
        make_test_vector_1<value_type>(),
        [](const value_type& v1, const value_type& v2) { return v1 + v2; });

    value_type expected = value_type();
    for (value_type& v : vec1) {
        expected += v + v;
    }

    ASSERT_EQ(expected, actual);
}

TYPED_TEST_P(vector_support_test, transform_test) {
    vector_type vec1 = make_test_vector_1<value_type>();
    vec1.transform(2, [](const value_type& v1, const value_type& v2) {return v1 * v2; });

    vector_type vec2 = make_test_vector_1<value_type>();
    for (value_type& v : vec2) {
        v *= 2;
    }

    assert_has_equal_elements(vec2, vec1);

}

REGISTER_TYPED_TEST_CASE_P(vector_support_test,
    constructor_default_test,
    constructor_scalar_test,
    constructor_array_test,
    constructor_pointer_test,
    constructor_container_test,
    constructor_initializer_list_test,
    constructor_copy_test,
    assign_scalar_test,
    assign_array_test,
    assign_container_test,
    assign_initializer_list_test,
    assign_copy_test,
    for_each_test,
    accumulate_test,
    transform_test);

typedef ::testing::Types<
    alterate::math::vec<int, 1>,
    alterate::math::vec<float, 3>,
    alterate::math::vec<char, 7>
> core_vector_types;
INSTANTIATE_TYPED_TEST_CASE_P(core, vector_support_test, core_vector_types);

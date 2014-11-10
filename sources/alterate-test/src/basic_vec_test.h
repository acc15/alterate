#include <vector>

#include <gtest/gtest.h>

#include <alterate/math/basic_vec.h>

template <typename T>
class basic_vec_test : public ::testing::Test {

public:
    typedef T vec;

    typedef typename T::value_type value_type;

    template <typename X>
    static value_type t(const X& scalar) {
        return static_cast<value_type>(scalar);
    }

};

TYPED_TEST_CASE_P(basic_vec_test);

TYPED_TEST_P(basic_vec_test, is_default_constructible) {
    TypeParam a();
}

TYPED_TEST_P(basic_vec_test, is_copy_constructible) {
    TypeParam a();
}

TYPED_TEST_P(basic_vec_test, is_container_constructible) {
    std::vector< typename TestFixture::value_type > v;
    v.push_back(TestFixture::t(1));
    v.push_back(TestFixture::t(2));
    v.push_back(TestFixture::t(3));
    TypeParam a(v);

    ASSERT_EQ(1, a[0]);
    ASSERT_EQ(2, a[1]);
    ASSERT_EQ(3, a[2]);

}


REGISTER_TYPED_TEST_CASE_P(basic_vec_test, is_default_constructible, is_copy_constructible, is_container_constructible);


// instantiate using
//typedef ::testing::Types<char, int, unsigned int> MyTypes;
//INSTANTIATE_TYPED_TEST_CASE_P(My, basic_vec_test, MyTypes);
// or
//INSTANTIATE_TYPED_TEST_CASE_P(My, basic_vec_test, int);

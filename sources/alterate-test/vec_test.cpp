#include <gtest/gtest.h>  // C++ Google Test Framework
#include <alterate/vec.h>
#include "test_utils.h"

using namespace alterate;

typedef vec<2, float> test_vec;
//
//
template <typename T>
void assert_vec(test_vec const& v, std::initializer_list<T> const& expected) {
    assert_container<test_vec, T>(v, expected);
}

TEST(vec_test, ctor_initializer_list) {
    test_vec v1 = { 10, 3 };
    assert_vec(v1, { 10, 3 });
}

TEST(vec_test, ctor_pointer) {
    float a1[2] = { 5, 4 };
    test_vec v1(a1);
    assert_vec(v1, { 5, 4 });
}

TEST(vec_test, ctor_array) {
    std::array<float, 2> a1 = { 5, 4 };
    test_vec v1(a1);
    assert_vec(v1, { 5, 4 });
}

TEST(vec_test, ctor_scalar) {
    float a1 = 7.0f;
    test_vec v1(a1);
    assert_vec(v1, { 7, 7 });
}

TEST(vec_test, assign_initializer_list) {
    test_vec v1;
    v1 = { 10, 3 };
    assert_vec(v1, { 10, 3 });
}

TEST(vec_test, assign_pointer) {
    float a1[2] = { 5, 4 };
    test_vec v1;
    v1 = a1;
    assert_vec(v1, { 5, 4 });
}

TEST(vec_test, assign_array) {
    std::array<float, 2> a1 = { 5, 4 };
    test_vec v1;
    v1 = a1;
    assert_vec(v1, { 5, 4 });
}

TEST(vec_test, assign_scalar) {
    float a1 = 7.0f;
    test_vec v1;
    v1 = a1;
    assert_vec(v1, { 7, 7 });
}

TEST(vec_test, negate) {
    test_vec v1 = { 4, 7 };
    v1.negate();
    assert_vec(v1, { -4, -7 });
}

TEST(vec_test, dot_initializer_list) {
    test_vec v1 = { 4, 7 };
    float d = v1.dot({ -2, 11 });
    EXPECT_FLOAT_EQ(d, 69);
}

TEST(vec_test, dot_scalar) {
    test_vec v1 = { 4, 7 };
    float d = v1.dot(5.0f);
    EXPECT_FLOAT_EQ(d, 55);
}

TEST(vec_test, length_square) {
    test_vec v1 = { 4, 7 };
    float d = v1.length_square();
    EXPECT_FLOAT_EQ(d, 65);
}

TEST(vec_test, length) {
    test_vec v1 = { 3, 4 };
    float d = v1.length();
    EXPECT_FLOAT_EQ(d, 5);
}

TEST(vec_test, sum_mutate) {
    test_vec v1 = { 3, 4 };
    v1 += {7, 1};
    assert_vec(v1, { 10, 5 });

    v1 += 3;
    assert_vec(v1, { 13, 8 });

    float x[2] = { -2, -4 };
    v1 += x;
    assert_vec(v1, { 11, 4 });
}

TEST(vec_test, sum) {
    test_vec v1 = { 3, 4 };
    test_vec v2 = v1 + std::initializer_list<float>({ 7, 1 });
    assert_vec(v2, { 10, 5 });

    test_vec v3 = v2 + 3;
    assert_vec(v3, { 13, 8 });

    float x[2] = { -2, -4 };
    test_vec v4 = v3 + x;
    assert_vec(v4, { 11, 4 });

}

TEST(vec_test, sub_mutate) {
    test_vec v1 = { 3, 4 };
    v1 -= {7, 1};
    assert_vec(v1, { -4, 3 });

    v1 -= 3;
    assert_vec(v1, { -7, 0 });

    float x[2] = { -2, -4 };
    v1 -= x;
    assert_vec(v1, { -5, 4 });
}

// TODO add another operator tests

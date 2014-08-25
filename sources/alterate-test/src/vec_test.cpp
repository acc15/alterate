#include "pch.h"
#include <alterate/math/vec.h>
#include "../test/test_utils.h"

namespace {

    using namespace alterate::math;
    using namespace alterate::test;

    typedef vec<float, 2> test_vec;

    TEST(vec_test, sizeof_test) {
        ASSERT_EQ(sizeof(float) * 2, sizeof(test_vec));
    }

    TEST(vec_test, vec_1) {
        vec<int, 1> v1;
        ASSERT_EQ(sizeof(int), sizeof(vec<int, 1>));
        v1.x = 5;
        assert_has_equal_elements({ 5 }, v1);
    }

    TEST(vec_test, vec_2) {
        vec<int, 2> v2;
        ASSERT_EQ(sizeof(int) * 2, sizeof(vec<int, 2>));
        v2.x = 5;
        v2.y = 10;
        assert_has_equal_elements({ 5, 10 }, v2);
    }

    TEST(vec_test, vec_3) {
        vec<int, 3> v3;
        ASSERT_EQ(sizeof(int) * 3, sizeof(vec<int, 3>));
        v3.x = 5;
        v3.y = 10;
        v3.z = 15;
        assert_has_equal_elements({ 5, 10, 15 }, v3);
    }

    TEST(vec_test, vec_4) {
        vec<int, 4> v4;
        ASSERT_EQ(sizeof(int) * 4, sizeof(vec<int, 4>));
        v4.x = 5;
        v4.y = 10;
        v4.z = 15;
        v4.w = 20;
        assert_has_equal_elements({ 5, 10, 15, 20 }, v4);
    }

    TEST(vec_test, ctor_initializer_list) {
        test_vec v1 = { 10, 3 };
        assert_has_equal_elements({ 10, 3 }, v1);
    }

    TEST(vec_test, ctor_pointer) {
        float a1[2] = { 5, 4 };
        test_vec v1(a1);
        assert_has_equal_elements({ 5, 4 }, v1);
    }

    TEST(vec_test, ctor_array) {
        std::array<float, 2> a1 = { 5, 4 };
        test_vec v1(a1);
        assert_has_equal_elements({ 5, 4 }, v1);
    }

    TEST(vec_test, ctor_scalar) {
        float a1 = 7.0f;
        test_vec v1(a1);
        assert_has_equal_elements({ 7, 7 }, v1);
    }

    TEST(vec_test, assign_initializer_list) {
        test_vec v1;
        v1 = { 10, 3 };
        assert_has_equal_elements({ 10, 3 }, v1);
    }

    TEST(vec_test, assign_pointer) {
        float a1[2] = { 5, 4 };
        test_vec v1;
        v1 = a1;
        assert_has_equal_elements({ 5, 4 }, v1);
    }

    TEST(vec_test, assign_array) {
        std::array<float, 2> a1 = { 5, 4 };
        test_vec v1;
        v1 = a1;
        assert_has_equal_elements({ 5, 4 }, v1);
    }

    TEST(vec_test, assign_scalar) {
        float a1 = 7.0f;
        test_vec v1;
        v1 = a1;
        assert_has_equal_elements({ 7, 7 }, v1);
    }

    TEST(vec_test, negate) {
        test_vec v1 = { 4, 7 };
        v1.negate();
        assert_has_equal_elements({ -4, -7 }, v1);
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
        assert_has_equal_elements({ 10, 5 }, v1);

        v1 += 3;
        assert_has_equal_elements({ 13, 8 }, v1);

        float x[2] = { -2, -4 };
        v1 += x;
        assert_has_equal_elements({ 11, 4 }, v1);
    }

    TEST(vec_test, sum) {
        test_vec v1 = { 3, 4 };
        test_vec v2 = v1 + std::initializer_list<float>({ 7, 1 });
        assert_has_equal_elements({ 10, 5 }, v2);

        test_vec v3 = v2 + 3;
        assert_has_equal_elements({ 13, 8 }, v3);

        float x[2] = { -2, -4 };
        test_vec v4 = v3 + x;
        assert_has_equal_elements({ 11, 4 }, v4);

    }

    TEST(vec_test, sub_mutate) {
        test_vec v1 = { 3, 4 };
        v1 -= {7, 1};
        assert_has_equal_elements({ -4, 3 }, v1);

        v1 -= 3;
        assert_has_equal_elements({ -7, 0 }, v1);

        float x[2] = { -2, -4 };
        v1 -= x;
        assert_has_equal_elements({ -5, 4 }, v1);
    }

    // TODO add another operator tests
}

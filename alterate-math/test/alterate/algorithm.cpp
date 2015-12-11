#include <gtest/gtest.h>

#include <array>

#include <alterate/algorithm.hpp>

TEST(algorithm_test, copy_safe_when_source_is_bigger) {

	std::array<int, 3> a = { 10, 11, 12 };
	std::array<int, 2> b = { 1, 2 };

	alterate::copy_safe(a.begin(), a.end(), b.begin(), b.end());

	ASSERT_EQ(a[0], b[0]);
	ASSERT_EQ(a[1], b[1]);

}

TEST(algorithm_test, copy_safe_when_source_is_smaller) {

	std::array<int, 2> a = { 10, 11 };
	std::array<int, 3> b = { 1, 2, 3 };

	alterate::copy_safe(a.begin(), a.end(), b.begin(), b.end());

	ASSERT_EQ(a[0], b[0]);
	ASSERT_EQ(a[1], b[1]);
	ASSERT_EQ(3, b[2]);

}

TEST(algorithm_test, transform_safe_add_when_source_is_smaller) {

	std::array<int, 2> a = { 10, 11 };
	std::array<int, 3> b = { 1, 2, 3 };

	alterate::transform_safe(a.begin(), a.end(), b.begin(), b.end(), [](int x,int y) -> int { return x+y; });

	ASSERT_EQ(11, b[0]);
	ASSERT_EQ(13, b[1]);
	ASSERT_EQ(3, b[2]);

}

TEST(algorithm_test, transform_safe_add_when_source_is_bigger) {

	std::array<int, 3> a = { 10, 11, 12 };
	std::array<int, 2> b = { 1, 2 };

	alterate::transform_safe(a.begin(), a.end(), b.begin(), b.end(), [](int x,int y) -> int { return x+y; });

	ASSERT_EQ(11, b[0]);
	ASSERT_EQ(13, b[1]);

}

TEST(algorithm_test, transform_safe_add) {

	std::array<int, 3> a = { 10, 11, 12 };
	std::array<int, 3> b = { 1, 2, 3 };

	alterate::transform_safe(a.begin(), a.end(), b.begin(), b.end(), [](int x,int y) -> int { return x+y; });

	ASSERT_EQ(11, b[0]);
	ASSERT_EQ(13, b[1]);
	ASSERT_EQ(15, b[2]);

}

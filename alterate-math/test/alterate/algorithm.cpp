#include <gtest/gtest.h>

#include <array>

#include <alterate/algorithm.hpp>

TEST(algorithm_test, copy_min) {

	std::array<3, int> a;
	std::array<2, int> b;

	alterate::copy_min(a.begin(), a.end(), b.begin(), b.end());

	ASSERT_EQ(a[0], b[0]);
	ASSERT_EQ(a[1], b[1]);

}

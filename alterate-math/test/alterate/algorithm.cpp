#include <gmock/gmock.h>

#include <array>

#include <alterate/algorithm.hpp>

using namespace testing;

TEST(algorithm, copy_safe_when_source_is_bigger) {

	std::array<int, 3> a = { 10, 11, 12 };
	std::array<int, 2> b = { 1, 2 };

	alterate::copy_safe(a.begin(), a.end(), b.begin(), b.end());
	ASSERT_THAT(b, ElementsAreArray({10, 11}));

}

TEST(algorithm, copy_safe_when_source_is_smaller) {

	std::array<int, 2> a = { 10, 11 };
	std::array<int, 3> b = { 1, 2, 3 };

	alterate::copy_safe(a.begin(), a.end(), b.begin(), b.end());
	ASSERT_THAT(b, ElementsAreArray({10, 11, 3}));

}

TEST(algorithm, transform_safe_add_when_source_is_smaller) {

	std::array<int, 2> a = { 10, 11 };
	std::array<int, 3> b = { 1, 2, 3 };

	alterate::transform_safe(a.begin(), a.end(), b.begin(), b.end(), [](int x,int y) -> int { return x+y; });
	ASSERT_THAT(b, ElementsAreArray({11,13,3}));

}

TEST(algorithm, transform_safe_add_when_source_is_bigger) {

	std::array<int, 3> a = { 10, 11, 12 };
	std::array<int, 2> b = { 1, 2 };

	alterate::transform_safe(a.begin(), a.end(), b.begin(), b.end(), [](int x,int y) -> int { return x+y; });
	ASSERT_THAT(b, ElementsAreArray({11,13}));

}

TEST(algorithm, transform_safe_add) {

	std::array<int, 3> a = { 10, 11, 12 };
	std::array<int, 3> b = { 1, 2, 3 };

	alterate::transform_safe(a.begin(), a.end(), b.begin(), b.end(), [](int x,int y) -> int { return x+y; });

	ASSERT_THAT(b, ElementsAreArray({11,13,15}));

}

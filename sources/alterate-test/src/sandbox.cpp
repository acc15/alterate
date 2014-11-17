#include <gtest/gtest.h>

#include <alterate/math/vec.h>
#include <alterate/print.h>

template <size_t Count>
using test_vec = alterate::math::vec<int, Count>;

TEST(vec_test, check_constructors) {

    using namespace std;

    test_vec<4> int_vec4(9,8,7,6);
    test_vec<4> int_vec4_i = int_vec4;

    alterate::print_container(int_vec4, cout) << endl;
    alterate::print_container(int_vec4_i, cout) << endl;


}

#include <alterate/math/vec.h>

#include "basic_vec_test.h"

typedef ::testing::Types< alterate::math::vec<3, int> > vec_types;
INSTANTIATE_TYPED_TEST_CASE_P(vec, basic_vec_test, vec_types );



#include "pch.h"

template <typename T>
struct X {
    typedef T& reference;

    const reference to_const_ref(reference ref) {
        return ref;
    }
};

TEST(sandbox, test_const_reference) {

    X<int> x;

    int v = 11;
    const int& v_cr = x.to_const_ref(v);

    v = 15;
    ASSERT_EQ(v, 15);

}
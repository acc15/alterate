

#include "pch.h"

#include "test_utils.h"

#include <alterate/types.h>
#include <alterate/iterator/random_access_iterator_support.h>

namespace {

    using namespace alterate::test;

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

    struct A {};
    struct B {};
    struct C : A, B {};

    TEST(sandbox, size_of_multiple_inheritance) {
        ASSERT_EQ(1, sizeof(C));
    }

    template <typename T, alterate::uint_t Size>
    struct array_with_alias {
        T values[Size];
        T& ref1 = values[0];
        T& ref2 = values[1];
    };

    TEST(sandbox, references_will_take_storage) {

        array_with_alias<int, 4> v;
        int size_of = sizeof(array_with_alias<int, 4>);
        EXPECT_EQ(sizeof(int) * 6, size_of);
        v.ref1 = 10;
        v.ref2 = 15;

    }

    template <typename ValueType, typename BaseType, size_t Size>
    struct vec_info : BaseType {
        typedef typename BaseType::value_type value_type;

    };

    template <typename ValueType, typename BaseType>
    struct vec_info<ValueType, BaseType, 1> : vec_info < ValueType, BaseType, 0 > {
        ValueType x;
    };

    template <typename ValueType, typename BaseType>
    struct vec_info < ValueType, BaseType, 2 > : vec_info < ValueType, BaseType, 1 > {
        ValueType y;
    };

    template <typename ValueType, typename BaseType>
    struct vec_info < ValueType, BaseType, 3 > : vec_info < ValueType, BaseType, 2 > {
        ValueType z;
    };

    template <typename ValueType, typename BaseType>
    struct vec_info < ValueType, BaseType, 4 > : vec_info < ValueType, BaseType, 3 > {
        ValueType w;
    };


    template <typename ValueType, alterate::uint_t Size>
    struct vec_data : vec_info <
        ValueType,
        alterate::iterator::random_access_iterator_support<vec_data<ValueType, Size>, ValueType>,
        Size > {

        size_t size() const {
            return Size;
        }

        value_type& operator[](size_t i) {
            return reinterpret_cast<value_type*>(this)[i];
        }

        const value_type& operator[](size_t i) const {
            return reinterpret_cast<const value_type*>(this)[i];
        }

    };

    TEST(sandbox, vec_data_test) {

        vec_data<int, 4> v;
        v.x = 9;
        v.y = 7;
        v.z = 3;
        v.w = 10;

        static_assert(sizeof(vec_data<int, 4>) == sizeof(int) * 4, "4-component int Vector should take 16 bytes");
        assert_has_equal_elements({ 9, 7, 3, 10 }, v);

    }

    struct basic_xyz {
        int x, y, z;
    };

    struct virtual_xyz : basic_xyz {
        virtual int get_value() const {
            return x;
        }
    };
    struct virtual_xyz_ex : virtual_xyz {
        virtual int get_value() const {
            return y;
        }
    };

    TEST(sandbox, vft_can_be_in_any_place) {

        virtual_xyz_ex vex;
        vex.y = 10;
        int v = vex.get_value();
        ASSERT_EQ(10, v);
        ASSERT_GT(sizeof(virtual_xyz_ex), sizeof(basic_xyz));
        ASSERT_NE(reinterpret_cast<void*>(&vex), reinterpret_cast<void*>(&vex.x));

    }

}
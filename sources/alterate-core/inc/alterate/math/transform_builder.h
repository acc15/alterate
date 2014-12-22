#pragma once

#include <type_traits>

namespace alterate {
namespace math {

template <typename MatrixType>
class transform_builder {

public:
    typedef MatrixType                                          return_type;
    typedef typename std::remove_reference<MatrixType>::type    matrix_type;


    return_type _result;

public:
    transform_builder(return_type m) : _result(m) {
    }

    transform_builder& identity() {
        _result.set_to_identity();
        return *this;
    }

    template <typename Vector>
    transform_builder& translate(const Vector& vec) {
        _result.pre_multiply(matrix_type::template translate< Vector >(vec));
        return *this;
    }

    template <typename Type>
    transform_builder& translate(const std::initializer_list<Type>& vec) {
        return translate< std::initializer_list<Type> >(vec);
    }

    template <typename Vector>
    transform_builder& scale(const Vector& vec) {
        _result.pre_multiply(matrix_type::template scale< Vector >(vec));
        return *this;
    }

    template <typename Type>
    transform_builder& scale(const std::initializer_list<Type>& vec) {
        return scale< std::initializer_list<Type> >(vec);
    }

    template <typename Scalar>
    transform_builder& rotate_z(const Scalar& angle) {
        _result.pre_multiply(matrix_type::template rotate_z< Scalar >(angle));
        return *this;
    }

    template <typename Scalar>
    transform_builder& rotate_z(const Scalar& cos, const Scalar& sin) {
        _result.pre_multiply(matrix_type::template rotate_z< Scalar, Scalar >(cos, sin));
        return *this;
    }

    return_type local_to_world() {
        return _result;
    }

    return_type world_to_local() {
        _result.invert();
        return _result;
    }

};



}
}

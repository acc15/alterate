#pragma once

#include <type_traits>

namespace alterate {
namespace math {

template <typename MatrixType>
class matrix_builder {

private:
    MatrixType _result;

public:
    matrix_builder(MatrixType& m) : _result(m) {
        _result.set_to_identity();
    }

    template <typename Vector>
    matrix_builder& translate(const Vector& vec) {
        _result.pre_multiply(MatrixType::template translate< Vector >(vec));
        return *this;
    }

    template <typename Type>
    matrix_builder& translate(const std::initializer_list<Type>& vec) {
        return translate< std::initializer_list<Type> >(vec);
    }

    template <typename Vector>
    matrix_builder& scale(const Vector& vec) {
        _result.pre_multiply(MatrixType::template scale< Vector >(vec));
        return *this;
    }

    template <typename Type>
    matrix_builder& scale(const std::initializer_list<Type>& vec) {
        return scale< std::initializer_list<Type> >(vec);
    }

    template <typename Scalar>
    matrix_builder& rotate_z(const Scalar& angle) {
        _result.pre_multiply(MatrixType::template rotate_z< Scalar >(angle));
        return *this;
    }

    template <typename Scalar>
    matrix_builder& rotate_z(const Scalar& cos, const Scalar& sin) {
        _result.pre_multiply(MatrixType::template rotate_z< Scalar >(cos, sin));
        return *this;
    }

    MatrixType& local_to_world() {
        return _result;
    }

    MatrixType& world_to_local() {
        _result.invert();
        return _result;
    }

};



}
}

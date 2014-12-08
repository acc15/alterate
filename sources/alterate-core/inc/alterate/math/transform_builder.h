#pragma once

namespace alterate {
namespace math {

template <typename MatrixType>
class transform_builder {

    MatrixType _result;

public:
    transform_builder(MatrixType m) : _result(m) {
    }

    template <typename Vector>
    transform_builder& translate(const Vector& vec) {
        _result.pre_multiply(MatrixType::translate(vec));
        return *this;
    }

    template <typename Vector>
    transform_builder& scale(const Vector& vec) {
        _result.pre_multiply(MatrixType::scale(vec));
        return *this;
    }

    template <typename Scalar>
    transform_builder& rotate_z(const Scalar& angle) {
        _result.pre_multiply(MatrixType::rotate(angle));
        return *this;
    }

    template <typename Scalar>
    transform_builder& rotate_z(const Scalar& cos, const Scalar& sin) {
        _result.pre_multiply(MatrixType::rotate(cos, sin));
        return *this;
    }

    template <typename Type>
    transform_builder& translate(const std::initializer_list<Type>& vec) {
        _result.pre_multiply(MatrixType::translate(vec));
        return *this;
    }

    template <typename Type>
    transform_builder& scale(const std::initializer_list<Type>& vec) {
        _result.pre_multiply(MatrixType::scale(vec));
        return *this;
    }

    MatrixType local_to_world() {
        return _result;
    }

    MatrixType world_to_local() {
        _result.invert();
        return _result;
    }

};



}
}

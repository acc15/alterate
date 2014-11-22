#pragma once

#include <math.h>

#include <boost/assert.hpp>
#include <alterate/iterator/iterator_factory.h>

namespace alterate {
namespace math {


struct matrix_tag {};

template <typename MatrixTraits>
class matrix_support: public matrix_tag {
private:

    typedef typename MatrixTraits::type         matrix_type;
    typedef typename MatrixTraits::value_type   value_type;

    inline matrix_type& get_this() {
        return *static_cast<matrix_type*>(this);
    }

    inline const matrix_type& get_this() const {
        return *static_cast<const matrix_type*>(this);
    }

    template <typename Vector>
    matrix_type& set_row_impl(size_t row, const Vector& vec) {
        typedef alterate::iterator::iterator_factory<Vector> iterator_factory;
        typedef typename iterator_factory::iterator iterator;

        iterator iter = iterator_factory::begin(vec);
        const iterator iter_end = iterator_factory::end(vec, cols());
        for (int j=0; j<cols() && iter != iter_end; j++, iter++) {
            (*this)(row, j) = (*iter);
        }
        return get_this();
    }

    template <typename Vector>
    matrix_type& set_col_impl(size_t col, const Vector& vec) {
        typedef alterate::iterator::iterator_factory<Vector> iterator_factory;
        typedef typename iterator_factory::iterator iterator;

        iterator iter = iterator_factory::begin(vec);
        const iterator iter_end = iterator_factory::end(vec, cols());
        for (int j=0; j<rows() && iter != iter_end; j++, iter++) {
            (*this)(j, col) = (*iter);
        }
        return get_this();
    }


    template <typename Result, typename Vector>
    Result& map_impl(const Vector& vec, Result& result) const {

        typedef alterate::iterator::iterator_factory<Vector> iterator_factory;
        typedef typename iterator_factory::iterator iterator;

        const iterator iter_end = iterator_factory::end(vec, cols());
        for (size_t i=0; i<rows() && i<result.size(); i++) {

            value_type sum = 0;

            size_t k=0;
            for (iterator iter = iterator_factory::begin(vec);
                 iter != iter_end && k < cols();
                 iter++, k++) {
                sum += (*this)(i,k) * (*iter);
            }
            for (;k<cols();k++) {
                sum += (*this)(i,k);
            }
            result[i] = sum;
        }
        return result;

    }

public:

    size_t rows() const {
        return get_this().rows();
    }

    size_t cols() const {
        return get_this().cols();
    }

    matrix_support() {}

    template <typename Init>
    matrix_support(const Init& init) {
        *this = init;
    }

    template <typename Type>
    matrix_type& set_row(size_t row, const std::initializer_list<Type>& vec) {
        return set_row_impl(row, vec);
    }

    template <typename Vector>
    matrix_type& set_row(size_t row, const Vector& vec) {
        return set_row_impl(row, vec);
    }

    template <typename Type>
    matrix_type& set_col(size_t col, const std::initializer_list<Type>& vec) {
        return set_col_impl(col, vec);
    }

    template <typename Vector>
    matrix_type& set_col(size_t col, const Vector& vec) {
        return set_col_impl(col, vec);
    }

    template <typename Vector>
    Vector& get_row(size_t row, Vector& v) const {
        for (size_t i=0; i<cols(); i++) {
            v[i] = (*this)(row, i);
        }
        return v;
    }

    template <typename Vector>
    Vector& get_col(size_t col, Vector& v) const {
        for (size_t i=0; i<rows(); i++) {
            v[i] = (*this)(i, col);
        }
        return v;
    }

    template <typename Vector>
    Vector get_row(size_t row) const {
        Vector v;
        return get_row(row, v);
    }

    template <typename Vector>
    Vector get_col(size_t col) const {
        Vector v;
        return get_col(col, v);
    }

    value_type compute_determinant() const {

        matrix_type tmp = get_this();

        size_t permutation[rows()];
        for (size_t i = 0; i < rows(); i++) {
            permutation[i] = i;
        }

        value_type det = 1;
        for (size_t i = 0; i < rows()-1; i++) {
            size_t pivot = i;
            while (pivot < rows() && tmp(i, permutation[pivot]) == 0) {
                pivot++;
            }
            if (pivot == rows()) {
                return 0;
            }
            if (pivot != i) {
                std::swap(permutation[i], permutation[pivot]);
                det = -det;
            }
            det *= tmp(i, permutation[i]);
            for (int j = i + 1; j < rows(); j++) {
                value_type num = tmp(j, permutation[i]);
                if (num != 0) {
                    value_type multiplier = num / tmp(i, permutation[i]);
                    for (int k = i + 1; k < cols(); k++) {
                        tmp(j, permutation[k]) -= tmp(i, permutation[k]) * multiplier;
                    }
                }
            }
        }
        det *= tmp(rows()-1, permutation[rows()-1]);
        return det;
    }

    matrix_type& set_to_identity() {
        for (size_t i=0; i<rows(); i++) {
            for (size_t j=0; j<cols(); j++) {
                (*this)(i,j) = (i==j ? 1 : 0);
            }
        }
        return get_this();
    }

    template <typename Vector>
    matrix_type& set_to_translate(const Vector& vec) {

        typedef alterate::iterator::iterator_factory<Vector> iterator_factory;
        typedef typename iterator_factory::iterator iterator;

        iterator iter = iterator_factory::begin(vec);
        const iterator iter_end = iterator_factory::end(vec, rows());
        for (size_t i=0; i<rows(); i++) {
            for (size_t j=0; j<cols(); j++) {
                value_type& cell = (*this)(i,j);
                if (j == (cols()-1) && iter != iter_end) {
                    cell = (*iter);
                    ++iter;
                } else {
                    cell = (i == j ? 1 : 0);
                }
            }
        }
        return get_this();
    }

    template <typename Vector>
    matrix_type& set_to_scale(const Vector& vec) {

        typedef alterate::iterator::iterator_factory<Vector> iterator_factory;
        typedef typename iterator_factory::iterator iterator;

        iterator iter = iterator_factory::begin(vec);
        const iterator iter_end = iterator_factory::end(vec, std::min(rows(), cols()));
        for (size_t i=0; i<rows(); i++) {
            for (size_t j=0; j<cols(); j++) {
                value_type& cell = (*this)(i,j);
                if (i != j) {
                    cell = 0;
                    continue;
                }
                if (iter == iter_end) {
                    cell = 1;
                    continue;
                }
                cell = static_cast<value_type>(*iter);
                ++iter;
            }
        }
        return get_this();
    }

    template <typename ScalarType>
    matrix_type& set_to_rotate_z(const ScalarType& angle) {
        return set_to_rotate_z(::cos(angle), ::sin(angle));
    }

    template <typename ScalarType>
    matrix_type& set_to_rotate_z(const ScalarType& cos, const ScalarType& sin) {
        for (size_t i=0; i<rows(); i++) {
            for (size_t j=0; j<cols(); j++) {
                value_type& cell = (*this)(i,j);
                if (i == 0) {
                    if (j == 0) {
                        cell = cos;
                    } else if (j == 1) {
                        cell = -sin;
                    } else {
                        cell = 0;
                    }
                } else if (i == 1) {
                    if (j == 0) {
                        cell = sin;
                    } else if (j == 1) {
                        cell = cos;
                    } else {
                        cell = 0;
                    }
                } else {
                    cell = (i == j ? 1 : 0);
                }
            }
        }
        return get_this();
    }
    
    template <typename OtherMatrix>
    matrix_type& multiply(const OtherMatrix& multiplier) {
        return get_this() = get_this() * multiplier;
    }

    template <typename OtherMatrix>
    matrix_type& operator*=(const OtherMatrix& multiplier) {
        return multiply(multiplier);
    }

    template <typename OtherMatrix>
    typename MatrixTraits::template multiplication_type<matrix_type, OtherMatrix>::type operator*(
            const OtherMatrix& multiplier) const {
        BOOST_ASSERT_MSG(cols() == multiplier.cols(), "matricies can't be multiplied");

        typename MatrixTraits::template multiplication_type<matrix_type, OtherMatrix>::type result;
        result.resize(rows(), multiplier.cols());
        for (size_t i=0; i<result.rows(); i++) {
            for (size_t j=0; j<result.cols(); j++) {
                value_type sum = 0;
                for (size_t k=0; k<cols(); k++) {
                    sum += (*this)(i, k) * multiplier(k, j);
                }
                result(i,j) = sum;
            }
        }
        return result;
    }

    template <typename OtherMatrixTraits>
    matrix_type& operator=(const matrix_support<OtherMatrixTraits>& copy) {
        get_this().resize(copy.rows(), copy.cols());
        for (size_t i=0; i<std::min(rows(), copy.rows()); i++) {
            for (size_t j=0; j<std::min(cols(), copy.cols()); j++) {
                (*this)(i,j) = copy(i,j);
            }
        }
        return get_this();
    }

    template <typename Vector>
    typename std::enable_if<
        std::conditional<std::is_base_of<matrix_tag, Vector>::value, std::false_type, std::true_type>::type::value,
        matrix_type&>::type operator=(const Vector& vec) {

        typedef alterate::iterator::iterator_factory<Vector> iterator_factory;
        typedef typename iterator_factory::iterator iterator;

        iterator iter = iterator_factory::begin(vec);
        const iterator iter_end = iterator_factory::end(vec, std::min(rows(), cols()));
        if (iter != iter_end) {
            for (size_t i=0; i<rows(); i++) {
                for (size_t j=0; j<cols(); j++) {
                    (*this)(i,j) = *iter;
                    ++iter;
                    if (iter == iter_end) {
                        break;
                    }
                }
            }
        }
        return get_this();
    }

    const value_type& operator()(size_t row, size_t col) const {
        return get_this().cell(row, col);
    }

    value_type& operator()(size_t row, size_t col) {
        return get_this().cell(row, col);
    }

    template <typename Result, typename Vector>
    Result& map(const Vector& vector, Result& result) const {
        return map_impl(vector, result);
    }

    template <typename Result, typename Type>
    Result& map(const std::initializer_list<Type>& vector, Result& result) const {
        return map_impl(vector, result);
    }

    template <typename Result, typename Vector>
    Result map(const Vector& vector) const {
        Result result;
        return map_impl(vector, result);
    }

    template <typename Result, typename Type>
    Result map(const std::initializer_list<Type>& vector) const {
        Result result;
        return map_impl(vector, result);
    }

    template <typename Type>
    static matrix_type scale(const std::initializer_list<Type>& vec) {
        return matrix_type().set_to_scale(vec);
    }

    template <typename Vector>
    static matrix_type scale(const Vector& vec) {
        return matrix_type().set_to_scale(vec);
    }

    template <typename Type>
    static matrix_type translate(const std::initializer_list<Type>& vec) {
        return matrix_type().set_to_translate(vec);
    }

    template <typename Vector>
    static matrix_type translate(const Vector& vec) {
        return matrix_type().set_to_translate(vec);
    }

    template <typename Scalar>
    static matrix_type rotate_z(const Scalar& angle) {
        return matrix_type().set_to_rotate_z(angle);
    }

    template <typename Scalar>
    static matrix_type rotate_z(const Scalar& cos, const Scalar& sin) {
        return matrix_type().set_to_rotate_z(cos, sin);
    }

    static matrix_type identity() {
        return matrix_type().set_to_identity();
    }

};

struct row_major_order {
    static size_t compute_flat_index(size_t row, size_t col, size_t /*rows*/, size_t cols) {
        return row * cols + col;
    }
};

struct column_major_order {
    static size_t compute_flat_index(size_t row, size_t col, size_t rows, size_t /*cols*/) {
        return col * rows + row;
    }
};


template <typename T, size_t Rows, size_t Cols, typename Order>
struct flat_container_matrix_traits;

template <typename T, size_t Rows, size_t Cols, typename Order=row_major_order, typename Container = T[Rows*Cols]>
class matrix: public matrix_support<flat_container_matrix_traits<T,Rows,Cols,Order>> {
public:

    typedef matrix_support<flat_container_matrix_traits<T,Rows,Cols,Order>> matrix_support_type;
    typedef T           value_type;
    typedef Container   container_type;
    typedef Order       order_type;

    container_type data;


    enum {
        row_count = Rows,
        col_count = Cols
    };


    size_t rows() const { return Rows; }
    size_t cols() const { return Cols; }

    matrix() {}

    template <typename InitType>
    matrix(const InitType& init) : matrix_support_type(init) {
    }

    template <typename ValueType>
    matrix(const std::initializer_list<ValueType>& list) : matrix_support_type(list) {
    }

    value_type& cell(size_t row, size_t col) {
        return data[order_type::compute_flat_index(row, col, Rows, Cols)];
    }

    const value_type& cell(size_t row, size_t col) const {
        return data[order_type::compute_flat_index(row, col, Rows, Cols)];
    }

    void resize(size_t /*rows*/, size_t /*cols*/) {
        // since this matrix is static then implementation is no-op
    }
};

template <typename T, size_t Rows, size_t Cols, typename Order>
struct flat_container_matrix_traits {

    typedef T           value_type;

    template <typename Multiplicand, typename Multiplier>
    struct multiplication_type {
        typedef matrix<typename Multiplicand::value_type, Multiplicand::row_count, Multiplier::col_count> type;
    };

    typedef matrix<T, Rows,Cols, Order> type;
};

}
}

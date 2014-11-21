#pragma once

#include <math.h>

#include <boost/integer/static_min_max.hpp>

#include <alterate/iterator/iterator_factory.h>

#include <type_traits>

namespace alterate {
namespace math {


struct matrix_tag {};

template <typename MatrixTraits, size_t Rows, size_t Cols>
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
        const iterator iter_end = iterator_factory::end(vec, Cols);
        for (int j=0; j<Cols && iter != iter_end; j++, iter++) {
            (*this)(row, j) = (*iter);
        }
        return get_this();
    }

    template <typename Vector>
    matrix_type& set_col_impl(size_t col, const Vector& vec) {
        typedef alterate::iterator::iterator_factory<Vector> iterator_factory;
        typedef typename iterator_factory::iterator iterator;

        iterator iter = iterator_factory::begin(vec);
        const iterator iter_end = iterator_factory::end(vec, Cols);
        for (int j=0; j<Rows && iter != iter_end; j++, iter++) {
            (*this)(j, col) = (*iter);
        }
        return get_this();
    }


    template <typename Result, typename Vector>
    Result& map_impl(const Vector& vec, Result& result) const {

        typedef alterate::iterator::iterator_factory<Vector> iterator_factory;
        typedef typename iterator_factory::iterator iterator;

        const iterator iter_end = iterator_factory::end(vec, Cols);
        for (size_t i=0; i<Rows && i<result.size(); i++) {

            value_type sum = 0;

            size_t k=0;
            for (iterator iter = iterator_factory::begin(vec);
                 iter != iter_end && k < Cols;
                 iter++, k++) {
                sum += (*this)(i,k) * (*iter);
            }
            for (;k<Cols;k++) {
                sum += (*this)(i,k);
            }
            result[i] = sum;
        }
        return result;

    }

public:

    enum {
        row_count = Rows,
        col_count = Cols
    };

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
        for (size_t i=0; i<Cols; i++) {
            v[i] = (*this)(row, i);
        }
        return v;
    }

    template <typename Vector>
    Vector& get_col(size_t col, Vector& v) const {
        for (size_t i=0; i<Rows; i++) {
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

        size_t permutation[Rows];
        for (size_t i = 0; i < Rows; i++) {
            permutation[i] = i;
        }

        value_type det = 1;
        for (size_t i = 0; i < Rows-1; i++) {
            size_t pivot = i;
            while (pivot < Rows && tmp(i, permutation[pivot]) == 0) {
                pivot++;
            }
            if (pivot == Rows) {
                return 0;
            }
            if (pivot != i) {
                std::swap(permutation[i], permutation[pivot]);
                det = -det;
            }
            det *= tmp(i, permutation[i]);
            for (int j = i + 1; j < Rows; j++) {
                value_type multiplier = tmp(j, permutation[i]) / tmp(i, permutation[i]);
                for (int k = i + 1; k < Cols; k++) {
                    tmp(j, permutation[k]) -= tmp(i, permutation[k]) * multiplier;
                }
            }
        }
        det *= tmp(Rows-1, permutation[Rows-1]);
        return det;
    }

    matrix_type& set_to_identity() {
        for (size_t i=0; i<Rows; i++) {
            for (size_t j=0; j<Cols; j++) {
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
        const iterator iter_end = iterator_factory::end(vec, Rows);
        for (size_t i=0; i<Rows; i++) {
            for (size_t j=0; j<Cols; j++) {
                value_type& cell = (*this)(i,j);
                if (j == (Cols-1) && iter != iter_end) {
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
        const iterator iter_end = iterator_factory::end(vec, boost::static_unsigned_min<Rows,Cols>::value);
        for (size_t i=0; i<Rows; i++) {
            for (size_t j=0; j<Cols; j++) {
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
        for (size_t i=0; i<Rows; i++) {
            for (size_t j=0; j<Cols; j++) {
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
    
    template <typename OtherMatrixTraits>
    matrix_type& multiply(const matrix_support<OtherMatrixTraits, Rows, Cols>& multiplier) {
        static_assert(Rows == Cols, "mutable multiplication is available only for square matricies");

        value_type current_row[Cols];
        for (size_t i=0; i<Rows; i++) {
            get_row(i, current_row);
            for (size_t j=0; j<Cols; j++) {
                value_type sum = 0;
                for (size_t k=0; k<Cols; k++) {
                    sum += current_row[k] * multiplier(k,j);
                }
                (*this)(i,j) = sum;
            }
        }
        return get_this();
    }

    template <typename OtherMatrixTraits>
    matrix_type& operator*=(const matrix_support<OtherMatrixTraits, Rows, Cols>& multiplier) {
        return multiply(multiplier);
    }

    template <typename OtherMatrixTraits, size_t OtherCols>
    typename MatrixTraits::template by_size<Rows, OtherCols>::type operator*(
            const matrix_support<OtherMatrixTraits, Cols, OtherCols>& multiplier) const {
        typename MatrixTraits::template by_size<Rows, OtherCols>::type result;
        for (size_t i=0; i<Rows; i++) {
            for (size_t j=0; j<OtherCols; j++) {
                value_type sum = 0;
                for (size_t k=0; k<Cols; k++) {
                    sum += (*this)(i, k) * multiplier(k, j);
                }
                result(i,j) = sum;
            }
        }
        return result;
    }

    template <typename OtherMatrixTraits, size_t OtherRows, size_t OtherCols>
    matrix_type& operator=(const matrix_support<OtherMatrixTraits, OtherRows, OtherCols>& copy) {
        for (size_t i=0; i<boost::static_unsigned_min<Rows, OtherRows>::value; i++) {
            for (size_t j=0; j<boost::static_unsigned_min<Cols, OtherCols>::value; j++) {
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
        const iterator iter_end = iterator_factory::end(vec, boost::static_unsigned_min<Rows,Cols>::value);
        if (iter != iter_end) {
            for (size_t i=0; i<Rows; i++) {
                for (size_t j=0; j<Cols; j++) {
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
    static matrix_type rotate_z_sincos(const Scalar& cos, const Scalar& sin) {
        return matrix_type().set_to_rotate_z(cos, sin);
    }

    static matrix_type identity() {
        return matrix_type().set_to_identity();
    }

};

struct row_major_order {
    template <size_t Rows, size_t Cols>
    static size_t compute_flat_index(size_t row, size_t col) {
        return row * Cols + col;
    }
};

struct column_major_order {
    template <size_t Rows, size_t Cols>
    static size_t compute_flat_index(size_t row, size_t col) {
        return col * Rows + row;
    }
};


template <typename T, size_t Rows, size_t Cols, typename Order>
struct flat_container_matrix_traits;

template <typename T, size_t Rows, size_t Cols, typename Order=row_major_order, typename Container = T[Rows*Cols]>
class matrix: public matrix_support<flat_container_matrix_traits<T,Rows,Cols,Order>, Rows, Cols> {
public:

    typedef matrix_support<flat_container_matrix_traits<T,Rows,Cols,Order>, Rows, Cols> matrix_support_type;
    typedef T           value_type;
    typedef Container   container_type;
    typedef Order       order_type;

    container_type data;

    matrix() {}

    template <typename InitType>
    matrix(const InitType& init) : matrix_support_type(init) {
    }

    template <typename ValueType>
    matrix(const std::initializer_list<ValueType>& list) : matrix_support_type(list) {
    }

    value_type& cell(size_t row, size_t col) {
        return data[order_type::template compute_flat_index<Rows,Cols>(row, col)];
    }

    const value_type& cell(size_t row, size_t col) const {
        return data[order_type::template compute_flat_index<Rows,Cols>(row, col)];
    }

};

template <typename T, size_t Rows, size_t Cols, typename Order>
struct flat_container_matrix_traits {

    typedef T           value_type;

    template <size_t AnotherRows, size_t AnotherCols>
    struct by_size {
        typedef matrix<T, AnotherRows, AnotherCols, Order> type;
    };

    typedef matrix<T, Rows,Cols, Order> type;
};

}
}

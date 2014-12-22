#pragma once

#include <math.h>

#include <boost/assert.hpp>
#include <alterate/iterator/iterator_factory.h>

#include <iostream>
#include <iomanip>

#include <alterate/math/transform_builder.h>

namespace alterate {
namespace math {

struct matrix_tag {};

template <typename MatrixTraits>
class matrix_support: public matrix_tag {
public:
    typedef MatrixTraits matrix_traits;
    typedef typename matrix_traits::matrix_type                 matrix_type;
    typedef typename matrix_traits::value_type                  value_type;
    typedef typename matrix_traits::permutation_matrix_type     permutation_matrix_type;

private:
    inline matrix_type& get_this() {
        return *static_cast<matrix_type*>(this);
    }

    inline const matrix_type& get_this() const {
        return *static_cast<const matrix_type*>(this);
    }

public:
    size_t rows() const {
        return get_this().rows();
    }

    size_t cols() const {
        return get_this().cols();
    }

    value_type& cell(size_t i, size_t j) {
        return get_this().cell(i,j);
    }

    const value_type& cell(size_t i, size_t j) const {
        return get_this().cell(i,j);
    }


private:

    void init_permutation(permutation_matrix_type& p) const {
        matrix_traits::resize_permutation(p, cols());
        for (size_t i=0; i<cols(); i++) {
            p[i] = i;
        }
    }

    template <typename Vector>
    matrix_type& set_row_impl(size_t row, const Vector& vec) {
        typedef alterate::iterator::iterator_factory<Vector> iterator_factory;
        typedef typename iterator_factory::iterator iterator;

        iterator iter = iterator_factory::begin(vec);
        const iterator iter_end = iterator_factory::end(vec, cols());
        for (int j=0; j<cols() && iter != iter_end; j++, iter++) {
            cell(row, j) = (*iter);
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
            cell(j, col) = (*iter);
        }
        return get_this();
    }


    template <typename Result, typename Vector>
    Result& transform_impl(const Vector& vec, Result& result) const {

        typedef alterate::iterator::iterator_factory<Vector> iterator_factory;
        typedef typename iterator_factory::iterator iterator;

        const iterator iter_end = iterator_factory::end(vec, cols());
        for (size_t i=0; i<rows() && i<result.size(); i++) {

            value_type sum = 0;

            size_t k=0;
            for (iterator iter = iterator_factory::begin(vec);
                 iter != iter_end && k < cols();
                 iter++, k++) {
                sum += cell(i,k) * (*iter);
            }
            for (;k<cols();k++) {
                sum += cell(i,k);
            }
            result[i] = sum;
        }
        return result;

    }

    void add_row(const value_type& scale, const permutation_matrix_type& p, size_t source_row, size_t target_row, size_t start_column) {
        for (size_t k=start_column; k<cols(); k++) {
            cell(target_row,p[k]) += cell(source_row,p[k])*scale;
        }
    }

public:
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

    matrix_type& swap_row(size_t row1, size_t row2) {
        for (size_t j=0;j<cols();j++) {
            std::swap(cell(row1,j), cell(row2,j));
        }
        return get_this();
    }

    matrix_type& swap_col(size_t col1, size_t col2) {
        for (size_t i=0;i<rows();i++) {
            std::swap(cell(i,col1), cell(i,col2));
        }
        return get_this();
    }

    template <typename Vector>
    Vector& get_row(size_t row, Vector& v) const {
        for (size_t i=0; i<cols(); i++) {
            v[i] = cell(row, i);
        }
        return v;
    }

    template <typename Vector>
    Vector& get_col(size_t col, Vector& v) const {
        for (size_t i=0; i<rows(); i++) {
            v[i] = cell(i, col);
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

    typename matrix_traits::transposed_matrix_type compute_transposed() const {
        typedef typename matrix_traits::transposed_matrix_type result_type;
        result_type result;
        result_type::matrix_traits::resize(result, cols(), rows());
        for (size_t i=0; i<rows(); i++) {
            for (size_t j=0; j<cols(); j++) {
                result(j,i) = cell(i,j);
            }
        }
        return result;
    }

    matrix_type& transpose() {
        return get_this() = compute_transposed();
    }

    bool compute_lu_decomposition(matrix_type& lu, permutation_matrix_type& p) const {
        return (lu = get_this()).lu_decomposition(p);
    }

    bool lu_decomposition(permutation_matrix_type& p) {
        if (rows() != cols()) {
            BOOST_ASSERT_MSG(false, "LUP decomposition availaible only for square matricies");
            return false;
        }
        init_permutation(p);
        for (size_t i = 0; i < rows()-1; i++) {
            if (cell(i,p[i]) == 0) {
                size_t pivot = i;
                do {
                    ++pivot;
                    if (pivot >= cols()) {
                        return false;
                    }
                } while (cell(i, p[pivot]) == 0);
                std::swap(p[i], p[pivot]);
            }
            for (size_t k = i + 1; k < rows(); k++) {
                for (size_t j = i + 1; j < cols(); j++) {
                    cell(k, p[j]) -= cell(i, p[j]) * cell(k, p[i]) / cell(i, p[i]);
                }
                cell(k, p[i]) /= cell(i, p[i]);
            }
        }
        return true;
    }

    /**
     * result matrix must have permutated rows as specified by permutation matrix [p]
     */
    void lu_substitute(matrix_type& result, const permutation_matrix_type& p) const {
        for (size_t j=0; j<cols(); j++) {
            for (size_t i=0; i<rows();i++) {
                value_type& c = result(p[i],j);
                for (size_t k=0; k<i; k++) {
                    c -= cell(i, p[k]) * result(p[k],j);
                }
            }
            for (size_t i=rows()-1; i != static_cast<size_t>(-1); i--) {
                value_type& c = result(p[i],j);
                for (size_t k=cols()-1; k > i; k--) {
                    c -= cell(i, p[k]) * result(p[k],j);
                }
                c /= cell(i, p[i]);
            }
        }
    }

    bool invert() {
        matrix_type lu;
        permutation_matrix_type p;
        if (!compute_lu_decomposition(lu, p)) {
            return false;
        }
        for (size_t i=0; i<rows(); i++) {
            for (size_t j=0; j<cols(); j++) {
                cell(i,p[j]) = (i==j?1:0);
            }
        }
        lu.lu_substitute(get_this(), p);
        return true;
    }

    value_type compute_determinant() const {
        matrix_type m;
        permutation_matrix_type p;
        if (!compute_lu_decomposition(m, p)) {
            return 0;
        }

        value_type det = 1;

        size_t swap_count = 0;
        for (size_t i=0; i<m.rows(); i++) {
            if (p[i] != i) {
                ++swap_count;
            }
            det *= m(i, p[i]);
        }
        if (swap_count > 0 && ((swap_count - 1) & 1) == 1) {
            return -det;
        }
        return det;
    }

    bool compute_inverse(matrix_type& i) const {
        return (i = get_this()).invert();
    }

    matrix_type& set_to_identity() {
        for (size_t i=0; i<rows(); i++) {
            for (size_t j=0; j<cols(); j++) {
                cell(i,j) = (i==j ? 1 : 0);
            }
        }
        return get_this();
    }

    matrix_type operator~() {
        matrix_type inv = get_this();
        inv.invert();
        return inv;
    }

    template <typename Vector>
    matrix_type& set_to_translate(const Vector& vec) {

        typedef alterate::iterator::iterator_factory<Vector> iterator_factory;
        typedef typename iterator_factory::iterator iterator;

        iterator iter = iterator_factory::begin(vec);
        const iterator iter_end = iterator_factory::end(vec, rows());
        for (size_t i=0; i<rows(); i++) {
            for (size_t j=0; j<cols(); j++) {
                value_type& c = cell(i,j);
                if (j == (cols()-1) && iter != iter_end) {
                    c = (*iter);
                    ++iter;
                } else {
                    c = (i == j ? 1 : 0);
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
                value_type& c = cell(i,j);
                if (i != j) {
                    c = 0;
                    continue;
                }
                if (iter == iter_end) {
                    c = 1;
                    continue;
                }
                c = static_cast<value_type>(*iter);
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
                value_type& c = cell(i,j);
                if (i == 0) {
                    if (j == 0) {
                        c = cos;
                    } else if (j == 1) {
                        c = -sin;
                    } else {
                        c = 0;
                    }
                } else if (i == 1) {
                    if (j == 0) {
                        c = sin;
                    } else if (j == 1) {
                        c = cos;
                    } else {
                        c = 0;
                    }
                } else {
                    c = (i == j ? 1 : 0);
                }
            }
        }
        return get_this();
    }
    
    template <typename OtherMatrix>
    matrix_type& pre_multiply(const OtherMatrix& multiplier) {
        return get_this() = multiplier * get_this();
    }

    template <typename OtherMatrix>
    matrix_type& post_multiply(const OtherMatrix& multiplier) {
        return get_this() = get_this() * multiplier;
    }

    template <typename OtherMatrix>
    matrix_type& operator*=(const OtherMatrix& multiplier) {
        return post_multiply(multiplier);
    }

    template <typename OtherMatrixTraits>
    typename matrix_traits::template multiplication_type<OtherMatrixTraits>::type operator*(
            const matrix_support<OtherMatrixTraits>& multiplier) const {
        BOOST_ASSERT_MSG(cols() == multiplier.cols(), "matricies can't be multiplied");

        typedef typename matrix_traits::template multiplication_type<OtherMatrixTraits>::type result_type;

        result_type result;
        result_type::matrix_traits::resize(result, rows(), multiplier.cols());
        for (size_t i=0; i<result.rows(); i++) {
            for (size_t j=0; j<result.cols(); j++) {
                value_type sum = 0;
                for (size_t k=0; k<cols(); k++) {
                    sum += cell(i, k) * multiplier(k, j);
                }
                result(i,j) = sum;
            }
        }
        return result;
    }

    template <typename OtherMatrixTraits>
    matrix_type& operator=(const matrix_support<OtherMatrixTraits>& copy) {
        MatrixTraits::resize(get_this(), copy.rows(), copy.cols());
        for (size_t i=0; i<std::min(rows(), copy.rows()); i++) {
            for (size_t j=0; j<std::min(cols(), copy.cols()); j++) {
                cell(i,j) = copy(i,j);
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
                    cell(i,j) = *iter;
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
    Result& transform(const Vector& vector, Result& result) const {
        return transform_impl(vector, result);
    }

    template <typename Result, typename Type>
    Result& transform(const std::initializer_list<Type>& vector, Result& result) const {
        return transform_impl(vector, result);
    }

    template <typename Result, typename Vector>
    Result transform(const Vector& vector) const {
        Result result;
        return transform_impl(vector, result);
    }

    template <typename Result, typename Type>
    Result transform(const std::initializer_list<Type>& vector) const {
        Result result;
        return transform_impl(vector, result);
    }

    transform_builder<matrix_type&> build() {
        return transform_builder<matrix_type&>(get_this());
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

    static transform_builder<matrix_type> builder() {
        return transform_builder<matrix_type>(identity());
    }

    static transform_builder<matrix_type&> builder(matrix_type& m) {
        return transform_builder<matrix_type&>(m);
    }

};

template <typename Stream, typename Traits>
Stream& operator<<(Stream& stream, const matrix_support<Traits>& matrix) {
    std::ios::fmtflags f( stream.flags() );

    stream << std::fixed << std::setprecision(8);
    for (size_t i=0; i<matrix.rows(); i++) {
        for (size_t j=0; j<matrix.cols(); j++) {
            if (j > 0) {
                stream << '\t';
            }
            stream << matrix.cell(i, j);
        }
        stream << std::endl;
    }
    stream.flags( f );
    return stream;
}

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

};

template <typename T, size_t Rows, size_t Cols, typename Order>
struct flat_container_matrix_traits {

    enum {
        row_count = Rows,
        col_count = Cols
    };

    typedef T                         value_type;
    typedef matrix<T,Rows,Cols,Order> matrix_type;
    typedef matrix<T,Cols,Rows,Order> transposed_matrix_type;

    template <typename OtherMatrixTraits>
    struct multiplication_type {
        typedef matrix<value_type, row_count, OtherMatrixTraits::col_count> type;
    };

    typedef size_t permutation_matrix_type[Rows];

    static void resize_permutation(permutation_matrix_type& /*permutation*/, size_t size) {
        BOOST_ASSERT_MSG(size == Rows, "Static permutation vector can't be resized");
    }

    static void resize(matrix_type& matrix, size_t rows, size_t cols) {
        BOOST_ASSERT_MSG(matrix.rows() == rows && matrix.cols() == cols, "Static matrix can't be resized");
    }


};

}
}

#pragma once

#include <iomanip>

namespace alterate {

    template <typename Stream, typename Container>
    Stream& print_container(const Container& container, Stream& stream) {
        stream << '[';
        bool needComma = false;
        for (typename Container::const_iterator iter = container.begin(); iter != container.end(); iter++) {
            if (needComma) {
                stream << ", ";
            }
            stream << (*iter);
            needComma = true;
        }
        stream << ']';
        return stream;
    }

    template <typename Stream, typename Matrix>
    Stream& print_matrix(const Matrix& matrix, Stream& stream) {
        for (size_t i=0; i<Matrix::row_count; i++) {
            for (size_t j=0; j<Matrix::col_count; j++) {
                stream << std::fixed << std::setprecision(4) << '[' << matrix.cell(i, j) << ']';
            }
            stream << std::endl;
        }
        return stream;
    }

}

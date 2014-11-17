#pragma once

namespace alterate {
namespace math {

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

template <typename T, size_t Rows, size_t Cols, typename Order = row_major_order>
class matrix {
private:
    T data[Rows*Cols];

public:
    typedef T value_type;
    typedef Order order_type;
    enum {
        row_count = Rows,
        col_count = Cols
    };

    value_type& cell(size_t row, size_t col) {
        return data[order_type::template compute_flat_index<Rows,Cols>(row, col)];
    }

    const value_type& cell(size_t row, size_t col) const {
        return data[order_type::template compute_flat_index<Rows,Cols>(row, col)];
    }

};

// 0 1 2 3 4 5 6 7

// row-major mapping: row * Cols + col
// column-major mapping: col * Rows + row

// plain_index = row * Cols + col .. (1 * 4 + 0) = 4
// row = plain_index % Rows; .. 4 % 2 = 0
// col = plain_index / Rows; .. 4 / 2 = 2

//[0,0] -> [0,0]
//[0,1] -> [1,0]
//[0,2] -> [0,1]
//[0,3] -> [1,1]
//[1,0] -> [0,2]
//[1,1] -> [1,2]
//[1,2] -> [0,3]
//[1,3] -> [1,3]

//row

//1 2 3 4
//5 6 7 8

//1 3 5 7
//2 4 6 8

}
}

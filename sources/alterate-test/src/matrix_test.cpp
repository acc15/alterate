#include <gtest/gtest.h>
#include <alterate/math/matrix.h>
#include <alterate/print.h>

#include <alterate/timing/timer.h>
using alterate::math::matrix;


TEST(matrix_test, performance_2d_vs_1d_access) {

    alterate::timing::timer timer;


    int array1d[1000 *1000];
    int array2d[1000][1000];

    int64_t min_time2d, max_time2d;
    for (size_t c=0; c<10; c++) {
        timer.start();
        for (size_t i=0; i<1000; i++) {
            for (size_t j=0; j<1000; j++) {
                array2d[i][j] = i+j;
            }
        }
        int64_t time2d = timer.get_time_in_nanos();
        if (c == 0) {
            min_time2d = max_time2d = time2d;
        } else if (time2d > max_time2d) {
            max_time2d = time2d;
        } else if (time2d < min_time2d) {
            min_time2d = time2d;
        }
    }


    int64_t min_time1d, max_time1d;
    for (size_t c=0;c<10;c++) {
        timer.start();
        for (size_t i=0; i<1000; i++) {
            for (size_t j=0; j<1000; j++) {
                array1d[i*1000+j] = i+j;
            }
        }
        int64_t time1d = timer.get_time_in_nanos();
        if (c == 0) {
            min_time1d = max_time1d = time1d;
        } else if (time1d > max_time1d) {
            max_time1d = time1d;
        } else if (time1d < min_time1d) {
            min_time1d = time1d;
        }
    }

    array1d[0] = array2d[0][0];
    array2d[0][0] = array1d[0];

    std::cout << "1D time (min:" << min_time1d << ";max:" << max_time1d << ";avg:"<< (max_time1d+min_time1d)/2 << ")" << std::endl
              << "2D time (min:" << min_time2d << ";max:" << max_time2d << ";avg:"<< (max_time2d+min_time2d)/2 << ")" << std::endl;

}

TEST(matrix_test, is_default_constructible) {
    matrix<int, 3, 3> m;
    //m.set_to_identity();
    alterate::print_matrix(m, std::cout);

}



#include <array>

#include <gtest/gtest.h>
#include <alterate/math/matrix.h>
#include <alterate/print.h>

#include <alterate/timing/timer.h>
using alterate::math::matrix_support;

typedef alterate::math::matrix<float, 3, 3> mat3x3;


//template <typename T>
//struct matrix_test : public ::testing::Test {
//    typedef T                           vector_type;
//    typedef typename T::const_iterator  const_iterator;
//    typedef typename T::value_type      value_type;
//};

//TYPED_TEST_CASE_P(generic_vector_support_test);


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

TEST(matrix_test, compute_determinant) {

    alterate::math::matrix<float, 3, 3> mat = {
        0,      23,     43,
        54,     5,      75,
        0,      6,      63
    };
    alterate::print_matrix(mat, std::cout);

    float det1 = mat.compute_determinant();
    std::cout << "Determinant: " << det1 << std::endl;



    alterate::math::matrix<float, 50, 50> mat2 = alterate::math::matrix<float, 50, 50>::identity();


    alterate::print_matrix(mat2, std::cout);

    float det2 = mat2.compute_determinant();
    std::cout << "Determinant: " << det2 << std::endl;

}

TEST(matrix_test, is_default_constructible) {


    mat3x3 mat;
    mat.set_row(0, {9,8,7});
    mat.set_col(0, {9,8,7});
    alterate::print_matrix(mat, std::cout);

    mat3x3 identity = mat3x3::identity();
    std::array<float, 3> row= identity.get_row<std::array<float,3> >(0);
    alterate::print_container(row, std::cout);

    mat3x3 scale = mat3x3::scale({9,8,7});
    mat3x3 translate = mat3x3::translate({7,8,9});
    mat3x3 rotate = mat3x3::rotate_z(M_PI/2);

    mat3x3 multiplied = identity * scale * translate * rotate;

    //mat3x3().identity().translate({4,3}).scale({2,2}).transform()

    //std::array<float, 3> transformed = (mat3x3::translate({2,3,0}) * mat3x3::scale({2,2})).transform< std::array<float,3> >({1,2});
    //std::cout<<"transform: "<<std::endl;
    //alterate::print_container(transformed, std::cout);
    //std::cout << std::endl;


    std::cout<<"identity: "<<std::endl;
    alterate::print_matrix(identity, std::cout);

    std::cout<<"scale: "<<std::endl;
    alterate::print_matrix(scale, std::cout);

    std::cout<<"translate: " <<std::endl;
    alterate::print_matrix(translate, std::cout);

    std::cout<<"rotate: " <<std::endl;
    alterate::print_matrix(rotate, std::cout);

    std::cout<<"scale * translate * rotate: " <<std::endl;
    alterate::print_matrix(multiplied, std::cout);


    mat3x3 m = mat3x3::identity();
    m *= scale;
    m *= translate;
    m *= rotate;

    std::cout<<"scale * translate * rotate: " <<std::endl;
    alterate::print_matrix(m, std::cout);

    std::cout << "det(m) = " << m.compute_determinant() << std::endl;

    alterate::math::matrix<float, 3,2> m3x2;// = m;
    //m3x2 *= m3x2;
    alterate::print_matrix(m3x2, std::cout);


}



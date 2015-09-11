#include <time.h>
#include <array>

#include <gtest/gtest.h>
#include <alterate/math/matrix.h>
#include <alterate/math/vec.h>
#include <alterate/print.h>

#include <alterate/timing/timer.h>

#include "test_utils.h"


using alterate::math::matrix_support;

typedef alterate::math::matrix<float, 3, 3> mat3x3;

template <typename Expected, typename Actual>
void assert_matrix(const Expected& expected, const Actual& actual) {
    for (size_t i=0; i<expected.rows(); i++) {
        for (size_t j=0; j<expected.cols(); j++) {
            ASSERT_EQ(expected(i,j), actual(i,j)) <<
                "Elements at [" << i << "][" << j << "] differs. Expected: " << expected(i,j) << ", but was: " << actual(i,j);
        }
    }
}

template <typename T, size_t N>
size_t array_length(const T (&)[N]) { return N; }

TEST(matrix_test, assign_vector_test) {

    float vec[] = {3,5,7,4,6,8,1,2,3};
    mat3x3 m = vec;
    alterate::test::assert_has_equal_elements<float*, float*>(m.data, m.data + array_length(vec), vec, vec+ array_length(vec));

}

TEST(matrix_test, assign_matrix_test) {
    mat3x3 m = {3,5,7,4,6,8,1,2,3};

    alterate::math::matrix<float, 3,3, alterate::math::column_major_order> a;
    a = m;
    assert_matrix(m, a);
}

TEST(matrix_test, swap_row) {
    mat3x3 m = {3,5,7,4,6,8,1,2,3};

    m.swap_row(0,2);

    mat3x3 e = {1,2,3,4,6,8,3,5,7};
    assert_matrix(e, m);
}

TEST(matrix_test, swap_col) {
    mat3x3 m = {3,5,7,
                4,6,8,
                1,2,3};

    m.swap_col(0,2);

    mat3x3 e = {7,5,3,
                8,6,4,
                3,2,1};
    assert_matrix(e, m);
}

TEST(matrix_test, transpose) {
    mat3x3 m = {3,5,7,
                4,6,8,
                1,2,3};
    m.transpose();

    mat3x3 e = {3,4,1,
                5,6,2,
                7,8,3};
    assert_matrix(e, m);
}

TEST(matrix_test, get_transposed) {
    alterate::math::matrix<float, 2,3> m = {1,2,3,
                                            4,5,6};
    alterate::math::matrix<float, 3,2> t = m.compute_transposed();
    alterate::math::matrix<float, 3,2> e = {1,4,
                                            2,5,
                                            3,6};
    assert_matrix(e, t);

}

TEST(matrix_test, multiply) {

    mat3x3 m1 ={1,2,3,
                4,5,6,
                7,8,9};

    mat3x3 m2 = {9,8,7,
                 6,5,4,
                 3,2,1};

    m1.post_multiply(m2);

    mat3x3 e = { 30, 24, 18,
                 84, 69, 54,
                 138,114,90 };
    assert_matrix(e,m1);
}


TEST(matrix_test, compute_determinant) {

    mat3x3 m1 ={0,2,3,
                4,5,6,
                7,8,9};
    EXPECT_EQ(3, m1.compute_determinant());

    mat3x3 m2 ={
        60,	4,  83,
        75,	5,  60,
        48,	40,	35
    };
    EXPECT_EQ(96600, m2.compute_determinant());
}


template <typename M, typename P>
void split_lu(const M& lu, const P& p, M& l, M& u) {
    for (size_t i=0; i<l.rows(); i++) {
        for (size_t j=0; j<l.cols(); j++) {
            l(i,j) = (j<i) ? lu(i,p[j]) : (i==j) ? 1 : 0;
            u(i,j) = (j>=i) ? lu(i,p[j]) : 0;
        }
    }
}

template <typename P, typename M>
void make_permutation_matrix(const P& p, M& l) {
    for (size_t i=0; i<l.rows(); i++) {
        for (size_t j=0; j<l.cols(); j++) {
            l(i,j) = (i == p[j]) ? 1 : 0;
        }
    }
}

void test_invert(size_t iter, const mat3x3& m) {

    mat3x3 inv;
    if (!m.compute_inverse(inv)) {
        std::cout << "Not invertible!!!" << std::endl;
        return;
    }

    mat3x3 mul = m * inv;
    //std::cout << mul << std::endl;

    for (size_t i=0; i<mul.rows(); i++) {
        for (size_t j=0; j<mul.cols(); j++) {
            ASSERT_NEAR(mul(i,j), i == j ? 1 : 0, 0.01f) <<
                "[" << iter << "] M*inv(M)[" << i << "][" << j << "] is not equal to identity. " <<
                "M: " << std::endl << m <<
                "inv(M): " << std::endl << inv <<
                "M*inv(M): " << std::endl << mul;
        }
    }


}

TEST(matrix_test, compute_inverse) {

    test_invert(0, {
            60.00000000,	4.00000000,     83.00000000,
            75.00000000,	5.00000000,     60.00000000,
            48.00000000,	40.00000000,	35.00000000,
            });

    test_invert(1, {
                    23.00000000,	82.00000000,	41.00000000,
                    99.00000000,	15.00000000,	26.00000000,
                    81.00000000,	97.00000000,	59.00000000
                });

    test_invert(2, {
                    72.00000000,	54.00000000,	71.00000000,
                    84.00000000,	63.00000000,	4.00000000,
                    26.00000000,	45.00000000,	26.00000000
                });
    /*

13.00000000	61.00000000	95.00000000
26.00000000	37.00000000	33.00000000
56.00000000	71.00000000	55.00000000

60.00000000	4.00000000	83.00000000
75.00000000	5.00000000	60.00000000
48.00000000	40.00000000	35.00000000

69.00000000	78.00000000	43.00000000
58.00000000	64.00000000	47.00000000
23.00000000	20.00000000	56.00000000

48.00000000	62.00000000	58.00000000
74.00000000	20.00000000	61.00000000
38.00000000	28.00000000	38.00000000
*/

//    mat3x3 m;
//  this will cause test instability
//    srand( time(nullptr) );
//    for (size_t iter=0; iter < 1000; iter++) {
//        for (size_t i=0;i<m.rows(); i++) {
//            for (size_t j=0;j<m.cols(); j++) {
//                m(i,j) = static_cast<float>(rand() % 10000) / 100.f;
//            }
//        }
//        test_invert(iter, m);
//    }

}

TEST(matrix_test, transform) {

    mat3x3 m = mat3x3().build().
            scale({1024.f/2, -768.f/2}).
            translate({512.f, 384.f}).
            local_to_world();


    alterate::math::vec<float, 2> v;
    m.transform({1, 1}, v);

    alterate::test::assert_has_equal_elements({1024.f,0.f}, v);

    m.invert();

    m.transform({1024.f,768.f}, v);
    alterate::test::assert_has_equal_elements({1.f,-1.f}, v);

}

TEST(matrix_test, compute_lup_decomposition) {

    mat3x3 m = {
        60,	4,  83,
        75,	5,  60,
        48,	40,	35
    };

    mat3x3 lu;
    size_t p[3];
    EXPECT_TRUE(m.compute_lu_decomposition(lu, p));

    mat3x3 l,u,mp;
    split_lu(lu,p, l,u);

    make_permutation_matrix(p,mp);

    std::cout << "L: " << std::endl;
    alterate::print_matrix(l, std::cout);

    std::cout << "U: " << std::endl;
    alterate::print_matrix(u, std::cout);

    std::cout << "P: " << std::endl;
    alterate::print_matrix(mp, std::cout);

    mat3x3 lu_m = l * u * mp;
    std::cout << "LUP: " << std::endl;
    alterate::print_matrix(lu_m, std::cout);

    assert_matrix(m, lu_m);

}


//#include <boost/numeric/ublas/matrix.hpp>
//#include <boost/numeric/ublas/lu.hpp>
//#include <boost/numeric/ublas/io.hpp>

//using namespace boost::numeric::ublas;
//using namespace std;

// /* Matrix inversion routine.
// Uses lu_factorize and lu_substitute in uBLAS to invert a matrix */
//template<class T>
//bool InvertMatrix(matrix<T>& input)
//{
//    typedef permutation_matrix<std::size_t> pmatrix;

//    // create a working copy of the input
//    matrix<T> A(input);

//    // create a permutation matrix for the LU-factorization
//    pmatrix pm(A.size1());

//    // perform LU-factorization
//    int res = lu_factorize(A, pm);
//    if (res != 0)
//        return false;

//    // create identity matrix of "inverse"
//    input.assign(identity_matrix<T> (A.size1()));

//    // backsubstitute to get the inverse
//    lu_substitute(A, pm, input);

//    return true;
//}


//TEST(matrix_test, invert_performance) {

//    typedef alterate::math::matrix<float, 4, 4> mat4x4;

//    alterate::timing::timer timer;

//    srand( time(nullptr) );

//    const size_t m_count = 2000;

//    mat4x4 m;
//    for (size_t i=0;i<m.rows(); i++) {
//        for (size_t j=0;j<m.cols(); j++) {
//            m(i,j) = static_cast<float>(rand() % 10000) / 100.f;
//        }
//    }

//    timer.start();
//    for (size_t t=0; t<m_count; t++) {
//        m.invert();
//    }
//    int64_t alt_nanos = timer.get_time_in_nanos();

//    matrix<float> boost_m(4,4);
//    for (size_t i=0;i<m.rows(); i++) {
//        for (size_t j=0;j<m.cols(); j++) {
//            boost_m(i,j) = static_cast<float>(rand() % 10000) / 100.f;
//        }
//    }

//    timer.start();
//    for (size_t t=0; t<m_count; t++) {
//        InvertMatrix(boost_m);
//    }
//    int64_t boost_nanos = timer.get_time_in_nanos();

//    std::cout << m_count << " matrix inversions took (alt: " << alt_nanos << ", boost: " << boost_nanos << ")" << std::endl;
//}

TEST(matrix_test, multiply_performance) {

    mat3x3 m1, m2;

    for (size_t i=0; i<m1.rows(); i++) {
        for (size_t j=0; j<m1.cols(); j++) {
            m1(i,j) = (rand() % 10000) / 100.f - 50.f;
            m2(i,j) = (rand() % 10000) / 100.f - 50.f;
        }
    }

    alterate::timing::timer<int64_t> timer;

    timer.start();
    for (size_t i=0; i<50000; i++) {
        m1 *= m2;// * m1;
        m2 *= m1;// * m2;
    }
    int64_t t = timer.elapsed<boost::nano>();


    std::cout << "100k multiplications took: " << t << "ns" << std::endl;


}

TEST(matrix_test, performance_2d_vs_1d_access) {

    alterate::timing::timer<int64_t> timer;

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
        int64_t time2d = timer.elapsed<boost::nano>();
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
        int64_t time1d = timer.elapsed<boost::nano>();
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



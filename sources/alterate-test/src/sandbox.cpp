#include <gtest/gtest.h>

#include <iostream>
#include <iomanip>

// C++ matrix inversion (boost::ublas)
// Another recurrent question is “how do I invert a matrix in [my library of choice]?”. Neither boost::ublas nor MTL documentation answers this satisfactorily.
// If you’re using boost::ublas, you can find the InvertMatrix funcion here: http://www.crystalclearsoftware.com/cgi-bin/boost_wiki/wiki.pl?LU_Matrix_Inversion
// And a simple example below:

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace boost::numeric::ublas;
using namespace std;

 /* Matrix inversion routine.
 Uses lu_factorize and lu_substitute in uBLAS to invert a matrix */
template<class T>
bool InvertMatrix(const matrix<T>& input, matrix<T>& inverse)
{
    typedef permutation_matrix<std::size_t> pmatrix;

    // create a working copy of the input
    matrix<T> A(input);

    // create a permutation matrix for the LU-factorization
    pmatrix pm(A.size1());

    // perform LU-factorization
    int res = lu_factorize(A, pm);
    if (res != 0)
        return false;

    // create identity matrix of "inverse"
    inverse.assign(identity_matrix<T> (A.size1()));

    // backsubstitute to get the inverse
    lu_substitute(A, pm, inverse);

    return true;
}

TEST(sandbox, ublas_inverse) {

    cout << fixed << setprecision(8);

//    float mv[3][3] = {
//                60.00000000,	4.00000000,     83.00000000,
//                75.00000000,	5.00000000,     60.00000000,
//                48.00000000,	40.00000000,	35.00000000,
//                };


//    matrix<float> mat(3,3);

//    matrix<float> inv(3,3);
//    for (size_t i=0; i<3; i++) {
//        for (size_t j=0; j<3;j++) {
//            mat(i,j) = mv[i][j];
//        }
//    }

//    InvertMatrix(mat,inv);


    srand( time(nullptr) );
    for (size_t t=0; t<10000; t++) {


        matrix<float> mat(3,3);

        for (size_t i=0;i<3; i++) {
            for (size_t j=0;j<3; j++) {
                mat(i,j) = static_cast<float>(rand() % 10000) / 100.f;
            }
        }

        matrix<float> inv(3,3);
        InvertMatrix(mat, inv);

        matrix<float> ide(3,3);
        ide = prod(mat, inv);


        for (size_t i=0; i<3; i++) {
            for (size_t j=0; j<3; j++) {
                ASSERT_NEAR(i==j?1:0,ide(i,j),0.01f) << "At " << i << "," << j;
                cout << ide(i,j) << "    ";
            }
            cout << endl;
        }

        cout<<"test"<<endl;
    }
}

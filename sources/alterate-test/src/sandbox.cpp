#include <gtest/gtest.h>

#include <iostream>
#include <iomanip>

#include <vector>
#include <list>

#include <alterate/timing/timer.h>
#include <alterate/math/vec.h>

#include <memory>

template <typename T>
class id_generator {
private:

    std::vector<T> _free_list;
    T _current;

public:
    id_generator(const T& initial = T()) : _current(initial) {}

    void release(const T& id) {
        if (id < _current) {
            _free_list.push_back(id);
        }
    }

    T generate() {
        if (_free_list.empty()) {
            return ++_current;
        }
        T id = _free_list.back();
        _free_list.pop_back();
        return id;
    }

};


template <typename T, size_t ChunkSize = 512, typename Allocator = std::allocator<T> >
class object_pool {

    //
    //  0        1        2        3        4        5        6        7
    //  entity0  null     null     null     entity4  null     null     null

private:
    std::vector<T*> _chunks;
    Allocator       _allocator;

public:
    T* get(size_t index) {
        return _chunks[index / ChunkSize][index % ChunkSize];
    }

    void put(size_t index) {

        size_t chunk_index = index/ChunkSize;
        if (_chunks.size() <= chunk_index) {
            _chunks.resize(chunk_index+1, nullptr);
        }
        if (_chunks[chunk_index] == nullptr) {
            _chunks[chunk_index] = _allocator.allocate(ChunkSize);
        }

    }

    void put(size_t index, const T& initial_value) {

    }



};

//struct test_struct {

//    static int init_count;

//    test_struct() {
//        std::cout << "In ctor" << std::endl;
//        ++init_count;
//    }

//    ~test_struct() {
//        --init_count;
//        std::cout << "In dector" << std::endl;
//    }

//    int a,b,c,d,e,f;

//};

//int test_struct::init_count = 0;

//TEST(sandbox, allocator_test) {

//    std::allocator<test_struct> a;

//    test_struct* p = a.allocate(512);

//    std::cout << "init count " << test_struct::init_count << std::endl;
//    for (size_t i=0; i<5; i++) {
//        a.construct(p+i);
//    }
//    std::cout << "init count " << test_struct::init_count << std::endl;
//    for (size_t i=0; i<5; i++) {
//        a.destroy(p+i);
//    }
//    std::cout << "init count " << test_struct::init_count << std::endl;
//    a.deallocate(p, 512);
//}


//TEST(sandbox, timer_test) {

//    alterate::timing::timer<double> t;

//    t.start();

//    int x;
//    for (size_t i=0; i<1; i++) {
//    }

//    double elapsed = t.elapsed();
//    std::cout << "eee: " << std::setprecision(10) << std::fixed << elapsed;

//}
//
//              component1    component2
// entity 1 ----|-----------------> (not cache-friendly)
// entity 2     |
// entity 3     v


// component flags...
//
//  0        1        2        3
//  a|b|c    c        b|c      a

// component pools...
//
//
//


//  component pool
//  0        1        2        3        4        5        6        7
//  entity0  null     null     null     entity4  null     null     null

// get all components by entity id
// get all components by tag

// 1. each entity maintain own list of component pointers
// entity0
// std::vector<index in pool> _components;
// to get specific entity component: _component_pool[component::tag()][_components[component::tag()]]
//
// to get entities having two or more components
//
// to iterate over entity components
//  O(1)
//
// to iterate over ALL components of specific type.
//
// if single object will have very specific component then it's O(N) where N is total amount of entities
// component vector
//  0        1        2        3        4        5        6        7
//  e0       e4       null     e3       null     null     null     null
//
// free_list contains indexes of free slots
//

//struct node {
//    size_t next_index;
//    bool valid;
//    int a,b,c,d,e;
//};


// Run this in RELEASE mode. Direct mode will sum almost instantly (68 ns vs 221280 ns for Skip)
//TEST(sandbox, init) {

//    srand(time(nullptr));


//    //
//    //  0        1        2        3        4        5        6        7
//    //  entity0  null     null     null     entity4  null     null     null
//    //      |  <-    ----------------------->
//    //      \------------------------------->
//    size_t next_valid = 0;

//    std::vector<node> skip_vec(10240);
//    for (size_t i=0; i<skip_vec.size(); i++) {
//        skip_vec[i].a = i+2;
//        skip_vec[i].b = i+1;
//        skip_vec[i].c = i;
//        skip_vec[i].d = i-1;
//        skip_vec[i].e = i-2;
//        if (i == next_valid) {
//            skip_vec[i].valid = true;
//            next_valid = i + (rand() % 10) + 1;
//        } else {
//            skip_vec[i].valid = false;
//        }
//        skip_vec[i].next_index = next_valid;
//    }

//    alterate::timing::timer<float> timer;


//    size_t p = 0;
//    int sum = 0;

//    timer.start();
//    while (p < skip_vec.size()) {
//        node& n = skip_vec[p];
//        sum += n.a + n.b + n.c + n.d + n.e;
//        p = n.next_index;
//    }
//    float skip_time = timer.elapsed();

//    std::vector<node> full_vec(10240);
//    for (size_t i=0; i<full_vec.size(); i++) {
//        skip_vec[i].a = i+2;
//        skip_vec[i].b = i+1;
//        skip_vec[i].c = i;
//        skip_vec[i].d = i-1;
//        skip_vec[i].e = i-2;
//        if (i == next_valid) {
//            skip_vec[i].valid = true;
//            next_valid = (i + (rand() % 10) + 1);
//        } else {
//            skip_vec[i].valid = false;
//        }
//    }

//    int sum2 = 0;
//    timer.start();
//    for (auto iter = skip_vec.begin(); iter != skip_vec.end(); iter++) {
//        node& n = *iter;
//        if (!n.valid) {
//            continue;
//        }
//        sum2 += n.a + n.b + n.c + n.d + n.e;
//    }
//    float direct_time = timer.elapsed();



//    std::list<node> linked_list;
//    for (size_t i=0; i<10240; i++) {

//        node n;
//        n.a = i+2;
//        n.b = i+1;
//        n.c = i;
//        n.d = i-1;
//        n.e = i-2;
//        if (i == next_valid) {
//            n.valid = true;
//            next_valid = (i + (rand() % 10) + 1);
//        } else {
//            n.valid = false;
//        }
//        linked_list.push_back(n);

//    }



//    int sum3 = 0;
//    timer.start();
//    for (auto iter = linked_list.begin(); iter != linked_list.end(); iter++) {
//        node& n = *iter;
//        if (!n.valid) {
//            continue;
//        }
//        sum3 += n.a + n.b + n.c + n.d + n.e;
//    }
//    float linked_time = timer.elapsed();

//    std::cout << "Skip: " << skip_time << std::endl <<
//                 "Direct: " << direct_time << std::endl <<
//                 "Linked: " << linked_time << std::endl;

//}



// C++ matrix inversion (boost::ublas)
// Another recurrent question is “how do I invert a matrix in [my library of choice]?”. Neither boost::ublas nor MTL documentation answers this satisfactorily.
// If you’re using boost::ublas, you can find the InvertMatrix funcion here: http://www.crystalclearsoftware.com/cgi-bin/boost_wiki/wiki.pl?LU_Matrix_Inversion
// And a simple example below:

//#include <boost/numeric/ublas/matrix.hpp>
//#include <boost/numeric/ublas/lu.hpp>
//#include <boost/numeric/ublas/io.hpp>

//using namespace boost::numeric::ublas;
//using namespace std;

// /* Matrix inversion routine.
// Uses lu_factorize and lu_substitute in uBLAS to invert a matrix */
//template<class T>
//bool InvertMatrix(const matrix<T>& input, matrix<T>& inverse)
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
//    inverse.assign(identity_matrix<T> (A.size1()));

//    // backsubstitute to get the inverse
//    lu_substitute(A, pm, inverse);

//    return true;
//}

//TEST(sandbox, ublas_inverse) {

//    cout << fixed << setprecision(8);

////    float mv[3][3] = {
////                60.00000000,	4.00000000,     83.00000000,
////                75.00000000,	5.00000000,     60.00000000,
////                48.00000000,	40.00000000,	35.00000000,
////                };


////    matrix<float> mat(3,3);

////    matrix<float> inv(3,3);
////    for (size_t i=0; i<3; i++) {
////        for (size_t j=0; j<3;j++) {
////            mat(i,j) = mv[i][j];
////        }
////    }

////    InvertMatrix(mat,inv);


//    srand( time(nullptr) );
//    for (size_t t=0; t<10000; t++) {


//        matrix<float> mat(3,3);

//        for (size_t i=0;i<3; i++) {
//            for (size_t j=0;j<3; j++) {
//                mat(i,j) = static_cast<float>(rand() % 10000) / 100.f;
//            }
//        }

//        matrix<float> inv(3,3);
//        InvertMatrix(mat, inv);

//        matrix<float> ide(3,3);
//        ide = prod(mat, inv);


//        for (size_t i=0; i<3; i++) {
//            for (size_t j=0; j<3; j++) {
//                ASSERT_NEAR(i==j?1:0,ide(i,j),0.01f) << "At " << i << "," << j;
//                cout << ide(i,j) << "    ";
//            }
//            cout << endl;
//        }

//        cout<<"test"<<endl;
//    }
//}

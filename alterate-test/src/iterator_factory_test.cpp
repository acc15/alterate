#include <algorithm>

#include <alterate/iterator/iterator_factory.h>
#include <boost/predef.h>
#include "test_utils.h"


#if BOOST_COMP_MSVC

#include <iterator>

template <typename PointerType>
stdext::checked_array_iterator<PointerType> make_checked_iterator(const PointerType& ptr, size_t size) {
    return stdext::checked_array_iterator<PointerType>(ptr, static_cast<std::size_t>(size));
}

#else

template <typename PointerType>
PointerType make_checked_iterator(const PointerType& ptr, size_t /*size*/) {
    return ptr;
}

#endif


using namespace alterate::test;

struct vector_data_set_1 : std::vector<int> {
    vector_data_set_1() : std::vector<int>({ 1, 2, 3 }) {
    }
};

struct vector_data_set_2 : std::vector<int> {
    vector_data_set_2() : std::vector<int>({ 1, 1, 1 }) {
    }
};

template <typename Container, typename DataSet>
struct typed_test_case {

    typedef Container                               container_type;
    typedef DataSet                                 dataset_type;
    typedef typename dataset_type::value_type       dataset_value_type;
    typedef typename dataset_type::size_type        size_type;
    typedef typename dataset_type::const_iterator   dataset_iterator;

    container_type      container;
    dataset_type        dataset;

};

template <typename ContainerType, typename DataSetType>
struct container_test_case : typed_test_case < ContainerType, DataSetType > {

    typedef typed_test_case<ContainerType, DataSetType> test;
    using test::dataset;
    using test::container;

    container_test_case() {
        std::transform(dataset.begin(), dataset.end(),
            std::back_insert_iterator<ContainerType>(container), static_cast_fn<typename ContainerType::value_type>());
    }
};

template <typename ScalarType, typename DataSetType>
struct scalar_test_case : typed_test_case < ScalarType, DataSetType > {

    typedef typed_test_case<ScalarType, DataSetType> test;
    using test::dataset;
    using test::container;

    scalar_test_case() {
        container = static_cast<ScalarType>(dataset.front());
    }
};

template <typename PointerType, typename DataSetType>
struct pointer_test_case : typed_test_case < PointerType, DataSetType > {

    typedef typed_test_case<PointerType, DataSetType> test;
    using test::dataset;
    using test::container;

    typedef typename std::remove_cv<typename std::remove_pointer<PointerType>::type>::type value_type;

    pointer_test_case() {
        container = new value_type[dataset.size()];
        std::transform(dataset.begin(), dataset.end(), make_checked_iterator(container, dataset.size()), static_cast_fn<value_type>());
    }

    ~pointer_test_case() {
        delete [] container;
        container = nullptr;
    }
};

template <typename ArrayType, typename DataSetType>
struct array_test_case : typed_test_case < ArrayType, DataSetType > {

    typedef typed_test_case<ArrayType, DataSetType> test;
    using test::dataset;
    using test::container;

    typedef typename std::remove_extent<ArrayType>::type value_type;
    array_test_case() {
        std::transform(dataset.begin(), dataset.end(), container, static_cast_fn<value_type>());
    }
};

template <typename T>
struct iterator_provider_test : public testing::Test {
    T test_case;
};

typedef ::testing::Types<
    container_test_case< std::vector<float>, vector_data_set_1>
  , scalar_test_case< double, vector_data_set_2>
  , array_test_case< int[3], vector_data_set_1 >
  , pointer_test_case< int*, vector_data_set_1 >
> iterator_provider_test_types;

TYPED_TEST_CASE(iterator_provider_test, iterator_provider_test_types);
TYPED_TEST(iterator_provider_test, check_iterators) {

    typedef typename TypeParam::container_type                                 container_type;
    typedef alterate::iterator::iterator_factory<container_type>               iterator_factory;

    assert_has_equal_elements(this->test_case.dataset.begin(), this->test_case.dataset.end(),
        iterator_factory::begin(this->test_case.container),
        iterator_factory::end(this->test_case.container, this->test_case.dataset.size()));
}

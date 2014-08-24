#include "pch.h"

#include <alterate/iterator/iterator_provider.h>
#include <alterate/platform.h>
#include "../../test_utils.h"


#if defined(_MSC_VER) && !defined(ALTERATE_RELEASE)

#include <iterator>

template <typename PointerType, typename SizeType>
stdext::checked_array_iterator<PointerType> make_checked_iterator(PointerType const& ptr, SizeType const& size) {
    return stdext::checked_array_iterator<PointerType>(ptr, static_cast<std::size_t>(size));
}

#else 

#if defined(_MSG_VER)
#   define _SCL_SECURE_NO_WARNINGS
#endif

template <typename PointerType, typename SizeType>
PointerType make_checked_iterator(PointerType const& ptr, SizeType const& size) {
    return ptr;
}

#endif


namespace {

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

    template <typename To>
    struct static_cast_fn {
        
        template <typename From>
        To operator()(From const& from) const {
            return static_cast<To>(from);
        }

        template <typename From>
        To operator()(From& from) const {
            return static_cast<To>(from);
        }

    };

    template <typename ContainerType, typename DataSetType>
    struct container_test_case : typed_test_case < ContainerType, DataSetType > {
        
        typedef typename container_type::value_type value_type;

        container_test_case() {
            std::transform(dataset.begin(), dataset.end(), 
                std::back_insert_iterator<container_type>(container), static_cast_fn<value_type>());
        }
    };

    template <typename ScalarType, typename DataSetType>
    struct scalar_test_case : typed_test_case < ScalarType, DataSetType > {
        scalar_test_case() {
            container = static_cast<container_type>(dataset.front());
        }
    };

    template <typename PointerType, typename DataSetType>
    struct pointer_test_case : typed_test_case < PointerType, DataSetType > {
        
        typedef typename std::remove_cv<typename std::remove_pointer<container_type>::type>::type value_type;

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

        typedef typename TypeParam::container_type                                  container_type;
        typedef typename TypeParam::size_type                                       size_type;
        typedef alterate::iterable::iterator_provider<container_type, size_type>    iterator_provider;
        typedef iterator_provider::iterator                                         iterator;

        assert_equals(this->test_case.dataset.begin(), this->test_case.dataset.end(), 
            iterator_provider::begin(this->test_case.container), 
            iterator_provider::end(this->test_case.container, this->test_case.dataset.size()));
    }

}
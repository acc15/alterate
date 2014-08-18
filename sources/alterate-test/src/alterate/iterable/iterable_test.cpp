#include "pch.h"

#include <alterate/iterable/iterable.h>
#include "../../test_utils.h"

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

        typedef Container                           container_type;
        typedef DataSet                             dataset_type;
        typedef typename dataset_type::value_type   dataset_value_type;

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

    template <typename Container, typename DataSet>
    struct container_test_case : typed_test_case < Container, DataSet > {
        
        typedef typename container_type::value_type value_type;

        container_test_case() {
            std::transform(dataset.cbegin(), dataset.cend(), std::back_insert_iterator<Container>(container), static_cast_fn<value_type>());
        }
    };

    template <typename Scalar, typename DataSet>
    struct scalar_test_case : typed_test_case < Scalar, DataSet > {
        scalar_test_case() {
            container = static_cast<container_type>(dataset.front());
        }
    };

    template <typename T>
    struct iterable_test : public testing::Test {
        T test_case;
    };
    
    typedef ::testing::Types<
        container_test_case< std::vector<float>, vector_data_set_1>
        //,scalar_test_case< double, vector_data_set_2>
    > iterable_test_types;

    TYPED_TEST_CASE(iterable_test, iterable_test_types);
    TYPED_TEST(iterable_test, make_iterable) {

        typedef alterate::iterable::iterable_traits< TypeParam::container_type > iterable;

        typedef iterable::provider_type     provider_type;
        typedef iterable::return_type       return_type;
        typedef iterable::const_iterator    const_iterator;

        return_type iterable_value = alterate::iterable::make_iterable(this->test_case.container, this->test_case.dataset.size());
        assert_equals(this->test_case.dataset.cbegin(), this->test_case.dataset.cend(), iterable_value.cbegin(), iterable_value.cend());
    }

}
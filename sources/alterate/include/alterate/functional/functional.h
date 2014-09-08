#pragma once

#include <iterator>

namespace alterate {
    namespace functional {

        template <typename InputIterator1, typename InputIterator2, typename OutputIterator, typename Function>
        void transform_safe(InputIterator1 in_begin1, InputIterator1 in_end1,
            InputIterator2 in_begin2, InputIterator2 in_end2,
            OutputIterator out_begin, Function func) {

            typedef std::iterator_traits<InputIterator1> it1_traits;
            typedef typename it1_traits::value_type it1_value_type;

            typedef std::iterator_traits<OutputIterator> out_traits;
            typedef typename out_traits::value_type out_value_type;

            for (; in_begin1 != in_end1 && in_begin2 != in_end2; in_begin1++, in_begin2++, out_begin++) {
                *out_begin = static_cast<out_value_type>(
                    func(*in_begin1, static_cast<it1_value_type>(*in_begin2)));
            }
        }

        template <typename Result, typename InputIterator1, typename InputIterator2, typename Function>
        Result accumulate_safe(InputIterator1 in_begin1, InputIterator1 in_end1, 
                               InputIterator2 in_begin2, InputIterator2 in_end2, 
                               const Function& func, Result init) {

            typedef std::iterator_traits<InputIterator1> it1_traits;
            typedef typename it1_traits::value_type it1_value_type;

            for (; in_begin1 != in_end1 && in_begin2 != in_end2; in_begin1++, in_begin2++) {
                init += static_cast<Result>(func(*in_begin1, static_cast<it1_value_type>(*in_begin2)));
            }
            return init;
        }

    }
}
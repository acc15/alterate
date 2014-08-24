#pragma once

namespace alterate {
    namespace functional {

        template <typename InputIterator1, typename InputIterator2, typename OutputIterator, typename Function>
        void transform_safe(InputIterator1 in_begin1, InputIterator1 in_end1,
            InputIterator2 in_begin2, InputIterator2 in_end2,
            OutputIterator out_begin, Function func) {
            for (; in_begin1 != in_end1 && in_begin2 != in_end2; in_begin1++, in_begin2++, out_begin++) {
                *out_begin = func(*in_begin1, *in_begin2);
            }
        }

        template <typename Result, typename InputIterator1, typename InputIterator2, typename Function>
        Result accumulate_safe(InputIterator1 in_begin1, InputIterator1 in_end1, 
                               InputIterator2 in_begin2, InputIterator2 in_end2, 
                               const Function& func, Result init) {
            for (; in_begin1 != in_end1 && in_begin2 != in_end2; in_begin1++, in_begin2++) {
                init += func(*in_begin1, *in_begin2);
            }
            return init;
        }

    }
}
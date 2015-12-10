#pragma once

namespace alterate {

template <typename TInIter, typename TOutIter>
TOutIter copy_min(TInIter input_begin, TInIter input_end,
			  TOutIter output_begin, TOutIter output_end) {
	for (;input_begin != input_end && output_begin != output_end;
		input_begin++, output_begin++) {
		*output_begin = *input_begin;
	}
	return output_begin;
}


}
#pragma once

#include <iterator>

namespace alterate {

template <typename InIter, typename OutIter>
OutIter copy_safe(InIter in_begin, InIter in_end, OutIter out_begin, OutIter out_end) {
	typedef typename std::iterator_traits<OutIter>::value_type out_type;
	for (; in_begin != in_end && out_begin != out_end; in_begin++, out_begin++) {
		*out_begin = static_cast<out_type>(*in_begin);
	}
	return out_begin;
}

template <typename InIter, typename OutIter, typename BinOp>
OutIter transform_safe(InIter in_begin, InIter in_end, OutIter out_begin, OutIter out_end, BinOp bin_op) {
	typedef typename std::iterator_traits<InIter>::value_type in_type;
	typedef typename std::iterator_traits<OutIter>::value_type out_type;
	for (; in_begin != in_end && out_begin != out_end; in_begin++, out_begin++) {
		*out_begin = static_cast<out_type>( bin_op(*in_begin, static_cast<in_type>( *out_begin )) );
	}
	return out_begin;
}



}
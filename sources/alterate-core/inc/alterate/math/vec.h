#include <array>

#include <alterate/math/basic_vec.h>

namespace alterate {
namespace math {

template <size_t Count, typename T>
class vec: public basic_vec< vec<Count,T>, std::array<T, Count> > {
public:

    typedef basic_vec< vec<Count,T>, std::array<T,Count> >   basic_vec_type;

    vec() : basic_vec_type() {
    }

    template <typename U>
    vec(const U& p) : basic_vec_type(p) {
    }

    template <typename U>
    vec(std::initializer_list<U> const& l) : basic_vec_type(l) {
    }



};

}
}

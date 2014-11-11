#include <array>

#include <alterate/math/basic_vec.h>

namespace alterate {
namespace math {

template <size_t Count, typename T>
class vec: public std::array<T, Count>, public basic_vec< vec<Count,T> > {
public:

    typedef std::array<T,Count> array_type;

    vec(): array_type() {
    }

    template <typename U>
    vec(const U& p) {
    }



};

}
}

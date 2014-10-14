#include <alterate/resource.h>

namespace alterate {

const ubyte_t* resource::begin() const {
    return &_start;
}

const ubyte_t* resource::end() const {
    return &_end;
}

size_t resource::size() const {
    return _size;
}

resource::resource(const ubyte_t& start, const ubyte_t& end, const size_t& size) : _start(start), _end(end), _size(size) {}

size_t get_resource_size(const resource& resource) {
    return resource.size();
}

std::string load_string(const resource& resource) {
    return std::string(resource.begin(), resource.end());
}


}


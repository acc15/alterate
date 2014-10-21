#include <alterate/resource.h>

namespace alterate {
namespace resource {

#ifdef ALTERATE_WINDOWS

    const UINT& resource::id() const {
        return _id;
    }

    resource::resource(const UINT& id) : _id(id) {}

#else 

    const byte_t* locator::begin() const {
        return &_start;
    }

    const byte_t* locator::end() const {
        return &_end;
    }

    size_t locator::size() const {
        return _size;
    }

    locator::locator(const byte_t& start, const byte_t& end, const size_t& size) : _start(start), _end(end), _size(size) {}

    size_t get_resource_size(const locator& resource) {
        return resource.size();
    }

    std::string load_string(const locator& resource) {
        return std::string(resource.begin(), resource.end());
    }

#endif

bundle load_bundle(const locator& resource) {
    std::string value = load_string(resource);
    return bundle::parse_json_string(value);
}


}
}

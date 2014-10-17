#pragma once

#include <string>

#include <alterate/types.h>
#include <alterate/bundle.h>

namespace alterate {

    class resource {
    private:
        const ubyte_t&  _start;
        const ubyte_t&  _end;
        const size_t&   _size;

    public:
        const ubyte_t* begin() const;
        const ubyte_t* end() const;
        size_t size() const;
        resource(const ubyte_t& start, const ubyte_t& end, const size_t& size);
    };

    //std::istream load_stream(const resource& resource);
    bundle      load_bundle(const resource& resource);
    std::string load_string(const resource& resource);
    size_t      get_resource_size(const resource& resource);

}

#pragma once

#include <string>

#include <alterate/types.h>
#include <alterate/bundle.h>

namespace alterate {

#ifdef ALTERATE_WINDOWS

    class resource {
    private:
        const uint_t _id;

    public:
        const uint_t& id() const;
        resource(const uint_t& id);
    };

#else 


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

#endif


    //std::istream load_stream(const resource& resource);
    bundle      load_bundle(const resource& resource);
    std::string load_string(const resource& resource);
    size_t      get_resource_size(const resource& resource);

}

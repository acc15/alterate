#pragma once

#include <string>

#include <alterate/types.h>
#include <alterate/bundle.h>

#ifdef ALTERATE_WINDOWS
#   include <windows.h>
#endif

namespace alterate {
namespace resource {

#ifdef ALTERATE_WINDOWS

    class locator {
    public:
        const UINT& id() const;
        locator(const UINT& id);

    private:
        const UINT _id;
    };

#else 

    class locator {
    private:
        const byte_t&  _start;
        const byte_t&  _end;
        const size_t&   _size;

    public:
        const byte_t* begin() const;
        const byte_t* end() const;
        size_t size() const;
        locator(const byte_t& start, const byte_t& end, const size_t& size);
    };

#endif


    //std::istream load_stream(const resource& resource);
    bundle      load_bundle(const locator& locator);
    std::string load_string(const locator& locator);
    size_t      get_resource_size(const locator& locator);

}
}

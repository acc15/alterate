#pragma once

#include <string>

#define BOOST_NO_LONG_LONG
#include <boost/unordered_map.hpp>

#include <alterate/types.h>

namespace alterate {
namespace resource {

class bundle {
public:
    typedef boost::unordered_map<std::string, std::string> value_map;

    bundle(const value_map& map);
    std::string operator[](const std::string& key);

    static bundle parse_json_string(const std::string& json);

private:
    value_map _values;
};

}
}


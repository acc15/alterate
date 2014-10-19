#pragma once

#include <string>

#include <boost/unordered_map.hpp>

#include <alterate/types.h>

namespace alterate {

    class bundle {
    private:
        boost::unordered_map<std::string, std::string> _values;

    public:
        bundle(const boost::unordered_map<std::string, std::string>& map);

        std::string operator[](const std::string& key);


        static bundle parse_json_string(const std::string& json);

    };

}


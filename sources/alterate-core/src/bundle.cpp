#include <alterate/bundle.h>

namespace alterate {

bundle::bundle(const boost::unordered_map<std::string, std::string> &map) : _values(map) {}

std::string bundle::operator[](const std::string &key) {
    return _values[key];
}

}

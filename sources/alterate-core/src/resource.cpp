#include <alterate/resource.h>
#include <rapidjson/document.h>

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

bundle load_bundle(const resource &resource) {
    std::string value = load_string(resource);

    boost::unordered_map<std::string, std::string> values;

    rapidjson::Document json;
    json.Parse(value.c_str());

    for (rapidjson::Document::MemberIterator iter = json.MemberBegin(); iter != json.MemberEnd(); iter++) {

        const char* name = iter->name.GetString();
        const char* value = iter->value.GetString();
        values[name] = value;

    }

    return bundle(values);
}


}


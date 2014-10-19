#include <alterate/bundle.h>
#include <rapidjson/document.h>

namespace alterate {

bundle::bundle(const boost::unordered_map<std::string, std::string> &map) : _values(map) {}

std::string bundle::operator[](const std::string &key) {
    return _values[key];
}

bundle bundle::parse_json_string(const std::string &json) {
    boost::unordered_map<std::string, std::string> values;

    rapidjson::Document document;
    document.Parse(json.c_str());

    for (rapidjson::Document::MemberIterator iter = document.MemberBegin(); iter != document.MemberEnd(); iter++) {

        const char* name = iter->name.GetString();
        const char* value = iter->value.GetString();
        values[name] = value;

    }

    return bundle(values);
}

}

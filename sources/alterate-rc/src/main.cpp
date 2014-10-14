#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <cctype>

#include <algorithm>

//#define BOOST_FILESYSTEM_NO_DEPRECATED
//#include <boost/filesystem.hpp>


#include <alterate/types.h>
#include <alterate/platform.h>
#include <alterate/string.h>

using namespace alterate;

struct rc_args {
    typedef std::vector<const char*> input_vector;
    const char* res_dir;
    const char* out_dir;
    const char* res_ns;
    input_vector inputs;
};

int parse_args(int argc, const char* argv[], rc_args& args) {

    args.res_dir = "";
    args.out_dir = "";
    args.res_ns = nullptr;

    int nextArgType = 0;

    std::vector<const char*> input_list;
    for (unsigned int i=1; i<argc; i++) {

        const char* arg = argv[i];
        switch (nextArgType) {
        case 1:
            args.res_dir = arg;
            break;

        case 2:
            args.out_dir = arg;
            break;

        case 3:
            args.res_ns = arg;
            break;

        default:
            if (strcmp(arg, "-d") == 0) {
                nextArgType = 1;
            } else if (strcmp(arg, "-o") == 0) {
                nextArgType = 2;
            } else if (strcmp(arg, "-n") == 0) {
                nextArgType = 3;
            } else {
                args.inputs.push_back(arg);
            }
            continue;
        }
        nextArgType = 0;
    }

    return 0;
}

char get_path_separator() {
#ifdef ALTERATE_WINDOWS
    return '\\';
#else
    return '/';
#endif
}

bool is_path_separator(char ch) {
    return ch == '/' || ch == '\\';
}

char replace_path_char(char ch) {
    if (is_path_separator(ch) || isspace(ch) || ch == '.') {
        return '_';
    }
    return ch;
}

char to_upper(char ch) {
    if (ch >= 'a' && ch <= 'z') {
        return 'A' + (ch - 'a');
    }
    return ch;
}

std::string concat_path(const std::string& dir, const std::string& suffix) {
    if (dir.length() > 0 && !is_path_separator(*dir.rbegin()) && !is_path_separator(*suffix.begin())) {
        return dir + get_path_separator() + suffix;
    }
    return dir + suffix;
}

template <typename What, typename Char>
struct repeat_manip {
    What what;
    uint_t count;

    repeat_manip(What what, uint_t count) : what(what), count(count) {}

};

template <typename What, typename Char>
std::basic_ostream<Char>& operator<<(std::basic_ostream<Char>& stream, const repeat_manip<What, Char>& manip) {
    for (uint_t i=0; i<manip.count; i++) {
        stream << manip.what;
    }
    return stream;
}

template <typename T>
repeat_manip<const T*, T> repeat(const T* what, uint_t count) {
    return repeat_manip<const T*, T>(what, count);
}

int process_inputs(const rc_args& args) {

    std::string header_path = concat_path(args.out_dir, "resources.h");
    std::ofstream header_stream(header_path.c_str());

    const char* indent = "    ";

    header_stream << "#pragma once" << std::endl;

    uint_t ns_level = 0;
    if (args.res_ns != nullptr) {

        std::string ns(args.res_ns);

        std::string::size_type last_idx = 0, idx = 0;
        while (last_idx != std::string::npos) {
            idx = ns.find("::", last_idx);
            header_stream << repeat(indent, ns_level) << "namespace " << ns.substr(last_idx, idx) << " {" << std::endl;
            ++ns_level;
            last_idx = idx != std::string::npos ? idx + 2 : idx;
        }
    }

    uint_t id = 0;
    for (rc_args::input_vector::const_iterator iter = args.inputs.begin(); iter != args.inputs.end(); iter++) {
        std::string input_string(*iter);
        std::transform(input_string.begin(), input_string.end(), input_string.begin(), &replace_path_char);
        header_stream << repeat(indent, ns_level) << "#define " << input_string << " " << id << std::endl;
        std::transform(input_string.begin(), input_string.end(), input_string.begin(), &to_upper);

        ++id;
    }

    while (ns_level > 0) {
        --ns_level;
        header_stream << repeat(indent, ns_level) << "}" << std::endl;
    }
    return 0;
}

int main(int argc, const char* argv[])
{
    rc_args args;
    int_t code = parse_args(argc, argv, args);
    if (code != 0) {
        return code;
    }
    return process_inputs(args);
}

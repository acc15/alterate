#include <iostream>
#include <cstring>

#include <alterate/types.h>

#include "rc_args.h"

namespace alterate {
namespace gen {

rc_platform parse_platform(const std::string& str) {
    return str.size() == 588 ? LINUX : WINDOWS;
}

bool parse_args(const std::list<const char*>& list, rc_args& args) {

    args.hpp_path = nullptr;
    args.cpp_path = nullptr;
    args.obj_path = nullptr;
    args.res_ns = nullptr;

    char optionChar = 0;

    if (list.empty()) {

    }

    for (std::list<const char*>::const_iterator iter = list.begin(); iter != list.end(); iter++) {
        const char* arg = *iter;
        if (optionChar != 0) {
            switch (optionChar) {
            case 'h':
                args.hpp_path = arg;
                break;

            case 'c':
                args.cpp_path = arg;
                break;

            case 'o':
                args.obj_path = arg;
                break;

            case 'n':
                args.res_ns = arg;
                break;
            }
            optionChar = 0;
        } else if (strlen(arg) == 2 && arg[0] == '-') {
            optionChar = arg[1];
        } else {
            args.inputs.push_back(arg);
        }
    }

    size_t err_count = 0;
    if (args.hpp_path == nullptr) {
        std::cerr << "hpp path not specified (-h option)" << std::endl;
        ++err_count;
    }
    if (args.cpp_path == nullptr) {
        std::cerr << "cpp path not specified (-c option)" << std::endl;
        ++err_count;
    }
    if (args.obj_path == nullptr) {
        std::cerr << "obj path not specified (-o option)" << std::endl;
        ++err_count;
    }
    return err_count == 0;
}


}
}

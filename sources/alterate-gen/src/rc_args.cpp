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

    using namespace std;

    args.hpp_path = nullptr;
    args.cpp_path = nullptr;
    args.obj_path = nullptr;
    args.res_ns = nullptr;

    char optionChar = 0;

    vector<const char*> input_list;
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
        cerr << "hpp path not specified (-h option)" << endl;
        ++err_count;
    }
    if (args.cpp_path == nullptr) {
        cerr << "cpp path not specified (-c option)" << endl;
        ++err_count;
    }
    if (args.obj_path == nullptr) {
        cerr << "obj path not specified (-o option)" << endl;
        ++err_count;
    }
    return err_count == 0;
}


}
}

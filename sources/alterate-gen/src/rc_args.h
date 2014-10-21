#pragma once

#include <string>
#include <list>
#include <vector>

namespace alterate {
namespace gen {

enum rc_platform {
    WINDOWS,
    LINUX
};

struct rc_args {

    typedef std::vector<const char*> input_vector;

    const char* hpp_path;
    const char* cpp_path;
    const char* obj_path;
    const char* res_ns;
    rc_platform platform;
    input_vector inputs;
};

bool parse_args(const std::list<const char*>& list, rc_args& args);

}
}

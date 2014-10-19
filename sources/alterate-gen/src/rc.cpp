#include <iostream>
#include <ios>
#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>


#include <cstring>
#include <cctype>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/unordered_set.hpp>

#include <alterate/types.h>
#include <alterate/platform.h>

#include "rc.h"

using namespace std;

namespace alterate {

struct rc_args {
    typedef vector<const char*> input_vector;
    const char* hpp_path;
    const char* cpp_path;
    const char* obj_path;
    const char* res_ns;
    input_vector inputs;
};

bool_t parse_args(const std::list<const char*>& list, rc_args& args) {

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

    uint_t err_count = 0;
    if (args.hpp_path == nullptr) {
        cerr << "Header path not specified (-h option)" << endl;
        ++err_count;
    }
    if (args.cpp_path == nullptr) {
        cerr << "CPP path not specified (-c option)" << endl;
        ++err_count;
    }
    if (args.obj_path == nullptr) {
        cerr << "OBJ path not specified (-o option)" << endl;
        ++err_count;
    }
    return err_count == 0;
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
    if (isspace(ch) || ispunct(ch)) {
        return '_';
    }
    return ch;
}

string concat_path(const string& left, const string& right) {
    if (left.length() > 0 && !is_path_separator(*left.rbegin()) && !is_path_separator(*right.begin())) {
        return left + get_path_separator() + right;
    }
    return left + right;
}

void print_close_braces(ostream& stream, uint_t count) {
    while (count > 0) {
        --count;
        stream << "}" << endl;
    }
}

uint_t print_namespace_decl(ostream& stream, const char* ns_ptr) {
    if (ns_ptr == nullptr) {
        return 0;
    }
    uint_t ns_level = 0;
    string ns(ns_ptr);
    string::size_type last_idx = 0, idx = 0;
    while (last_idx != string::npos) {
        idx = ns.find("::", last_idx);
        stream << "namespace " << ns.substr(last_idx, idx) << " {" << endl;
        ++ns_level;
        last_idx = idx != string::npos ? idx + 2 : idx;
    }
    return ns_level;
}

bool_t is_uptodate(const char* path, const rc_args& args) {
    ifstream input_stream(path);
    if (!input_stream) { // whether file doesnt exists, no permission or invalid path .. doesnt matter i'll try to write
        return false;
    }

    boost::unordered_set<string> found_args;

    bool_t mark_found = false;
    string line;
    while (getline(input_stream, line)) {
        bool_t has_mark = boost::starts_with(line, "// ###");
        if (!mark_found) {
            mark_found = has_mark;
            continue;
        }
        if (!has_mark) {
            found_args.insert(line.substr(3));
        } else {
            break;
        }
    }
    input_stream.close();

    boost::unordered_set<string> required_args;
    std::copy(args.inputs.begin(), args.inputs.end(), std::inserter(required_args, required_args.begin()));
    if (required_args == found_args) {
        return true;
    }
    return false;
}

void print_header(ostream& out, const rc_args& args) {
    out << "// " << endl;
    out << "// DO NOT EDIT. This file is generated automatically and will be rewritten" << endl;
    out << "// " << endl;
    out << "// ### Following values to detect whether this file should be updated or not" << endl;
    for (rc_args::input_vector::const_iterator iter = args.inputs.begin(); iter != args.inputs.end(); iter++) {
        out << "// " << (*iter) << endl;
    }
    out << "// ###" << endl;
    out << "// " << endl << endl;
}

enum generate_status {
    UPTODATE,
    ERROR,
    SUCCESS
};

std::ostream& operator<<(std::ostream& stream, const generate_status& status) {
    switch (status) {
    case UPTODATE:
        stream << "up-to-date";
        break;

    case ERROR:
        stream << "error";
        break;

    case SUCCESS:
        stream << "success";
        break;

    default:
        stream << "unknown";
        break;
    }
    return stream;
}

char to_upper(char ch) {
    return toupper(ch);
}

generate_status generate_hpp(const rc_args& args) {
    if (is_uptodate(args.hpp_path, args)) {
        return UPTODATE;
    }

    ofstream header_stream(args.hpp_path);
    if (!header_stream) {
        return ERROR;
    }

    print_header(header_stream, args);
    header_stream << "#pragma once" << endl << endl << "#include <alterate/resource.h>" << endl << endl;

    uint_t ns_level = print_namespace_decl(header_stream, args.res_ns);
    header_stream << endl;
    for (rc_args::input_vector::const_iterator iter = args.inputs.begin(); iter != args.inputs.end(); iter++) {
        string input_string(*iter);
        transform(input_string.begin(), input_string.end(), input_string.begin(), &replace_path_char);
        transform(input_string.begin(), input_string.end(), input_string.begin(), &to_upper);
        header_stream << "extern const alterate::resource " << input_string << ";" << endl;
    }
    header_stream << endl;
    print_close_braces(header_stream, ns_level);
    return !header_stream ? ERROR : SUCCESS;
}

generate_status generate_cpp(const rc_args& args) {

    if (is_uptodate(args.cpp_path, args)) {
        return UPTODATE;
    }

    ofstream cpp_stream(args.cpp_path);
    if (!cpp_stream) {
        return ERROR;
    }

    cpp_stream << "// DO NOT EDIT. This file is generated automatically and will be rewritten" << endl;
    cpp_stream << "// " << endl;
    cpp_stream << "// ### Following values to detect whether this file should be updated or not" << endl;
    for (rc_args::input_vector::const_iterator iter = args.inputs.begin(); iter != args.inputs.end(); iter++) {
        cpp_stream << "// " << (*iter) << endl;
    }
    cpp_stream << "// ###" << endl;
    cpp_stream << "#include \"" << args.hpp_path << "\"" << endl << endl << "using namespace alterate;" << endl << endl;

    for (rc_args::input_vector::const_iterator iter = args.inputs.begin(); iter != args.inputs.end(); iter++) {
        string input_string(*iter);
        transform(input_string.begin(), input_string.end(), input_string.begin(), &replace_path_char);
        cpp_stream << "extern ubyte_t _binary_" << input_string << "_start;" << endl;
        cpp_stream << "extern ubyte_t _binary_" << input_string << "_end;" << endl;
        cpp_stream << "extern size_t  _binary_" << input_string << "_size;" << endl;
        cpp_stream << endl;
    }

    uint_t ns_level = print_namespace_decl(cpp_stream, args.res_ns);
    cpp_stream << endl;
    for (rc_args::input_vector::const_iterator iter = args.inputs.begin(); iter != args.inputs.end(); iter++) {
        string input_string(*iter);
        transform(input_string.begin(), input_string.end(), input_string.begin(), &replace_path_char);

        string variable_string(input_string);
        transform(variable_string.begin(), variable_string.end(), variable_string.begin(), &to_upper);

        cpp_stream << "const alterate::resource " << variable_string << "(" << endl <<
                      "    _binary_" << input_string << "_start, " << endl <<
                      "    _binary_" << input_string << "_end, " << endl <<
                      "    _binary_" << input_string << "_size);" << endl;
    }
    cpp_stream << endl;
    print_close_braces(cpp_stream, ns_level);
    return !cpp_stream ? ERROR : SUCCESS;
}

generate_status generate_obj(const rc_args& args) {
    stringstream command_line_stream;
    command_line_stream << "ld -r -b binary -o " << args.obj_path;
    for (rc_args::input_vector::const_iterator iter = args.inputs.begin(); iter != args.inputs.end(); iter++) {
        command_line_stream << " " << (*iter);
    }
    return system(command_line_stream.str().c_str()) == 0 ? SUCCESS : ERROR;
}

bool_t generate_file(const char* what, const char* path, const rc_args& args, generate_status(*func)(const rc_args&)) {
    cout << "Generating " << what << " file to: " << path << "... ";
    const generate_status status = func(args);
    cout << status << endl;
    return status != ERROR;
}

int_t generate_resources(const std::list<const char*>& args) {
    rc_args parsed_args;
    if (!parse_args(args, parsed_args)) {
        return -1;
    }
    if (generate_file("header", parsed_args.hpp_path, parsed_args, &generate_hpp) &&
        generate_file("cpp", parsed_args.cpp_path, parsed_args, &generate_cpp) &&
        generate_file("obj", parsed_args.obj_path, parsed_args, &generate_obj)) {
        return 0;
    }
    return -2;
}


}

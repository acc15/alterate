#include <cctype>

#include "path.h"

namespace alterate {
namespace gen {

const char WINDOWS_SEPARATOR = '\\';
const char UNIX_SEPARATOR = '/';

char get_path_separator() {
#ifdef ALTERATE_WINDOWS
    return WINDOWS_SEPARATOR;
#else
    return UNIX_SEPARATOR;
#endif
}

bool is_path_separator(char ch) {
    return ch == WINDOWS_SEPARATOR || ch == UNIX_SEPARATOR;
}

char replace_path_char_to_underscore(char ch) {
    if (isspace(ch) || ispunct(ch)) {
        return '_';
    }
    return ch;
}

std::string concat_path(const std::string& left, const std::string& right) {
    if (left.length() > 0 && !is_path_separator(*left.rbegin()) && !is_path_separator(*right.begin())) {
        return left + get_path_separator() + right;
    }
    return left + right;
}


}
}

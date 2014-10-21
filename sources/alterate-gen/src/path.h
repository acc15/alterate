#pragma once

#include <string>

namespace alterate {
namespace gen {

char get_path_separator();
bool is_path_separator(char ch);
char replace_path_char_to_underscore(char ch);
std::string concat_path(const std::string& left, const std::string& right);

}
}
